'''
import preprocessing, dataloader
import numpy as np
import pandas as pd
import re
import random
import pickle
import supervised 
from sklearn.model_selection import StratifiedKFold
from sklearn.utils import shuffle

f = 'F:/Program Files/paper2019/team/code_cp/delete_data.txt'
with open(f,'rb') as f:
    df = pickle.load(f)
Sequences, Labels = df[:574511], df[574511:]
x_train, x_test = Sequences[:459608], Sequences[459608:]
y_train, y_test = Labels[:459608], Labels[459608:]
print(len(Labels),len(y_train))
if __name__ == '__main__':
    feature_extractor = preprocessing.FeatureExtractor()
    x_train_total = feature_extractor.fit_transform(x_train, term_weighting='tf-idf')
    x_test = feature_extractor.transform(x_test)
    y_train_total = y_train

    # Divided calibration set
    location = list(i for i,v in enumerate(y_train_total) if v==0)
    calibration = list(x_train_total[i] for i in location)
    x_train = x_train_total
    train_total_sum,test_total_sum = np.array(x_train_total).shape[0], np.array(y_test).shape[0]
    calibration_sum = len(location)
    test_normal_sum = len(list(i for i,v in enumerate(y_test) if v==0))

    print('=================CV=====================')
    print('Total:{},Train:{},Test:{}'.format(np.array(Sequences).shape[0],train_total_sum,test_total_sum))
    print('Train: calibration:{},Anomaly:{}'.format(calibration_sum,(train_total_sum-calibration_sum)))
    print('Test: Normal:{},Anomaly:{}'.format(test_normal_sum,(np.array(x_test).shape[0] - test_normal_sum)))

    for i in ['LR', 'Decision_Tree', 'SVM']:
        model = supervised.Model()
        if i is 'LR':
            model.LR()
            model.fit(x_train_total, y_train_total.astype('int'))
            classical_lr = model.predict(x_test)
            classical_lr = model.zero_mat(classical_lr)

            model.LR()
            model.fit(x_train, y_train.astype('int'))
            scores_cali_lr = model.decision_function(calibration)
            scores_ver_lr = model.decision_function(x_test)
            ver_lr = model.run(scores_cali_lr, scores_ver_lr)
'''

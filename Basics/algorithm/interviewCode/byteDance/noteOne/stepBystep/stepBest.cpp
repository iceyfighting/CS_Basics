/*
 *上台阶，一次可以走一步或两步至n步
 *打印所有可能的上法
 * */

#include<iostream>
#include<vector>
using namespace std;
vector<vector<int> > result;

class Solution{
    public:
        void stepCount(int n, vector<int> &temp)
        {
            if(n == 0)
            {
                result.push_back(temp);
            }
            else if(n < 0)
            {
                
            }
            else 
            {
                temp.push_back(1);
                stepCount(n-1, temp );
                temp.pop_back();
                
                temp.push_back(2);
                stepCount(n-2, temp );
                temp.pop_back();
            }
        }
};

int main()
{
    Solution ss;
    vector<int> tmp;
    ss.stepCount(3, tmp);
    for(vector<vector<int> >::iterator iter=result.begin();iter !=result.end();iter++)
    {
        vector<int> vec_temp = *iter;
        for(vector<int>::iterator it = vec_temp.begin();it != vec_temp.end();it++)
        {
            cout << *it << " " ;
        }
        cout << endl;
    }
    //cout<<result;

}

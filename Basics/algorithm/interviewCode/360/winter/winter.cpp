#include<iostream>
#include<queue>
using namespace std;

int main()
{
    int m,n;//m个选手,n连胜
    cin >> n >> m ;
    queue<int> q;
    int h,y,cnt2=0   ;//cnt2是共进行的比赛场数
    for(int i = 0;i< n;i++)
    {
        cin >> h;
        q.push(h);//把每个选手的战斗力存放进队列中
    }
    
    int cnt = 0;//每个选手进行多少场比赛
    h = q.front();//取第一个元素
    q.pop();
    //while循环的终止条件:比赛次数cnt>连胜次数m
    while(cnt < m)
    {
        cnt2++;
        y = q.front();
        if(h > y) //若h赢了，则h继续作为基准
        {
            cnt++;
            q.pop();
            q.push(y);
        }
        else //若y赢了，重新开始
        {
            q.pop();
            q.push(h);
            h = y;
            cnt = 1;
        }
        cout << "cnt的变化:" << cnt << endl;
    }
    cout << "共进行的比赛场数:" << cnt2 << endl; 
    return 0;
}

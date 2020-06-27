#include<iostream>
using namespace std;

double a[105][105];

int main()
{
    int n,x;
    cin >> n >> x;
    for(int i = 0;i<=x;i++)
    {
        a[1][i] = 1.0/(x+1);
    }
    if(n == 1)
    {
        printf("%.5f\n",a[1][0]);
        return 0;
    }

    for(int i = 2;i<=n;i++)
    {
        for(int j = 0;j<=x;j++)
        {
            for(int k=j;k<=x;k++)
            {
                printf("变化前a[%d",i);
                printf("][%d",j);
                printf("]:%.5f",a[i][j]);
                a[i][j] += (a[i-1][k]*(1.0/(k+1)));

                printf("    变化后:%.5f\n",a[i][j]);
            }
        }
    }
    printf("%.5f\n",a[n][0]);
    return 0;
}

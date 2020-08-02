#include<iostream>
#include<string.h>
using namespace std;

#define cols  5
#define rows  5

class Solution{
    public:
        int isLandCore(int Land[][cols],int row,int col,int visited[][cols], bool & flag)
        {
            int a[4];
            int result = 0;
            memset(a,0,4*sizeof(int));
            if(visited[row][col] == 0 && Land[row][col]==1)
            {
                flag = true;  // 代表这是一个小岛
                visited[row][col] = 1;
                //判断是否有相连的小岛
                bool tmp = false;
                if(row > 0)
                {
                   a[0]= isLandCore(Land,row-1,col,visited, tmp);//每次判断一个点是否为小岛时tmp都为false
                }
                if(row < rows-1)
                {
                    a[1]=isLandCore(Land,row+1,col,visited, tmp);
                }

                if(col > 0)
                {
                   a[2]= isLandCore(Land,row,col-1,visited, tmp);
                }

                if(col < cols-1)
                {
                    a[3]=isLandCore(Land,row,col+1,visited, tmp);
                }
                result = 1 + a[0] + a[1] + a[2] + a[3];
            }
            else
            {
                result = 0;
            }
            return result;
        }
        int isLand(int Land[][cols])
        {
            if(Land == NULL)
            {
                return 0;
            }
            int count = 0,sum = 0;
            bool flag;
            int visited[rows][cols];
            memset(visited,0,sizeof(int)*rows*cols);
            for(int i=0; i < rows; ++i)
            {
               for(int j=0; j < cols; ++j)
               {
                   flag = false;
                   sum += isLandCore(Land, i, j, visited, flag);
                   if(true == flag)
                   {
                       ++count; 
                   }
               }
            }
            return sum;
        }
};

int main()
{
   int Land[rows][cols] = {{1,0,0,1,1},
             {1,1,0,0,0},
             {1,0,1,0,1},
             {0,0,1,1,1},
             {1,1,0,0,0}};
    Solution ss;
    int sum = ss.isLand(Land);
    cout << sum << endl;
}


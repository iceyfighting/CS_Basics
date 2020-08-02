#include<iostream>
#include<string.h>
using namespace std;

#define cols  5
#define rows  5

class Solution{
    public:
        void isLandCore(int *Land,int row,int col,int visited[][cols], bool & flag)
        {
            if(visited[row][col] == 0 && Land[row*cols+col]==1)
            {
                flag = true;  // 代表这是一个小岛
                visited[row][col] = 1;
                //判断是否有相连的小岛
                bool tmp = false;
                if(row > 0)
                {
                    isLandCore(Land,row-1,col,visited, tmp);//每次判断一个点是否为小岛时tmp都为false
                }
                if(row < rows-1)
                {
                    isLandCore(Land,row+1,col,visited, tmp);
                }

                if(col > 0)
                {
                    isLandCore(Land,row,col-1,visited, tmp);
                }

                if(col < cols-1)
                {
                    isLandCore(Land,row,col+1,visited, tmp);
                }
            }
        }
        int isLand(int *Land)
        {
            if(Land == NULL)
            {
                return 0;
            }
            int count = 0;
            bool flag;
            int visited[rows][cols];
            memset(visited,0,sizeof(int)*rows*cols);
            for(int i=0; i < rows; ++i)
            {
               for(int j=0; j < cols; ++j)
               {
                   flag = false;
                   isLandCore(Land, i, j, visited, flag);
                   if(true == flag)
                   {
                       ++count; 
                   }
               }
            }
            return count;
        }
};

int main()
{
   int Land[] = { 1,0,0,1,1,
                  1,1,0,0,0,
                  1,0,1,0,1,
                  0,0,1,1,1,
                  1,1,0,0,0};
    Solution ss;
    int sum = ss.isLand(Land);
    cout << sum << endl;
}


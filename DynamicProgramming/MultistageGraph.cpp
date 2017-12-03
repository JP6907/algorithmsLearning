/**
 * 问题描述：
 * 多段图最小成本路径
 */
#include "stdio.h"
#define n 7 //图的顶点数
#define k 4 //图的段数
#define MAX 23767
int cost[n][n]; //成本值数组
int path[k];    //存储最短路径的数组

void creatgraph() //创建图的(成本)邻接矩阵
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &cost[i][j]); //获取成本矩阵数据
}

void printgraph() //输出图的成本矩阵
{
    int i, j;
    printf("成本矩阵:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d ", cost[i][j]);
        printf("\n");
    }
}

//使用向前递推算法求多段图的最短路径
void FrontPath()
{
    int i, j, length, temp, v[n], d[n];
    for (i = 0; i < n; i++)
        v[i] = 0;
    for (i = n - 2; i >= 0; i--)
    {
        for (length = MAX, j = i + 1; j <= n - 1; j++)
            if (cost[i][j] > 0 && (cost[i][j]) + v[j] < length)
            {
                length = cost[i][j] + v[j];
                temp = j;
            }
        v[i] = length;
        d[i] = temp;
    }
    path[0] = 0;         //起点
    path[k - 1] = n - 1; //最后的目标
    for (i = 1; i <= k - 2; i++)
        (path[i]) = d[path[i - 1]]; //将最短路径存入数组中
}

//使用向后递推算法求多段图的最短路径
void BackPath()
{
    int i, j, length, temp, v[n], d[n];
    for (i = 0; i < n; i++)
        v[i] = 0;
    for (i = 1; i <= n - 1; i++)
    {
        for (length = MAX, j = i - 1; j >= 0; j--)
            if (cost[j][i] > 0 && (cost[j][i]) + v[j] < length)
            {
                length = cost[j][i] + v[j];
                temp = j;
            }
        v[i] = length;
        d[i] = temp;
    }
    path[0] = 0;
    path[k - 1] = n - 1;
    for (i = k - 2; i >= 1; i--)
        (path[i]) = d[path[i + 1]];
}

//输出最短路径序列
void printpath()
{
    int i;
    for (i = 0; i < k; i++)
        printf("%d ", path[i]);
}

int main()
{
    freopen("input.txt", "r", stdin);
    creatgraph();
    printgraph();
    FrontPath();
    printf("输出使用向前递推算法所得的最短路径:\n");
    printpath();
    printf("\n输出使用向后递推算法所得的最短路径:\n");
    BackPath();
    printpath();
    printf("\n");
}
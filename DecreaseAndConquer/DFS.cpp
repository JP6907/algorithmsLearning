/**
 * 问题描述：
 * 深度优先搜索图算法
 */

#include <stdio.h>
#define MAX 1000
//访问标志数组
int visited[MAX] = {0};
struct MGraph{
    ArcNode nodes[MAX];
    Vertice vertices[MAX];
};
struct ArcNode{
    int data;
    int adjvex;
    ArcNode *nextarc;
};
struct Vertice{
    ArcNode *firstarc;
};
//用邻接表方式实现深度优先搜索(递归方式）
//v 传入的是第一个需要访问的顶点
void DFS(MGraph G, int v)
{
    //图的顶点的搜索指针
    ArcNode *p;
    //置已访问标记
    visited[v] = 1;
    //输出被访问顶点的编号
    printf("%d  ", v);
    //p指向顶点v的第一条弧的弧头结点
    p = G.vertices[v].firstarc;
    while (p != NULL)
    {
        //若p->adjvex顶点未访问,递归访问它
        if (visited[p->adjvex] == 0)
        {
            DFS(G, p->adjvex);
        }
        //p指向顶点v的下一条弧的弧头结点
        p = p->nextarc;
    }
}
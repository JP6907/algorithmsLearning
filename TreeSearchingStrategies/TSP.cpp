/**
 * 问题描述：
 * 旅行推销员问题
 * 分支限界法求
 * http://blog.csdn.net/lovesummerforever/article/details/18622127
 */

//分支限界法
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#define INF 100000
using namespace std;
/*  n*n的一个矩阵  */
int n;
int mp[22][22]; //最少3个点，最多15个点
/*输入距离矩阵*/
void in()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                mp[i][j] = INF;
                continue;
            }
            scanf("%d", &mp[i][j]);
        }
    }
}
struct node
{
    int visp[22]; //标记哪些点走了
    int st;       //起点
    int st_p;     //起点的邻接点
    int ed;       //终点
    int ed_p;     //终点的邻接点
    int k;        //走过的点数
    int sumv;     //经过路径的距离
    int lb;       //目标函数的值
    bool operator<(const node &p) const
    {
        return lb > p.lb;
    }
};
priority_queue<node> q;
int low, up;
int inq[22];
//确定上界
int dfs(int u, int k, int l)
{
    if (k == n)
        return l + mp[u][1];
    int minlen = INF, p;
    for (int i = 1; i <= n; i++)
    {
        if (inq[i] == 0 && minlen > mp[u][i]) /*取与所有点的连边中最小的边*/
        {
            minlen = mp[u][i];
            p = i;
        }
    }
    inq[p] = 1;
    return dfs(p, k + 1, l + minlen);
}
int get_lb(node p)
{
    int ret = p.sumv * 2;       //路径上的点的距离
    int min1 = INF, min2 = INF; //起点和终点连出来的边
    for (int i = 1; i <= n; i++)
    {
        if (p.visp[i] == 0 && min1 > mp[i][p.st])
        {
            min1 = mp[i][p.st];
        }
    }
    ret += min1;
    for (int i = 1; i <= n; i++)
    {
        if (p.visp[i] == 0 && min2 > mp[p.ed][i])
        {
            min2 = mp[p.ed][i];
        }
    }
    ret += min2;
    for (int i = 1; i <= n; i++)
    {
        if (p.visp[i] == 0)
        {
            min1 = min2 = INF;
            for (int j = 1; j <= n; j++)
            {
                if (min1 > mp[i][j])
                    min1 = mp[i][j];
            }
            for (int j = 1; j <= n; j++)
            {
                if (min2 > mp[j][i])
                    min2 = mp[j][i];
            }
            ret += min1 + min2;
        }
    }
    return ret % 2 == 0 ? (ret / 2) : (ret / 2 + 1);
}
void get_up()
{
    inq[1] = 1;
    up = dfs(1, 1, 0);
}
void get_low()
{
    low = 0;
    for (int i = 1; i <= n; i++)
    {
        /*通过排序求两个最小值*/
        int min1 = INF, min2 = INF;
        int tmpA[22];
        for (int j = 1; j <= n; j++)
        {
            tmpA[j] = mp[i][j];
        }
        sort(tmpA + 1, tmpA + 1 + n); //对临时的数组进行排序
        low += tmpA[1];
    }
}
int solve()
{
    /*贪心法确定上界*/
    get_up();

    /*取每行最小的边之和作为下界*/
    get_low();

    /*设置初始点,默认从1开始 */
    node star;
    star.st = 1;
    star.ed = 1;
    star.k = 1;
    for (int i = 1; i <= n; i++)
        star.visp[i] = 0;
    star.visp[1] = 1;
    star.sumv = 0;
    star.lb = low;

    /*ret为问题的解*/
    int ret = INF;

    q.push(star);
    while (!q.empty())
    {
        node tmp = q.top();
        q.pop();
        if (tmp.k == n - 1)
        {
            /*找最后一个没有走的点*/
            int p;
            for (int i = 1; i <= n; i++)
            {
                if (tmp.visp[i] == 0)
                {
                    p = i;
                    break;
                }
            }
            int ans = tmp.sumv + mp[p][tmp.st] + mp[tmp.ed][p];
            node judge = q.top();

            /*如果当前的路径和比所有的目标函数值都小则跳出*/
            if (ans <= judge.lb)
            {
                ret = min(ans, ret);
                break;
            }
            /*否则继续求其他可能的路径和，并更新上界*/
            else
            {
                up = min(up, ans);
                ret = min(ret, ans);
                continue;
            }
        }
        /*当前点可以向下扩展的点入优先级队列*/
        node next;
        for (int i = 1; i <= n; i++)
        {
            if (tmp.visp[i] == 0)
            {
                next.st = tmp.st;

                /*更新路径和*/
                next.sumv = tmp.sumv + mp[tmp.ed][i];

                /*更新最后一个点*/
                next.ed = i;

                /*更新顶点数*/
                next.k = tmp.k + 1;

                /*更新经过的顶点*/
                for (int j = 1; j <= n; j++)
                    next.visp[j] = tmp.visp[j];
                next.visp[i] = 1;

                /*求目标函数*/
                next.lb = get_lb(next);

                /*如果大于上界就不加入队列*/
                if (next.lb > up)
                    continue;
                q.push(next);
            }
        }
    }
    return ret;
}
int main()
{
    in();
    printf("%d\n", solve());
    return 0;
}

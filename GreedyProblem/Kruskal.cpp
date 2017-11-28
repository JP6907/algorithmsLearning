/**
 * 问题描述：
 * Kruskal算法
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int M = 1e5 + 7;

struct node
{
    int a, b, val;
} Q[M];
int fa[M];

int Rd()
{
    int res = 0;
    char c;
    while (c = getchar(), !isdigit(c))
        ;
    do
    {
        res = (res << 3) + (res << 1) + (c ^ 48);
    } while (c = getchar(), isdigit(c));
    return res;
}

bool cmp(node a, node b)
{
    return a.val < b.val;
}

int getfa(int v)
{
    if (fa[v] != v)
        fa[v] = getfa(fa[v]);
    return fa[v];
}

int main()
{
    int i, j, n, m, x, y;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++)
    {
        Q[i].a = Rd();
        Q[i].b = Rd();
        Q[i].val = Rd();
    }
    sort(Q + 1, Q + m + 1, cmp);
    for (i = 1; i <= n; i++)
    {
        fa[i] = i;
    }

    int sum = 0, cut = 0;
    for (i = 1; i <= m; i++)
    {
        x = getfa(Q[i].a);
        y = getfa(Q[i].b);
        if (x == y)
            continue;
        sum += Q[i].val;
        if (++cut == n - 1)
            break;
        fa[x] = y;
    }
    printf("%d", sum);
    return 0;
}
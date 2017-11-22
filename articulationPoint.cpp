void dfs(int u)
{
    //记录dfs遍历次序
    static int counter = 0;

    //记录节点u的子树数
    int children = 0;

    ArcNode *p = graph[u].firstArc;
    visit[u] = 1;

    //初始化dfn与low
    dfn[u] = low[u] = ++counter;

    for (; p != NULL; p = p->next)
    {
        int v = p->adjvex;

        //节点v未被访问，则(u,v)为树边
        if (!visit[v])
        {
            children++;
            parent[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            //case (1)
            if (parent[u] == NIL && children > 1)
            {
                printf("articulation point: %d\n", u);
            }
            //case (2)
            if (parent[u] != NIL && low[v] >= dfn[u])
            {
                printf("articulation point: %d\n", u);
            }
        }

        //节点v已访问，则(u,v)为回边
        else if (v != parent[u])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
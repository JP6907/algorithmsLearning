/**
 * 问题描述：
 * A*算法
 * 启发式搜索单源最短路径
 * https://d1.zgdhhjha.com/zh-sg/A*%E6%90%9C%E5%AF%BB%E7%AE%97%E6%B3%95
 */
//伪代码
function A*(start,goal)
     closedset := the empty set                 //已经被估算的节点集合
     openset := set containing the initial node //将要被估算的节点集合，初始只包含start
     came_from := empty map
     g_score[start] := 0                        //g(n)
     h_score[start] := heuristic_estimate_of_distance(start, goal)    //通过估计函数 估计h(start)
     f_score[start] := h_score[start]            //f(n)=h(n)+g(n)，由于g(n)=0，所以省略
     while openset is not empty                 //当将被估算的节点存在时，执行循环
         x := the node in openset having the lowest f_score[] value   //在将被估计的集合中找到f(x)最小的节点
         if x = goal            //若x为终点，执行
             return reconstruct_path(came_from,goal)   //返回到x的最佳路径
         remove x from openset      //将x节点从将被估算的节点中删除
         add x to closedset      //将x节点插入已经被估算的节点
         for each y in neighbor_nodes(x)  //循环遍历与x相邻节点
             if y in closedset           //若y已被估值，跳过
                 continue
             tentative_g_score := g_score[x] + dist_between(x,y)    //从起点到节点y的距离
 
             if y not in openset          //若y不是将被估算的节点
                 add y to openset         //将y插入将被估算的节点中
                 tentative_is_better := true     //暂时判断为更好
             elseif tentative_g_score < g_score[y]         //如果起点到y的距离小于y的实际距离
                 tentative_is_better := true         //暂时判断为更好
             else
                 tentative_is_better := false           //否则判断为更差
             if tentative_is_better = true            //如果判断为更好
                 came_from[y] := x                  //将y设为x的子节点
                 g_score[y] := tentative_g_score    //更新y到原点的距离
                 h_score[y] := heuristic_estimate_of_distance(y, goal) //估计y到终点的距离
                 f_score[y] := g_score[y] + h_score[y]
     return failure
 
 function reconstruct_path(came_from,current_node)
     if came_from[current_node] is set
         p = reconstruct_path(came_from,came_from[current_node])
         return (p + current_node)
     else
         return current_node
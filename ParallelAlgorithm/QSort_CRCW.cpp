//A[1...n]排序用n个处理器，处理器i中存有A[i]
//f[i]中存有其元素是主元素的处理器号
//LC[1...n]和RC[1...n]分别记录给定主元素的左儿子和右儿子

for each processor i par-do
    root = i    //所有处理器竞争，只有一个写入root
    f[i] = root //所有处理器都把root写入自己的f[i]
    LC[i] = RC[i] = n + 1   //初始值
endfor

repeat for each processor i != root do
    if (A[i] < A[f[i]]) || (A[i] == A[f[i]] && i < f[i])
        LC[f[i]] = i    //并发写，所有满足条件的i只有一个写入LC[f[i]]作为左子树的根，也就是下一次循环的主元素
        if i == LC[f[i]] then
            exit        //若当前处理器写入则什么也不做
        else
            f[i] = LC[f[i]] //若当前处理器没有写入，那么它只能当LC[f[i]]的字节点了
        endif
    else
        RC[f[i]] = i    //并发写，所有满足条件的i只有一个写入RC[f[i]]作为右子树的根，也就是下一次循环的主元素
        if i == RC[f[i]] then
            exit        //若当前处理器写入则什么也不做
        else
            f[i] = RC[f[i]] //若当前处理器没有写入，那么它只能当RC[f[i]]的字节点了
        endif
    endif
endrepeat
/**
 * 红黑树
 * https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/zh/03.01.md
 * 1）每个结点要么是红的，要么是黑的。  
 * 2）根结点是黑的。  
 * 3）每个叶结点（叶结点即指树尾端NIL指针或NULL结点）是黑的。  
 * 4）如果一个结点是红的，那么它的俩个儿子都是黑的。  
 * 5）对于任一结点而言，其到叶结点树尾端NIL指针的每一条路径都包含相同数目的黑结点。
 */
RB-INSERT(T, z)  
y ← nil  
x ← T.root  
while x ≠ T.nil  
    do y ← x  
    if z.key < x.key  
        then x ← x.left  
    else x ← x.right  
z.p ← y  
if y == nil[T]  
    then T.root ← z  
else if z.key < y.key  
    then y.left ← z  
else y.right ← z  
z.left ← T.nil  
z.right ← T.nil  
z.color ← RED  
RB-INSERT-FIXUP(T, z)  //重点在这个插入后的修复

/**
 * 如果插入的是根结点，因为原树是空树，此情况只会违反性质2，所以直接把此结点涂为黑色。
 * 如果插入的结点的父结点是黑色，由于此不会违反性质2和性质4，红黑树没有被破坏，所以此时也是什么也不做。
 * 但当遇到下述3种情况时：
 * 
 * 插入修复情况1：如果当前结点的父结点是红色且祖父结点的另一个子结点（叔叔结点）是红色，
 * 把父节点和叔叔节点涂黑。祖父节点途红
 * 插入修复情况2：当前结点的父结点是红色,叔叔结点是黑色，当前结点是其父结点的右子
 * 插入修复情况3：当前结点的父结点是红色,叔叔结点是黑色，当前结点是其父结点的左子
 * 旋转，就如二叉平衡树的旋转，祖父节点是不平衡点
 */
RB-INSERT-FIXUP(T, z)  
while z.p.color == RED  
    do if z.p == z.p.p.left  
        then y ← z.p.p.right  
        if y.color == RED  
            then z.p.color ← BLACK              // ▹ Case 1  
            y.color ← BLACK                     // ▹ Case 1  
            z.p.p.color ← RED                   // ▹ Case 1  
            z ← z.p.p                           // ▹ Case 1  
        else if z == z.p.right  
            then z ← z.p                        // ▹ Case 2  
            LEFT-ROTATE(T, z)                    // ▹ Case 2  
        z.p.color ← BLACK                       // ▹ Case 3  
        z.p.p.color ← RED                       // ▹ Case 3  
        RIGHT-ROTATE(T, z.p.p)                   // ▹ Case 3  
    else (same as then clause with "right" and "left" exchanged)  
T.root.color ← BLACK  


/**
 * 删除节点
 * 如果删除的是红色节点，性质不变
 * 如果删除的是黑色节点，就要修正红黑树
 */

RB-DELETE(T, z)
if left[z] = nil[T] or right[z] = nil[T]  
    then y ← z  
    else y ← TREE-SUCCESSOR(z)  
if left[y] ≠ nil[T]  
    then x ← left[y]  
    else x ← right[y]  
 p[x] ← p[y]  
if p[y] = nil[T]  
    then root[T] ← x  
   else if y = left[p[y]]  
            then left[p[y]] ← x  
           else right[p[y]] ← x  
if y ≠ z  
   then key[z] ← key[y]  
        copy ys satellite data into z  
if color[y] = BLACK  
   then RB-DELETE-FIXUP(T, x)            //如果是删除黑树，进行修复
return y  

/**
 * 如果是以下情况，恢复比较简单：
 * a)当前结点是红+黑色 解法，直接把当前结点染成黑色，结束此时红黑树性质全部恢复。
 * b)当前结点是黑+黑且是根结点， 解法：什么都不做，结束。
 * 其他：
 * 删除修复情况1：当前结点是黑+黑且兄弟结点为红色(此时父结点和兄弟结点的子结点分为黑)
 * 把父结点染成红色，把兄弟结点染成黑色，之后重新进入算法
 * 
 * 删除修复情况2：当前结点是黑加黑且兄弟是黑色且兄弟结点的两个子结点全为黑色
 * 把当前结点和兄弟结点中抽取一重黑色追加到父结点上，把父结点当成新的当前结点，重新进入算法
 * 
 * 删除修复情况3：当前结点颜色是黑+黑，兄弟结点是黑色，兄弟的左子是红色，右子是黑色
 * 把兄弟结点染红，兄弟左子结点染黑，之后再在兄弟结点为支点解右旋，之后重新进入算法。
 * 
 * 删除修复情况4：当前结点颜色是黑-黑色，它的兄弟结点是黑色，但是兄弟结点的右子是红色，兄弟结点左子的颜色任意
 * 把兄弟结点染成当前结点父结点的颜色，把当前结点父结点染成黑色，兄弟结点右子染成黑色，
 * 之后以当前结点的父结点为支点进行左旋
 */

RB-DELETE-FIXUP(T, x)
 1 while x ≠ root[T] and color[x] = BLACK  
 2     do if x = left[p[x]]  
 3           then w ← right[p[x]]  
 4                if color[w] = RED  
 5                   then color[w] ← BLACK                       // ▹  Case 1  
 6                        color[p[x]] ← RED                      // ▹  Case 1  
 7                        LEFT-ROTATE(T, p[x])                    // ▹  Case 1  
 8                        w ← right[p[x]]                         // ▹  Case 1  
 9                if color[left[w]] = BLACK and color[right[w]] = BLACK  
10                   then color[w] ← RED                          //▹  Case 2  
11                        x ← p[x]                               // ▹  Case 2  
12                   else if color[right[w]] = BLACK  
13                           then color[left[w]] ← BLACK         // ▹  Case 3  
14                                color[w] ← RED                //  ▹  Case 3  
15                                RIGHT-ROTATE(T, w)             // ▹  Case 3  
16                                w ← right[p[x]]                // ▹  Case 3  
17                         color[w] ← color[p[x]]               //  ▹  Case 4  
18                         color[p[x]] ← BLACK                  //  ▹  Case 4  
19                         color[right[w]] ← BLACK              //  ▹  Case 4  
20                         LEFT-ROTATE(T, p[x])                  // ▹  Case 4  
21                         x ← root[T]                           // ▹  Case 4  
22        else (same as then clause with "right" and "left" exchanged)  
23 color[x] ← BLACK  
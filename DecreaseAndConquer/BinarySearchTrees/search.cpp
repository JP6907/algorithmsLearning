
/***
 * 问题描述：
 * 二叉搜索树搜索
 */
/************迭代方式***********/
#include <stdio.h>
#define dataType int
#define Tree int //树结构
Tree key[50], left[50], right[50];

dataType TreeSearch(Tree x, dataType k)
{
    if (x == NULL || k == key[x])
        return x;
    if (k < key[x])
        return TreeSearch(left[x], k);
    else
        return TreeSearch(right[x], k);
}

/*************非迭代方式（指针）****************/
dataType TreeSearch2(Tree x, dataType k)
{
    while (x != NULL && k != key[x])
    {
        if (k < key[x])
            x = left[x];
        else
            x = right[x];
    }
    return x;
}
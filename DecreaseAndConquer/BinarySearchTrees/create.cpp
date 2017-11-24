/**
 * 问题描述：
 * 构造：用数组arr[]创建二叉查找树
 */
#include "insert.cpp"
void Create_BST(BSTree &T, int arr[], int n)
{
    T = NULL; // 初始时为空树
    for (int i = 0; i < n; ++i)
        BST_Insert(T, arr[i]);
}

/**
 * Sorting with BST
 * 
 * 
 * Create_BST(T,arr,arr.length);
 * InorderTreeWalk(T);//遍历
 */
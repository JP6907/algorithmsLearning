#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>    //内含max(a,b)宏，故不需自己编写。
#include <stdbool.h>

/* 
 * 二叉树的二叉链表存储结构。
 * 额外添加树的高度，以判断结点的平衡度。
 */
typedef int TElemType;
typedef struct BiNode
{
    TElemType data;
    struct BiNode *lchild;
    struct BiNode *rchild;
    int height;
}BiNode, *BiTree;

//函数声明
bool AVLInsert(BiTree *T, TElemType key);
bool AVLDelete(BiTree *T, TElemType key);
bool LLRotate(BiTree *T);
bool LRRotate(BiTree *T);
bool RLRotate(BiTree *T);
bool RRRotate(BiTree *T);
int GetHeight(BiTree T);

#endif
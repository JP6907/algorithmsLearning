/*
 * 二叉平衡树的插入和删除操作
 */
#define _CRT_SECURE_NO_WARNINGS
#include "AVL.h"

#define TOTAL 10
bool InOrderTraverse(BiTree T);
bool print(BiTree *T);

int main()
{
    BiTree T = NULL;    //注意一定要将T初始化为空树。
    int i, num;

    //插入操作。
    printf("输入Total个数以构建二叉平衡树:\n");
    for (i = 0; i < TOTAL; i++)
    {
        scanf("%d", &num);
        AVLInsert(&T, num);
    }

    //检验插入操作。
    printf("树结构为:\n");
    print(&T);
    printf("中序遍历该树，检验是否为由小到大:\n");
    InOrderTraverse(T);
    putchar('\n');
    printf("树的深度为：%d\n", T->height);
    

    //删除操作。
    printf("输入待删除的数:");
    scanf("%d", &num);
    AVLDelete(&T, num);

    //检验删除操作。
    printf("删除后，树结构为:\n");
    print(&T);
    printf("中序遍历该树，检验是否为由小到大:\n");
    InOrderTraverse(T);
    putchar('\n');
    printf("树的深度为：%d\n", T->height);
    return 0;
}

/*
 * 中序遍历输出树结构。
 */
bool InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        printf("%-3d ", T->data);
        InOrderTraverse(T->rchild);
    }
    return true;
}

/*
 * 输出树结构，且标明父子关系。
 */
bool print(BiTree *T)
{
    
    if (!*T)
        return false;
    else
    {
        //如果树有左孩子或者右孩子，则输出它的左孩子和右孩子。
        //例：5有左孩子3和右孩子6，输出形式为：5(3,6)
        //5只有左孩子3，输出形式为：5(3, )
        //5只有右孩子6，输出形式为：5( ,6)
        if ((*T)->lchild || (*T)->rchild)
        {
            printf("%d(", (*T)->data);
            if ((*T)->lchild)
            {
                printf("%-3d,", (*T)->lchild->data);
            }
            else
            {
                printf("   ,");
            }
            if ((*T)->rchild)
            {
                printf("%-3d)\n", (*T)->rchild->data);
            }
            else
            {
                printf("   )\n");
            }
        }

        //递归输出左孩子和右孩子。
        print(&((*T)->lchild));
        print(&((*T)->rchild));
        return true;
    }
}
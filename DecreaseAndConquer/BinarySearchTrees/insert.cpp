/**********************
 * 问题描述：
 * 二叉查找树插入算法
 * 
 * 与搜索算法很相近
 */

int BST_Insert(BSTree &T, int k, Node *parent = NULL)
{
      if (T == NULL)
      {
            T = (BSTree)malloc(sizeof(Node));
            T->key = k;
            T->left = NULL;
            T->right = NULL;
            T->parent = parent;
            return 1; // 返回1表示成功
      }
      else if (k == T->key)
            return 0; // 树中存在相同关键字
      else if (k < T->key)
            return BST_Insert(T->left, k, T);
      else
            return BST_Insert(T->right, k, T);
}
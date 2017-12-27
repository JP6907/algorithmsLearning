/*
 * 实现二叉平衡树的插入、删除操作
 */

#include "AVL.h"

/*
 * 插入操作。
 * 如果以*T为根结点的二叉平衡树中已有结点key，插入失败，函数返回FALSE；
 * 否则将结点key插入到树中，插入结点后的树仍然为二叉平衡树，函数返回TRUE。
 */
bool AVLInsert(BiTree *T, TElemType key)
{
    BiTree t;

    //如果当前查找的根结点为空树，表明查无此结点，故插入结点。
    if (!*T)
    {
        t = (BiTree)malloc(sizeof(BiNode));
        t->data = key;
        t->height = 1;
        t->lchild = NULL;
        t->rchild = NULL;
        *T = t;
        return true;
    }
    //已有此结点，不再插入。
    else if (key == (*T)->data)
    {
        return false;
    }
    //在左子树中递归插入。
    else if (key < (*T)->data)
    {
        if (!AVLInsert(&((*T)->lchild), key))
            return false;
        else
        {
            //插入成功，修改树的高度。
            (*T)->height = max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;

            //已在*T的左子树插入结点key，判断是否需要进行旋转以保持二叉平衡树的特性。
            if (2 == GetHeight((*T)->lchild) - GetHeight((*T)->rchild))
            {
                //在左子树的左子树中插入结点。
                if (GetHeight((*T)->lchild->lchild) > GetHeight((*T)->lchild->rchild))
                {
                    LLRotate(T);
                }
                //在左子树的右子树中插入结点。
                else
                {
                    LRRotate(T);
                }
            }
            return true;
        }
    }
    //在右子树中递归插入。
    else // (key > (*T)->data)
    {
        if (!AVLInsert(&(*T)->rchild, key))
            return false;
        else
        {
            //插入成功，修改树的高度。
            (*T)->height = max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;

            //已在*T的右子树插入结点key，判断是否需要进行旋转以保持二叉平衡树的特性。
            if (-2 == GetHeight((*T)->lchild) - GetHeight((*T)->rchild))
            {
                //在右子树的左子树中插入结点。
                if (GetHeight((*T)->rchild->lchild) > GetHeight((*T)->rchild->rchild))
                {
                    RLRotate(T);
                }
                //在右子树的右子树中插入结点。
                else
                {
                    RRRotate(T);
                }
            }
            return true;
        }
    }
}

/*
 * 删除操作。
 * 如果以*T为根结点的树中存在结点key，将结点删除，函数返回TRUE，
 * 否则删除失败，函数返回FALSE。
 */
bool AVLDelete(BiTree *T, TElemType key)
{
    BiTree pre, post;

    //没有找到该结点。
    if (!*T)
        return false;
    //找到结点，将它删除。
    else if (key == (*T)->data)
    {
        //待删除节点为叶子结点。
        if (!(*T)->lchild && !(*T)->rchild)
            *T = NULL;
        //待删除结点只有右孩子。
        else if (!(*T)->lchild)
            *T = (*T)->rchild;
        //待删除结点只有左孩子。
        else if (!(*T)->rchild)
            *T = (*T)->lchild;
        //待删除结点既有左孩子，又有右孩子。
        else
        {
            //当待删除结点*T左子树的高度大于右子树的高度时，用*T的前驱结点pre代替*T，
            //再将结点pre从树中删除。这样可以保证删除结点后的树仍为二叉平衡树。
            if (GetHeight((*T)->lchild) > GetHeight((*T)->rchild))
            {
                //寻找前驱结点pre。
                pre = (*T)->lchild;
                while (pre->rchild)
                {
                    pre = pre->rchild;
                }
                //用pre替换*T。
                (*T)->data = pre->data;

                //删除节点pre。
                //虽然能够确定pre所属最小子树的根结点为&pre，
                //但是不采用AVLDelete(&pre,pre->data)删除pre，目的是方便递归更改节点的高度。
                AVLDelete(&((*T)->lchild), pre->data);
            }
            //当待删除结点*T左子树的高度小于或者等于右子树的高度时，用*T的后继结点post代替*T，
            //再将结点post从树中删除。这样可以保证删除结点后的树仍为二叉平衡树。
            else
            {
                //寻找后继节点post。
                post = (*T)->rchild;
                while (post->lchild)
                    post = post->lchild;
                //用post替换*T。
                (*T)->data = post->data;

                //删除节点post。
                //虽然能够确定post所属最小子树的根结点为&post，
                //但是不采用AVLDelete(&post,post->data)删除post，目的是方便递归更改节点的高度。
                AVLDelete(&((*T)->rchild), post->data);
            }
        }
        return true;
    }
    //在左子树中递归删除。
    else if (key < (*T)->data)
    {
        if (!AVLDelete(&((*T)->lchild), key))
            return false;
        else
        {
            //删除成功，修改树的高度。
            (*T)->height = max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;
            //已在*T的左子树删除结点key，判断是否需要进行旋转以保持二叉平衡树的特性。
            if (-2 == GetHeight((*T)->lchild) - GetHeight((*T)->rchild))
            {
                if (GetHeight((*T)->lchild->lchild) > GetHeight((*T)->lchild->rchild))
                {
                    LLRotate(T);
                }
                else
                {
                    LRRotate(T);
                }
            }
            return true;
        }
    }
    //在右子树中递归删除。
    else
    {
        if (!AVLDelete(&((*T)->rchild), key))
            return false;
        else
        {
            //删除成功，修改树的高度。
            (*T)->height = max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;
            //已在*T的右子树删除结点key，判断是否需要进行旋转以保持二叉平衡树的特性。
            if (2 == GetHeight((*T)->lchild) - GetHeight((*T)->rchild))
            {
                if (GetHeight((*T)->rchild->lchild) > GetHeight((*T)->rchild->rchild))
                {
                    RLRotate(T);
                }
                else
                {
                    RRRotate(T);
                }
            }
            return true;
        }
    }
}

/*
 * 当T的左子树的左子树上的节点使得T的平衡度为2时，以T为中心进行右旋。
 */
bool LLRotate(BiTree *T)
{
    BiTree lc;
    lc = (*T)->lchild;
    (*T)->lchild = lc->rchild;
    lc->rchild = (*T);

    //注意要更新结点的高度。整个树中只有*T的左子树和lc的右子树发生了变化，所以只需更改这两棵树的高度。
    (*T)->height = max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;
    lc->height = max(GetHeight(lc->lchild), GetHeight(lc->rchild)) + 1;

    *T = lc;
    return true;
}

/*
 * 当T的左子树的右子树上的节点使得T的平衡度为2时，
 * 先以T的左子树为中心进行左旋，再以T为中心进行右旋。
 */
bool LRRotate(BiTree *T)
{
    RRRotate(&((*T)->lchild));
    LLRotate(T);
    return true;
}

/*
 * 当T的右子树的左子树上的节点使得T的平衡度为-2时，
 * 先以T的右子树为中心进行右旋，再以T为中心进行左旋。
 */
bool RLRotate(BiTree *T)
{
    LLRotate(&((*T)->rchild));
    RRRotate(T);
    return true;
}

/*
 * 当T的右子树的右子树上的节点使得T的平衡度为-2时，以T为中心进行左旋。
 */
bool RRRotate(BiTree *T)
{
    BiTree rc;
    rc = (*T)->rchild;
    (*T)->rchild = rc->lchild;
    rc->lchild = (*T);

    //注意要更新结点的高度。整个树中只有*T的左子树和lc的右子树发生了变化，所以只需更改这两棵树的高度。
    (*T)->height = max(GetHeight((*T)->lchild), GetHeight((*T)->rchild)) + 1;
    rc->height = max(GetHeight(rc->lchild), GetHeight(rc->rchild)) + 1;

    *T = rc;
    return true;
}

/*
 * 当T=NULL ,即树为空树时，无法通过T->height获取树的高度0，所以要额外编写该函数。
 */
int GetHeight(BiTree T)
{
    if (T)
        return T->height;
    return 0;
}
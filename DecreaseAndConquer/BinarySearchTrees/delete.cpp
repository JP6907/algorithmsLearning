/*********************
 * 问题描述：
 * 二叉查找树删除
 * 
 * 例如：删除x节点
 * 若x没有子树，直接删除
 * 若有一个子树，把x从中去除，子树接代
 * 若有两个子树，将x与successor交换，再按照上面两点删除x
 */

Status DeleteBST(BiTree *T, KeyType key){
  //若二叉查找树T中存在关键字等于key的数据元素时，则删除该数据元素，并返回
  //TRUE；否则返回FALSE
  if(!T) 
    return false;	//不存在关键字等于key的数据元素
  else{
    if(key == T->data.key) { 	//  找到关键字等于key的数据元素
      return Delete(T);
    }
    else if(key < T->data.key)
      return DeleteBST(T->lchild, key);
    else
      return DeleteBST(T->rchild, key);
  }
}

Status Delete(BiTree *p){
  //该节点为叶子节点，直接删除
  BiTree *q, *s;
  if (!p->rchild && !p->lchild)
  {
      delete p;
      p = NULL;
  }
  else if(!p->rchild){	//右子树空则只需重接它的左子树
    q=p->lchild;
    p->data = p->lchild->data;
    p->lchild=p->lchild->lchild;
    p->rchild=p->lchild->rchild;

    delete q;
  }
  else if(!p->lchild){	//左子树空只需重接它的右子树
    q=p->rchild;
    p->data = p->rchild->data;
    p->lchild=p->rchild->lchild;
    p->rchild=p->rchild->rchild;

    delete q;  }
  else{	//左右子树均不空
    q=p; 
    s=p->lchild;
    while(s->rchild){ 
      q=s; 
      s=s->rchild;
    }	//转左，然后向右到尽头
    p->data = s->data;	//s指向被删结点的“前驱”
    if(q!=p)	
      q->rchild = s->lchild;	//重接*q的右子树
    else 
      q->lchild = s->lchild;	//重接*q的左子树
    delete s;
  }
  return true;
}
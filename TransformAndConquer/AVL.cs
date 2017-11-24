/*
问题描述：
平衡二叉树的各种应用
http://www.cnblogs.com/huangxincheng/archive/2012/07/22/2603956.html
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Diagnostics;

namespace DataStruct
{
class Program
{
    static void Main(string[] args)
    {
        AVLTree<int, int> avl = new AVLTree<int, int>();

        Dictionary<DateTime, int> dic = new Dictionary<DateTime, int>();

        AVLTree<DateTime, int> tree = new AVLTree<DateTime, int>();

        //500w
        for (int i = 1; i < 5000000; i++)
        {
            dic.Add(DateTime.Now.AddMinutes(i), i);

            tree.Add(DateTime.Now.AddMinutes(i), i);
        }

        //检索2012-7-30 4:00:00 到 2012-7-30 5:00:00的登陆人数
        var min = Convert.ToDateTime("2012/7/30 4:00:00");

        var max = Convert.ToDateTime("2012/7/30 5:00:00");

        var watch = Stopwatch.StartNew();

        var result1 = dic.Keys.Where(i = > i >= min && i <= max).Select(i = > dic[i]).ToList();

        watch.Stop();

        Console.WriteLine("字典查找耗费时间:{0}ms", watch.ElapsedMilliseconds);

        watch = Stopwatch.StartNew();

        var result2 = tree.SearchRange(min, max);

        watch.Stop();

        Console.WriteLine("平衡二叉树查找耗费时间:{0}ms", watch.ElapsedMilliseconds);
    }
}

#region 平衡二叉树节点
/// <summary>
/// 平衡二叉树节点
/// </summary>
/// <typeparam name="K"></typeparam>
/// <typeparam name="V"></typeparam>
public class AVLNode<K, V>
{
    /// <summary>
    /// 节点元素
    /// </summary>
  public
    K key;

    /// <summary>
    /// 增加一个高度信息
    /// </summary>
  public
    int height;

    /// <summary>
    /// 节点中的附加值
    /// </summary>
  public
    HashSet<V> attach = new HashSet<V>();

    /// <summary>
    /// 左节点
    /// </summary>
  public
    AVLNode<K, V> left;

    /// <summary>
    /// 右节点
    /// </summary>
  public
    AVLNode<K, V> right;

  public
    AVLNode() {}

  public
    AVLNode(K key, V value, AVLNode<K, V> left, AVLNode<K, V> right)
    {
        //KV键值对
        this.key = key;
        this.attach.Add(value);

        this.left = left;
        this.right = right;
    }
}
#endregion

public class AVLTree<K, V>
    where K : IComparable
{
  public
    AVLNode<K, V> node = null;

#region 添加操作
    /// <summary>
    /// 添加操作
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
  public
    void Add(K key, V value)
    {
        node = Add(key, value, node);
    }
#endregion

#region 添加操作
    /// <summary>
    /// 添加操作
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    /// <param name="tree"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> Add(K key, V value, AVLNode<K, V> tree)
    {
        if (tree == null)
            tree = new AVLNode<K, V>(key, value, null, null);

        //左子树
        if (key.CompareTo(tree.key) < 0)
        {
            tree.left = Add(key, value, tree.left);

            //如果说相差等于2就说明这棵树需要旋转了
            if (Height(tree.left) - Height(tree.right) == 2)
            {
                //说明此时是左左旋转
                if (key.CompareTo(tree.left.key) < 0)
                {
                    tree = RotateLL(tree);
                }
                else
                {
                    //属于左右旋转
                    tree = RotateLR(tree);
                }
            }
        }

        //右子树
        if (key.CompareTo(tree.key) > 0)
        {
            tree.right = Add(key, value, tree.right);

            if ((Height(tree.right) - Height(tree.left) == 2))
            {
                //此时是右右旋转
                if (key.CompareTo(tree.right.key) > 0)
                {
                    tree = RotateRR(tree);
                }
                else
                {
                    //属于右左旋转
                    tree = RotateRL(tree);
                }
            }
        }

        //将value追加到附加值中（也可对应重复元素）
        if (key.CompareTo(tree.key) == 0)
            tree.attach.Add(value);

        //计算高度
        tree.height = Math.Max(Height(tree.left), Height(tree.right)) + 1;

        return tree;
    }
#endregion

#region 计算当前节点的高度
    /// <summary>
    /// 计算当前节点的高度
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
  public
    int Height(AVLNode<K, V> node)
    {
        return node == null ? -1 : node.height;
    }
#endregion

#region 第一种：左左旋转（单旋转）
    /// <summary>
    /// 第一种：左左旋转（单旋转）
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> RotateLL(AVLNode<K, V> node)
    {
        //top：需要作为顶级节点的元素
        var top = node.left;

        //先截断当前节点的左孩子
        node.left = top.right;

        //将当前节点作为temp的右孩子
        top.right = node;

        //计算当前两个节点的高度
        node.height = Math.Max(Height(node.left), Height(node.right)) + 1;
        top.height = Math.Max(Height(top.left), Height(top.right)) + 1;

        return top;
    }
#endregion

#region 第二种：右右旋转（单旋转）
    /// <summary>
    /// 第二种：右右旋转（单旋转）
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> RotateRR(AVLNode<K, V> node)
    {
        //top：需要作为顶级节点的元素
        var top = node.right;

        //先截断当前节点的右孩子
        node.right = top.left;

        //将当前节点作为temp的右孩子
        top.left = node;

        //计算当前两个节点的高度
        node.height = Math.Max(Height(node.left), Height(node.right)) + 1;
        top.height = Math.Max(Height(top.left), Height(top.right)) + 1;

        return top;
    }
#endregion

#region 第三种：左右旋转（双旋转）
    /// <summary>
    /// 第三种：左右旋转（双旋转）
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> RotateLR(AVLNode<K, V> node)
    {
        //先进行RR旋转
        node.left = RotateRR(node.left);

        //再进行LL旋转
        return RotateLL(node);
    }
#endregion

#region 第四种：右左旋转（双旋转）
    /// <summary>
    /// 第四种：右左旋转（双旋转）
    /// </summary>
    /// <param name="node"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> RotateRL(AVLNode<K, V> node)
    {
        //执行左左旋转
        node.right = RotateLL(node.right);

        //再执行右右旋转
        return RotateRR(node);
    }
#endregion

#region 是否包含指定元素
    /// <summary>
    /// 是否包含指定元素
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
  public
    bool Contain(K key)
    {
        return Contain(key, node);
    }
#endregion

#region 是否包含指定元素
    /// <summary>
    /// 是否包含指定元素
    /// </summary>
    /// <param name="key"></param>
    /// <param name="tree"></param>
    /// <returns></returns>
  public
    bool Contain(K key, AVLNode<K, V> tree)
    {
        if (tree == null)
            return false;
        //左子树
        if (key.CompareTo(tree.key) < 0)
            return Contain(key, tree.left);

        //右子树
        if (key.CompareTo(tree.key) > 0)
            return Contain(key, tree.right);

        return true;
    }
#endregion

#region 树的指定范围查找
    /// <summary>
    /// 树的指定范围查找
    /// </summary>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
  public
    HashSet<V> SearchRange(K min, K max)
    {
        HashSet<V> hashSet = new HashSet<V>();

        hashSet = SearchRange(min, max, hashSet, node);

        return hashSet;
    }
#endregion

#region 树的指定范围查找
    /// <summary>
    /// 树的指定范围查找
    /// </summary>
    /// <param name="range1"></param>
    /// <param name="range2"></param>
    /// <param name="tree"></param>
    /// <returns></returns>
  public
    HashSet<V> SearchRange(K min, K max, HashSet<V> hashSet, AVLNode<K, V> tree)
    {
        if (tree == null)
            return hashSet;

        //遍历左子树（寻找下界）
        if (min.CompareTo(tree.key) < 0)
            SearchRange(min, max, hashSet, tree.left);

        //当前节点是否在选定范围内
        if (min.CompareTo(tree.key) <= 0 && max.CompareTo(tree.key) >= 0)
        {
            //等于这种情况
            foreach (var item in tree.attach)
                hashSet.Add(item);
        }

        //遍历右子树（两种情况：①:找min的下限 ②：必须在Max范围之内）
        if (min.CompareTo(tree.key) > 0 || max.CompareTo(tree.key) > 0)
            SearchRange(min, max, hashSet, tree.right);

        return hashSet;
    }
#endregion

#region 找到当前树的最小节点
    /// <summary>
    /// 找到当前树的最小节点
    /// </summary>
    /// <returns></returns>
  public
    AVLNode<K, V> FindMin()
    {
        return FindMin(node);
    }
#endregion

#region 找到当前树的最小节点
    /// <summary>
    /// 找到当前树的最小节点
    /// </summary>
    /// <param name="tree"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> FindMin(AVLNode<K, V> tree)
    {
        if (tree == null)
            return null;

        if (tree.left == null)
            return tree;

        return FindMin(tree.left);
    }
#endregion

#region 找到当前树的最大节点
    /// <summary>
    /// 找到当前树的最大节点
    /// </summary>
    /// <returns></returns>
  public
    AVLNode<K, V> FindMax()
    {
        return FindMin(node);
    }
#endregion

#region 找到当前树的最大节点
    /// <summary>
    /// 找到当前树的最大节点
    /// </summary>
    /// <param name="tree"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> FindMax(AVLNode<K, V> tree)
    {
        if (tree == null)
            return null;

        if (tree.right == null)
            return tree;

        return FindMax(tree.right);
    }
#endregion

#region 删除当前树中的节点
    /// <summary>
    /// 删除当前树中的节点
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
  public
    void Remove(K key, V value)
    {
        node = Remove(key, value, node);
    }
#endregion

#region 删除当前树中的节点
    /// <summary>
    /// 删除当前树中的节点
    /// </summary>
    /// <param name="key"></param>
    /// <param name="tree"></param>
    /// <returns></returns>
  public
    AVLNode<K, V> Remove(K key, V value, AVLNode<K, V> tree)
    {
        if (tree == null)
            return null;

        //左子树
        if (key.CompareTo(tree.key) < 0)
        {
            tree.left = Remove(key, value, tree.left);

            //如果说相差等于2就说明这棵树需要旋转了
            if (Height(tree.left) - Height(tree.right) == 2)
            {
                //说明此时是左左旋转
                if (key.CompareTo(tree.left.key) < 0)
                {
                    tree = RotateLL(tree);
                }
                else
                {
                    //属于左右旋转
                    tree = RotateLR(tree);
                }
            }
        }
        //右子树
        if (key.CompareTo(tree.key) > 0)
        {
            tree.right = Remove(key, value, tree.right);

            if ((Height(tree.right) - Height(tree.left) == 2))
            {
                //此时是右右旋转
                if (key.CompareTo(tree.right.key) > 0)
                {
                    tree = RotateRR(tree);
                }
                else
                {
                    //属于右左旋转
                    tree = RotateRL(tree);
                }
            }
        }
        /*相等的情况*/
        if (key.CompareTo(tree.key) == 0)
        {
            //判断里面的HashSet是否有多值
            if (tree.attach.Count > 1)
            {
                //实现惰性删除
                tree.attach.Remove(value);
            }
            else
            {
                //有两个孩子的情况
                if (tree.left != null && tree.right != null)
                {
                    //根据平衡二叉树的中顺遍历，需要找到”有子树“的最小节点
                    tree.key = FindMin(tree.right).key;

                    //删除右子树的指定元素
                    tree.right = Remove(tree.key, value, tree.right);
                }
                else
                {
                    //自减高度
                    tree = tree.left == null ? tree.right : tree.left;

                    //如果删除的是叶子节点直接返回
                    if (tree == null)
                        return null;
                }
            }
        }

        //统计高度
        tree.height = Math.Max(Height(tree.left), Height(tree.right)) + 1;

        return tree;
    }
#endregion
}
}
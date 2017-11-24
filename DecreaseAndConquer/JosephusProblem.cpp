
/***************************
 * 问题描述：设有n个人围坐在一个圆桌周围，现从第s个人开始报数，数到第m的人出列，
 * 然后从出列的下一个人重新开始报数，数到第m的人又出列，…，
 * 如此反复直到所有的人全部出列为止
 * 求出最后一个出列的人
 */
/******迭代josephus算法********/
#include <stdio.h>
int josephus(int n)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return (2 * josephus(n / 2) - 1);
    else
        return (2 * josephus((n - 1) / 2) + 1);
}

/**********改良后的josephus***********/
/***
 * b[]是数字n的二进制序列，例如40的二进制101000，从低位开始保存到b[]
 * k是b的位数
 */
int super_josephus(int b[], int k)
{
    int i, J = 1, ans;
    if (k == 1)
        ans = 1;
    else
    {
        for (i = k - 2; i >= 0; i--)
        {
            J = 2 * J + 2 * b[i] - 1;
        }
        ans = J;
    }
    return ans;
}
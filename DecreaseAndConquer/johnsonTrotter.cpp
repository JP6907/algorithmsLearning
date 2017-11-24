/***********************
 * 问题描述：
 * 对一个序列[1,2,3,4,....,n]
 * 进行全排序，并输出
 */

#include <stdio.h>
#define _swap(a, b) \
    {               \
        int t = a;  \
        a = b;      \
        b = t;      \
    }

void New_Permutation(int n)
{
    int lim = 1, i;
    int *list = new int[n], s = n - 2, dir = -1, j, temp = n - 2;
    for (i = 1; i < n; ++i)
        lim *= i, list[i - 1] = i;
    list[n - 1] = n;
    //copy( list, list+n, ostream_iterator<int>(cout," ") ),cout<<endl;
    for (i = 1; i <= lim; ++i)
    {
        for (j = 0; j < n - 1; ++j)
        {
            _swap(list[s], list[s + 1]);
            //copy( list, list+n, ostream_iterator<int>(cout," ") ),cout<<endl;
            s += dir;
        }
        s = i & 1 ? temp : 0;
        _swap(list[s], list[s + 1]);
        //copy( list, list+n, ostream_iterator<int>(cout," ") ),cout<<endl;
        s = temp - s;
        dir = -dir;
    }
    delete[] list;
}
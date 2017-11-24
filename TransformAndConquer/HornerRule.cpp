/* 霍纳算法实例 */
/**
 * 问题描述：
 * 假设有n＋2个实数a0，a1，…，an,和x的序列，
 * 要对多项式Pn(x)= anxn＋an－１xn－１＋…＋a１x＋a０求值，
 * 通过如下变换我们可以得到一种快得多的算法，
 * 即Pn(x)= anxn ＋an－１xn－１＋…＋a１x＋a０＝((…(((anx ＋an－１)x＋an－２)x+ an－3)…)x＋a1)x＋a０，
 * 这种求值的安排我们称为霍纳法则。
 */
#include <stdio.h>

long int 
horner(int coefficient[], int n, int x) //coefficient[]为待求多项式的系数数组，n为数组大小，x为多项式中未知数x的具体值
{                                       //注意：coefficient[0]存放系数a0，coefficient[1]存放系数a1，以此类推…
    int i;
    long int result;
    
    result = coefficient[n-1];
    for(i = 1; i <= n-1; i++)
    {
        result = result * x + coefficient[n-1-i];
    }

    return result;
}

int 
main(void)
{                               //Test
    long int p;
    int a[4] = {3, 2, 1, 1};
    p = horner(a, 4, 1);
    printf("polynomial x^3 + x^2 + 2x + 3 = %ld\n", p);
}
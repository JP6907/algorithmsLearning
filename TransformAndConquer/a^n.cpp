/**
 * 问题描述：
 * 更有效地计算a^n
 */

/**
 * 第一个从左往右的二进制幂乘，例如
 * 13=1101(2)
 * a^13=
 * 1    1       0       1
 * a    a^2*a   a^6     a^12*a
 */
int LeftRightBinaryExponentiation(int a, int b[])
{
    int product = a;
    for (int i = b.length - 1; i > 0; i--)
    {
        product = product * product;
        if (b[i] == 1)
            product *= a;
    }
    return product;
}

/**
 * 第二个从右往左的二进制幂乘，例如
 * 13=1102(2)
 * a^13=
 * 1    1   0   1
 * a^8  a^4 a^2 a
 * a^8  a^4     a
 * a^13
 */
int RightLeftBinaryExponentiation(int a, int b[])
{
    int term = a;
    int product;
    if (b[0] == 1)
        product = a;
    else
        product = 1;
    for (int i = 1; i < b.length; i++)
    {
        term *= term;
        if (b[i] == 1)
            product *= term;
    }
    return product;
}
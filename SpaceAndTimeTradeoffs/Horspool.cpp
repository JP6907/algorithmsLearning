/**
 * 问题描述：
 * Horspool字符串匹配算法
 * http://dsqiu.iteye.com/blog/1700312
 * 
 */
/*
  * implementation of Horspool
  * Author：Horspool
  */
#define WORD 26
int horspool(char *T, int lenT, char *P, int lenP)
{
    int d[WORD];
    int i, pos, j;

    for (i = 0; i != WORD; i++)
        d[i] = lenP;
    for (i = 0; i != (lenP - 1); i++)
        d[P[i] - 'A'] = lenP - i - 1;

    pos = 0;
    while (pos < (lenT - lenP))
    {
        j = lenP - 1;
        while (j >= 0 && T[pos + j] == P[j]) //matching
            j--;
        if (j == -1)
            return pos;
        else //not matched
            pos += d[T[pos + lenP - 1] - 'A'];
    }

    return -1;
}
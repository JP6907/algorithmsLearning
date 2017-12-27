/**
 * 问题描述：
 * KMP字符串匹配算法
 * http://dsqiu.iteye.com/blog/1700312
 * https://github.com/Mr-YangCheng/ForAndroidInterview/blob/master/data%20structure/%5B%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%5D%20KMP%E7%9A%84%E4%B8%80%E4%B8%AA%E7%AE%80%E5%8D%95%E8%A7%A3%E9%87%8A.md
 * https://www.cnblogs.com/zhangtianq/p/5839909.html
 */
/* *******************************************************************
    created:    2006/07/02
    filename:     KMP.cpp
    author:        李创
                 http://www.cppblog.com/converse/ 
                
                参考资料: 严蔚敏<<数据结构>>

    purpose:    KMP字符串匹配算法的演示
******************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_LEN_OF_STR 30 //  字符串的最大长度

typedef struct String //  这里需要的字符串数组,存放字符串及其长度
{
    char str[MAX_LEN_OF_STR]; //  字符数组
    int length;               //  字符串的实际长度
} String, *PString;

//  得到字符串的next数组
void GetNextArray(PString pstr, int next[])
{
    assert(NULL != pstr);
    assert(NULL != next);
    assert(pstr->length > 0);

    //  第一个字符的next值是-1,因为C中的数组是从0开始的
    next[0] = -1;
    for (int i = 0, j = -1; i < pstr->length - 1;)
    {
        //  i是主串的游标,j是模式串的游标
        //  这里的主串和模式串都是同一个字符串
        if (-1 == j ||                    //  如果模式串游标已经回退到第一个字符
            pstr->str[i] == pstr->str[j]) //  如果匹配成功
        {
            //  两个游标都向前走一步
            ++i;
            ++j;
            //  存放当前的next值为此时模式串的游标值
            next[i] = j;
        }
        else //  匹配不成功j就回退到上一个next值
        {
            j = next[j];
        }
    }
}

//  KMP字符串模式匹配算法
//  输入: S是主串,T是模式串,pos是S中的起始位置
//  输出: 如果匹配成功返回起始位置,否则返回-1
int KMP(PString S, PString T, int pos)
{
    assert(NULL != S);
    assert(NULL != T);
    assert(pos >= 0);
    assert(pos < S->length);

    if (S->length < T->length)
        return -1;

    printf(" 主串\t = %s\n ", S->str);
    printf(" 模式串\t = %s\n ", T->str);

    int *next = (int *)malloc(T->length * sizeof(int));
    //  得到模式串的next数组
    GetNextArray(T, next);

    int i, j;
    for (i = pos, j = 0; i < S->length && j < T->length;)
    {
        //  i是主串游标,j是模式串游标
        if (-1 == j ||              //  模式串游标已经回退到第一个位置
            S->str[i] == T->str[j]) //  当前字符匹配成功
        {
            //  满足以上两种情况时两个游标都要向前进一步
            ++i;
            ++j;
        }
        else //   匹配不成功,模式串游标回退到当前字符的next值
        {
            j = next[j];
        }
    }

    free(next);

    if (j >= T->length)
    {
        //  匹配成功
        return i - T->length;
    }
    else
    {
        //  匹配不成功
        return -1;
    }
}
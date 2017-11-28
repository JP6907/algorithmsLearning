/**
 * 问题描述：
 * Sunday字符串匹配算法
 * http://dsqiu.iteye.com/blog/1700312
 * 
 */
#include <iostream>
#include <cstring>
using namespace std;

int sunday(const char *src, const char *des)
{
    int len_s = strlen(src);
    int len_d = strlen(des);
    int next[26] = {0};
    for (int j = 0; j < 26; ++j)
        next[j] = len_d + 1;
    for (int j = 0; j < len_d; ++j)
        next[des[j] - 'a'] = len_d - j; //记录字符到最右段的最短距离+1
    //例如:des = "abcedfb"
    //next = {7 1 5 4 3 2 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8}
    int pos = 0;
    while (pos < (len_s - len_d + 1)) //末端对齐
    {
        int i = pos;
        int j;
        for (j = 0; j < len_d; ++j, ++i)
        {
            if (src[i] != des[j])
            {
                pos += next[src[pos + len_d] - 'a'];
                //不等于就跳跃,跳跃是核心
                break;
            }
        }
        if (j == len_d)
            return pos;
    }
    return -1;
}

int main()
{
    char src[] = "abcdacdaahfacabcdabcdeaa";
    char des[] = "abcde";
    cout << sunday(src, des) << endl;
    return 0;
}

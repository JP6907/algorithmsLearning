/**
 * 问题描述：
 * 斐波那契数列 动态规划
 * F(0)=0
 * F(1)=1
 * F(i)=F(i-1)+F(i-2) for i>=2
 */
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

#define N 100000000
long long num[N+1];                  // 全局变量，初始化为0
long long fib(unsigned i)
{
    if (i <= 1) return i;
    if(num[i] != 0) return num[i];   // 不为0时表明数据有更新, 返回先前缓存的结果
    num[i] = fib(i-1) + fib(i-2);    // 缓存结果
    return num[i];
}

int main()
{
    int m;
    while(cin>>m)
    {
        cout<<fib(m)<<endl;
        // memset(num, 0, sizeof(num));
    }
    return 0;
}
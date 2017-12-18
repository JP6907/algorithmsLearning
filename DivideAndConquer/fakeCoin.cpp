/**
 * 问题描述：
 * 假币问题（simple
 * 已知一堆硬币里有一枚假币，重量较轻，用较少的次数找出假币
 * 分三堆，比较一次，如果有较轻的一堆，就用较轻的那堆迭代
 * 如果没有，那就用第三堆迭代
 */
#include <stdio.h>
int Coin(int a[],int low,int high,int n)
{
	int num1,num2,num3,i;
	int add1=0,add2=0;
	
	if(n==1)
	{
		return low+1;
	}
		
	if(n%3==0)
	{
		num1=num2=n/3;
	}
		
	else
	{
		num1=num2=n/3+1;
	}
		
	num3=n-num1-num2;
	
	for(i=0;i<num1;i++)
	{
		add1=add1+a[low+i];
	}
		
	for(i=num1;i<num1+num2;i++)
	{
		add2=add2+a[low+i];
	}
		
	if(add1<add2)
	{
		return Coin(a,low,low+num1-1,num1);
	}
		
	else if(add1>add2)
	{
		return Coin(a,low+num1-1,low+num1+num2-1,num2);
	}
		
	else
	{
		return Coin(a,low+num1+num2,high,num3);
	}
}

int main()
{
	int a[100];
	int i,n,low,high,address;
	
	printf("Please input the counts of the coins：\n");
	scanf("%d",&n);
	
	low = 0;
	high = n-1;
	
	printf("Please input the weight of every coin: \n");
	for(i=0; i<n; ++i)
	{
		scanf("%d",&a[i]);
	}
	
	address=Coin(a,low,high,n);
    printf("The fake coin is %dnd\n",address+1);
    
    return 0;
}
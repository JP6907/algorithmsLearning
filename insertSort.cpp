#include <stdio.h>
int insert(int poker[], int card, int n) //把card插入前第0~n筆已排序好的資料
{
    int j = n;
    while (card < poker[j])
    {
        poker[j + 1] = poker[j];
        j--;
    }
    poker[j + 1] = card;
    return 0;
}

int insort(int poker[], int count) //排序第poker[1]到poker[count]筆資料
{
    int i;
    for (i = 2; i <= count; i++)
    {
        insert(poker, poker[i], i - 1);
    }
    printf("Numbers Sorted: ");
    for (i = 1; i <= count; i++)
    {
        printf("%d ", poker[i]);
    }
    printf("\n");
    return 0;
}

int main()
{
    int count;
    scanf("%d", &count);
    int poker[count];
    poker[0] = -1000000;
    int i;
    printf("Numbers to be sorted: "); //印出待排序數字
    for (i = 1; i <= count; i++)
    {
        scanf("%d", &poker[i]);
        printf("%d ", poker[i]);
    }
    printf("\n");
    insort(poker, count);
    return 0;
}
/**
 * 问题描述：
 * 快速排序
 * http://bubkoo.com/2014/01/12/sort-algorithm/quick-sort/
 */
#include <stdio.h>

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}
void quick_sort_recursive(int arr[], int start, int end)
{
    if (start >= end)
        return; // 這是為了防止宣告堆疊陣列時當機
    int mid = arr[end];
    int left = start, right = end - 1;
    while (left < right)
    {
        while (arr[left] < mid && left < right)
            left++;
        while (arr[right] >= mid && left < right)
            right--;
        swap(&arr[left], &arr[right]);
    }
    if (arr[left] >= arr[end])
        swap(&arr[left], &arr[end]);
    else
        left++;
    if (left)
        quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}
void quick_sort(int arr[], int len)
{
    quick_sort_recursive(arr, 0, len - 1);
}

// typedef struct _Range
// {
//     int start, end;
// } Range;
// Range new_Range(int s, int e)
// {
//     Range r;
//     r.start = s;
//     r.end = e;
//     return r;
// }
// void swap(int *x, int *y)
// {
//     int t = *x;
//     *x = *y;
//     *y = t;
// }
// void quick_sort(int arr[], const int len)
// {
//     if (len <= 0)
//         return; // 避免len等於負值時宣告堆疊陣列當機
//     // r[]模擬堆疊,p為數量,r[p++]為push,r[--p]為pop且取得元素
//     Range r[len];
//     int p = 0;
//     r[p++] = new_Range(0, len - 1);
//     while (p)
//     {
//         Range range = r[--p];
//         if (range.start >= range.end)
//             continue;
//         int mid = arr[range.end];
//         int left = range.start, right = range.end - 1;
//         while (left < right)
//         {
//             while (arr[left] < mid && left < right)
//                 left++;
//             while (arr[right] >= mid && left < right)
//                 right--;
//             swap(arr[left], arr[right]);
//         }
//         if (arr[left] >= arr[range.end])
//             swap(arr[left], arr[range.end]);
//         else
//             left++;
//         r[p++] = new_Range(range.start, left - 1);
//         r[p++] = new_Range(left + 1, range.end);
//     }
// }
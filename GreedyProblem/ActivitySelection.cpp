/**
 * 问题描述：
 * 活动选择问题
 * 给出当日活动表，开始时间、结束时间
 * 一段时间内只能有一个活动进行
 * 求所能安排的最大的活动个数
 */
// Activity_Selection.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
struct activity
{
    int s;
    int f;
};
struct activitySort : public std::binary_function<activity, activity, bool>
{
    bool operator()(const activity &a1, const activity &a2)
    {
        return a1.f < a2.f;
    }
};
struct activityPrint
{
    void operator()(activity a)
    {
        std::cout << "s = " << a.s << " , f = " << a.f << std::endl;
        ;
    }
};
/** 
* Description: find the max activity count in a particular time 
*              and print the result 
*@param a, un-sorted activity set; 
*/
void activity_selector(const std::vector<activity> &av)
{
    std::vector<activity> A;
    // create one copy since the parameter is const
    std::vector<activity> a(av);
    std::sort(a.begin(), a.end(), activitySort());
    A.push_back(a[0]);
    int j = 0;
    for (int i = 1; i < a.size(); i++)
    {
        if (a[i].s >= a[j].f)
        {
            A.push_back(a[i]);
            j = i;
        }
    }
    std::for_each(A.begin(), A.end(), activityPrint());
}
int _tmain(int argc, _TCHAR *argv[])
{
    //  Activity k[] = { {1,4}, {3,5}, {0,6}, {5,7}, {3,8}, {5,9}, {6,10}, {8,11}, {8,12}, {2,11}, {12, 14} };

    // un-sorted
    activity k[] = {{0, 6}, {1, 4}, {2, 11}, {3, 5}, {3, 8}, {5, 7}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {12, 14}};
    std::vector<activity> av(k, k + sizeof(k) / sizeof(k[0]));
    activity_selector(av);
    system("pause");

    return 0;
}
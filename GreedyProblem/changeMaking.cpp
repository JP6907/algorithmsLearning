/**
 * 问题描述：
 * 找零钱问题 Change-Making Problem
 * 给出硬币所有面额和需要换的钱，
 * 用最少数量的硬币去换
 */
#include <iostream>
#include<limits.h>
#define N 4
#define C 17
using namespace std;

// In this example we take the amount as 17, and a total of
// 4 denominations of coins

int main()
{
    // contains the coin denominations
    int coins[N] = {1, 2, 5, 10};

    // C[i] contains the minimum number of coins required
    // to form the sum i
    int amount[C + 1] = {0};

    for (int amt = 1; amt <= C; amt++)
    {
        amount[amt] = INT_MAX;
        int temp = INT_MAX;
        for (int c = 0; c < N; c++)
        {
            // if the value of the coin is less than the amount
            if (coins[c] <= amt)
            {
                // What is the other number of coins that will be used
                // if coins[c] is used in the solution for amount i
                int temp_amt = amount[amt - coins[c]] + 1;

                // choose the minimum number of coins that will be used
                // for the amount i

                if (temp_amt < temp)
                {
                    temp = temp_amt;
                    amount[amt] = temp;
                }
            }
        }
    }
    cout << amount[C] << endl;
    return 0;
}
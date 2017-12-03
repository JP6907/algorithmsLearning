/**
 * 问题描述：
 * 最长公共子序列问题
 * 例如：providence president
 * 最长公共子序列是 priden
 * 不需要连续
 * 
 */
#include "stdafx.h"
#include "string.h"
#include <iostream>
using namespace std;

// directions of LCS generation
enum decreaseDir
{
    kInit = 0,
    kLeft,
    kUp,
    kLeftUp
};

void LCS_Print(int **LCS_direction,
               char *pStr1, char *pStr2,
               size_t row, size_t col);

// Get the length of two strings' LCSs, and print one of the LCSs
// Input: pStr1         - the first string
//        pStr2         - the second string
// Output: the length of two strings' LCSs
int LCS(char *pStr1, char *pStr2)
{
    if (!pStr1 || !pStr2)
        return 0;

    size_t length1 = strlen(pStr1);
    size_t length2 = strlen(pStr2);
    if (!length1 || !length2)
        return 0;

    size_t i, j;

    // initiate the length matrix
    int **LCS_length;
    LCS_length = (int **)(new int[length1]);
    for (i = 0; i < length1; ++i)
        LCS_length[i] = (int *)new int[length2];

    for (i = 0; i < length1; ++i)
        for (j = 0; j < length2; ++j)
            LCS_length[i][j] = 0;

    // initiate the direction matrix
    int **LCS_direction;
    LCS_direction = (int **)(new int[length1]);
    for (i = 0; i < length1; ++i)
        LCS_direction[i] = (int *)new int[length2];

    for (i = 0; i < length1; ++i)
        for (j = 0; j < length2; ++j)
            LCS_direction[i][j] = kInit;

    for (i = 0; i < length1; ++i)
    {
        for (j = 0; j < length2; ++j)
        {
            //之前此处的代码有问题，现在订正如下：
            if (i == 0 || j == 0)
            {
                if (pStr1[i] == pStr2[j])
                {
                    LCS_length[i][j] = 1;
                    LCS_direction[i][j] = kLeftUp;
                }
                else
                {
                    if (i > 0)
                    {
                        LCS_length[i][j] = LCS_length[i - 1][j];
                        LCS_direction[i][j] = kUp;
                    }
                    if (j > 0)
                    {
                        LCS_length[i][j] = LCS_length[i][j - 1];
                        LCS_direction[i][j] = kLeft;
                    }
                }
            }
            // a char of LCS is found,
            // it comes from the left up entry in the direction matrix
            else if (pStr1[i] == pStr2[j])
            {
                LCS_length[i][j] = LCS_length[i - 1][j - 1] + 1;
                LCS_direction[i][j] = kLeftUp;
            }
            // it comes from the up entry in the direction matrix
            else if (LCS_length[i - 1][j] > LCS_length[i][j - 1])
            {
                LCS_length[i][j] = LCS_length[i - 1][j];
                LCS_direction[i][j] = kUp;
            }
            // it comes from the left entry in the direction matrix
            else
            {
                LCS_length[i][j] = LCS_length[i][j - 1];
                LCS_direction[i][j] = kLeft;
            }
        }
    }
    LCS_Print(LCS_direction, pStr1, pStr2, length1 - 1, length2 - 1); //调用下面的LCS_Pring 打印出所求子串。
    return LCS_length[length1 - 1][length2 - 1];                      //返回长度。
}

// Print a LCS for two strings
// Input: LCS_direction - a 2d matrix which records the direction of
//                        LCS generation
//        pStr1         - the first string
//        pStr2         - the second string
//        row           - the row index in the matrix LCS_direction
//        col           - the column index in the matrix LCS_direction
void LCS_Print(int **LCS_direction,
               char *pStr1, char *pStr2,
               size_t row, size_t col)
{
    if (pStr1 == NULL || pStr2 == NULL)
        return;

    size_t length1 = strlen(pStr1);
    size_t length2 = strlen(pStr2);

    if (length1 == 0 || length2 == 0 || !(row < length1 && col < length2))
        return;

    // kLeftUp implies a char in the LCS is found
    if (LCS_direction[row][col] == kLeftUp)
    {
        if (row > 0 && col > 0)
            LCS_Print(LCS_direction, pStr1, pStr2, row - 1, col - 1);

        // print the char
        printf("%c", pStr1[row]);
    }
    else if (LCS_direction[row][col] == kLeft)
    {
        // move to the left entry in the direction matrix
        if (col > 0)
            LCS_Print(LCS_direction, pStr1, pStr2, row, col - 1);
    }
    else if (LCS_direction[row][col] == kUp)
    {
        // move to the up entry in the direction matrix
        if (row > 0)
            LCS_Print(LCS_direction, pStr1, pStr2, row - 1, col);
    }
}

int _tmain(int argc, _TCHAR *argv[])
{
    char *pStr1 = "abcde";
    char *pStr2 = "acde";
    LCS(pStr1, pStr2);
    printf("\n");
    system("pause");
    return 0;
}
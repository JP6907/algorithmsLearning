/**
 * 问题描述：
 * 背包问题 （无界
 * 有一组物品，重量分别是是w1...wn，价值是v1...vn
 * 一个背包只能装W重量的东西
 * 求最有价值的背包装载
 * 
 * 显然，A(Y)满足：
 * A(0) = 0
 * A(Y) = max { A(Y - 1), { pj + A(Y - wj) | wj ≤ Y } }
 * 其中，pj为第j种物品的价格。
 */
/** 
 * 动态规划，背包问题。
 * 输入为：int n： 物品的种类数。 int[n] weight: 各件物品的重量。 int[n] value: 各种物品的价值。
 *        int W: 背包最大的装载重量。
 * 输出：V[n][b]的值， 最大的装载价值。 x[n] 各类物品的装载数量。
 * 
 * @author huangyongye
 *
 */

public class Bag {

    private int[][] V; // 备忘录，V[i][j] 表示只装前面的i种物品时，最大的装载价值
    private int[][] I; // 备忘录，I[i][j] 表示最后一个装载的物品的类别。

    /**
     * 
     * @param weight 各类物品的重量
     * @param value 各类物品的价值
     * @param b 最大的载重
     * @return
     */
    public int maxValue(int[] weight, int[] value, int b) {
        // 返回最大的装载价值
        int n = weight.length; // 物品的类别数量
        V = new int[n + 1][b + 1]; // 备忘录
        I = new int[n + 1][b + 1];
        /* 1.初始化 */
        for (int i = 0; i < n + 1; i++)
            V[i][0] = 0;
        for (int j = 0; j < b + 1; j++)
            V[0][j] = 0;

        /* 2.分割子问题，从小到大递推解决 */
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < b + 1; j++) {
                if (j < weight[i - 1]) { // 如果能装的重量小于物品的单个重量
                    V[i][j] = V[i - 1][j];
                    I[i][j] = I[i - 1][j];
                } else {
                    // 递推方程：V[i][j] = (/*不装i*/V[i-1][j] > /*装i*/V[i][j-weight[i-1]] + value[i-1]) ? 
                    //  V[i-1][j] : V[i][j-weight[i-1]] + value[i-1];
                    if (V[i - 1][j] > V[i][j - weight[i - 1]] + value[i - 1]) {
                        // 如果不装的话
                        V[i][j] = V[i - 1][j];
                        I[i][j] = V[i - 1][j];
                    } else {
                        // 否则装
                        V[i][j] = V[i][j - weight[i - 1]] + value[i - 1];
                        I[i][j] = i - 1;
                    }
                }
            }
        }
        int[] result = labels(I, weight, b);
        /* 3.构造解，输出选择结果 */
        for (int i : result) {
            System.out.print(i + " ");
        }
        return V[n][b];
    }

    /**
     * 返回装入的物品数量，构造解
     * @param I
     * @return
     */
    public int[] labels(int[][] I, int[] weight, int b) {
        int n = weight.length; // 物品的数量
        // 初始化
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = 0;
        }
        int y = b; // 总重量
        while (I[n][y] != 0) {
            int j = I[n][y]; // 最后放入的物品
            while (I[n][y] == j) {
                y = y - weight[j];
                result[j]++;
            }
        }
        return result;
    }

    public static void main(String[] args) {
        int[] weight = { 2, 3, 4, 7 };
        int[] value = { 1, 3, 5, 9 };
        int b = 10;
        Bag bt = new Bag();
        int result = bt.maxValue(weight, value, b);
        System.out.println("\nmax value is " + result);
    }
}
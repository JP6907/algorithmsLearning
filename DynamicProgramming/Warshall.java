/**
 * 问题描述：
 * Warshall算法求传递闭包
 * http://www.cnblogs.com/jmzz/archive/2011/07/01/2095158.html
 */

public class Warshall {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int[][] AdjMat = { { 0, 1, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 0, 0 }, { 1, 0, 1, 0 } };

        int[][] BiBao = Warshall(AdjMat);

        System.out.println("输出表达传递闭包的矩阵：\n");
        for (int i = 0; i < BiBao.length; i++) {
            for (int j = 0; j < BiBao.length; j++)
                System.out.print(BiBao[i][j] + "  ");
            System.out.println();
        }
    }

    public static int[][] Warshall(int[][] AdjMat) {
        //接受一个图的邻接矩阵为参数，返回表达它的传递闭包的矩阵
        int[][] Rresult = AdjMat; //初始结果R0
        int n = AdjMat.length;

        for (int k = 0; k < n; k++) //R0到Rn，做n步变换
        {
            int[][] Rtemp = new int[n][n]; //每循环一下求下次结果
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (Rresult[i][j] == 1)
                        Rtemp[i][j] = 1;
                    else if (Rresult[i][k] == 1 && Rresult[k][j] == 1)
                        Rtemp[i][j] = 1;
                    else
                        Rtemp[i][j] = 0;
                }
            Rresult = Rtemp;
        }

        return Rresult;
    }

}
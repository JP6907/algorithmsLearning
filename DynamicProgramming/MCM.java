/**
 * 问题描述：
 * 矩阵连乘 Matrix-Chain Multiplication
 * 给定n个矩阵：A1,A2,...,An，其中Ai与Ai+1是可乘的，i=1，2...，n-1。
 * 确定计算矩阵连乘积的计算次序，使得依此次序计算矩阵连乘积需要的数乘次数最少。
 * 输入数据为矩阵个数和每个矩阵规模，输出结果为计算矩阵连乘积的计算次序和最少数乘次数
 */
  
public class Matrix {  
    public static void MatrixChain(int[] p,int n, int[][] m, int[][] s) {  
     for (int i = 1; i <= n; i++) {  
         m[i][i] = 0;  
     }  
        for(int r = 2;r <= n; r++ ) {  
            for(int i = 1; i <= n-r+1; i++) {  
                int j = i+r-1;  
                m[i][j] = m[i+1][j] + p[i-1]*p[i]*p[j];  
                s[i][j] = i;  
                for(int k = i+1; k < j; k++) {  
                    int t = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];  
                    if(t < m[i][j]) {  
                        m[i][j] = t;  
                        s[i][j] = k;  
                    }  
                }  
            }  
        }  
    }  
  
    public static void Traceback(int i, int j, int[][] s) {  
        if(i == j) return;  
        Traceback(i,s[i][j],s);  
        Traceback(s[i][j] + 1,j,s);  
        System.out.println("Multiply    A" + i + "," + s[i][j] + "and A" + (s[i][j] + 1) + "," + j);  
    }  
  
    public static void main(String[] args) {  
        Matrix mc = new Matrix();  
        int n = 7;  
        int p[] = { 30, 35, 15, 5, 10, 20, 25 };  
        int m[][] = new int[n][n];  
        int s[][] = new int[n][n];  
        int l = p.length-1;  
        mc.MatrixChain(p, l,m, s);  
  
        for (int i = 1; i < n; i++) {  
            for (int j = 1; j < n; j++) {  
                System.out.print(m[i][j] + "\t");  
            }  
            System.out.println();  
        }  
        System.out.println();  
        for (int i = 1; i < n; i++) {  
            for (int j = 1; j < n; j++) {  
  
                System.out.print(s[i][j]+" ");  
            }  
            System.out.println();  
        }  
  
        mc.Traceback( 1, 6, s);  
    }  
}
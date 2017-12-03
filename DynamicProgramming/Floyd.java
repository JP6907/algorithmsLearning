/**
 * 问题描述：
 * Floyd算法求多源最短路径
 * http://www.cnblogs.com/jmzz/archive/2011/07/01/2095158.html
 * 
 *
 */

public class Floyd {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int[][] WeightMat = {
                {0,1000,3,1000},
                {2,0,1000,1000},
                {1000,7,0,1},
                {6,1000,1000,0}
        };
        int[][] Result = Floyd(WeightMat);
        
        System.out.println("输出表达完全最短路径的矩阵：\n");
        for(int i = 0;i < Result.length;i++)
        {
            for(int j = 0;j < Result.length;j++)
                System.out.print(Result[i][j] + "   ");
            System.out.println();
        }
                
    }
    
    public static int[][] Floyd(int[][] WeightMat){
        //接受一个图的权重矩阵，返回表达完全最短路径的矩阵
        int n = WeightMat.length;
        int[][] Result = WeightMat;
        
        for(int k = 0;k < n;k++)    //进行n次变换,每次加入第k个点
        {
            int[][] temp = new int[n][n];
            for(int i = 0;i < n;i++)
                for(int j = 0;j < n;j++)
                    temp[i][j] = min(Result[i][j],Result[i][k]+Result[k][j]);//加入第k个点后路径是否能缩短
            Result = temp;
        }
        
        return Result;
    }
    
    private static int min(int m,int n){
        if(m  < n)
            return m;
        return n;
    }

}
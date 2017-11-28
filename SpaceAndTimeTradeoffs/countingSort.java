/**
 * 问题描述：
 * 计数排序
 * 不进行比较的排序算法
 */
public class CountSortTest {  
    
      public static void main(String[] args) {  
            
          int [] A = {-1, 2, 0, 4, 3, 6, 5, 8, -2, 1, 3, 0, 3, 6, 5, 2};  
          int [] B = countSort2(A);  
          for(int index = 0; index < B.length; index++)  
              System.out.print(B[index] + "  ");  
          System.out.println();  
          countSort1(A);  
          for(int index = 0; index < A.length; index++)  
              System.out.print(A[index] + "  ");  
            
      }  
    //空间上有所改进的代码
      private static void countSort1(int [] A) {  
          int min = 0, max = 0;  
          int [] C = null;  
          for(int index = 0; index < A.length; index++) {  
              if(A[index] < min) {  
                  min = A[index];  
                  continue;  
              }  
              if(A[index] > max)   max = A[index];  
          }  
          C = new int[max - min + 1];  
          for(int index = 0; index < A.length; index++) {  
              C[A[index] - min]++;  
          }  
          int a = 0;  
          for(int index = 0; index < C.length; index++) {  
              for(int count = 0; count < C[index]; count++){  
                  A[a++] = index + min;  
              }  
          }  
      }  
    //原版代码
      private static int [] countSort2(int [] A) {  
          int min = 0, max = 0;  
          int [] C = null;  
          int [] B = new int[A.length];  
          for(int index = 0; index < A.length; index++) {  
              if(A[index] < min) {  
                  min = A[index];  
                  continue;  
              }  
              if(A[index] > max)   max = A[index];  
          }  
          C = new int[max - min + 1];  
          for(int index = 0; index < A.length; index++) {  
              C[A[index] - min]++;  
          }  
          for(int index = 1; index < C.length; index++){  
              C[index] = C[index] + C[index - 1];  
          }  
          for(int index = A.length - 1; index > -1; index--) {  
              B[C[A[index] - min] - 1] = A[index];  
              C[A[index] - min]--;  
          }  
          return B;  
      }  
  }  
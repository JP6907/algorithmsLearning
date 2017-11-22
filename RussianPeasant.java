import java.util.Scanner;


public class Algorithm_1 {


	/**
	 * 实现俄罗斯农夫法的乘法算法
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int m, n, flag,res;
		while (true) {
			m = sc.nextInt();
			n = sc.nextInt();
			flag = 0;res=0;
			if (m < 0) {
				m = 0 - m;
				flag = 1;
			}
			if (n < 0) {
				n = 0 - n;
				flag = 1 - flag;
			}
			while (m >= 1) {
				if ((m & 1) == 1) {// odd
					res+=n;
					m=(m-1)>>1;
					n=n<<1;
				}
				else{
					m=m>>1;
					n=n<<1;
				}
			}
			
			if(0 == flag){
				System.out.println("m × n = "+res);
			}else{
				System.out.println("m × n = -"+res);
			}
			
		}
	}
}
/*
 * 测试数据：
 * 输入：0 0 输出：0
 * 输入：13 18 输出：234
 * 输入：-13 18 输出：-234
 * 输入：13 -18 输出：-234
 * 输入：-13 -18 输出：234
 */
#include "queens_N.h"
using namespace std;
int main() {
	omp_set_num_threads(4);
	int N;
	do
	{
		printf("请输入N的值：");
		fflush(stdin);
		cin >> N;
		time_t start = time(NULL);
		printf("\n");
		if (N > 0)
		{
			if (N < 4 && N>1) {
				cout << N << "皇后:" << 0 << endl;
				break;
			}
			fflush(stdout);
			cout << N << "皇后:" << queens_Opti(N) << endl;
			cout << "计算时间：" << (time(NULL) - start) << endl;
			break;
		}
		else
		{
			printf("输入错误，请从新输入：");
			printf("\n\n");
			break;
		}

	} while (1);
	system("pause");
	return 0;
}
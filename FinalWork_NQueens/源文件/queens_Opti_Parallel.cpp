#include"queens_N.h"
#define THREADS 4
#define MAXBYTE 30
static int M;
unsigned long long total_Opti_Parallels[THREADS];
unsigned long long total_Opti_Parallel;
unsigned long long result2;
void countQueens_Para(int index, unsigned long *Available_Para,
	unsigned long *LDiagonal_Para, unsigned long *RDiagonal_Para,
	unsigned long *Column_Para);

long long queens_Opti_Parallel(int n) {
#pragma region 初始化
	omp_set_num_threads(THREADS);
	total_Opti_Parallel = result2 = 0;
	for (int i = 0; i < THREADS; i++) {
		total_Opti_Parallels[i] = 0;
	}
	M = n;
	unsigned long **LDiagonal_Para = new unsigned long *[THREADS];
	unsigned long **RDiagonal_Para = new unsigned long *[THREADS];
	unsigned long **Column_Para = new unsigned long *[THREADS];
	unsigned long **Available_Para = new unsigned long *[THREADS];
	for (int i = 0; i < THREADS; i++) {
		LDiagonal_Para[i] = new unsigned long[M];
		LDiagonal_Para[i][0] = 0;
	}
	for (int i = 0; i < THREADS; i++) {
		RDiagonal_Para[i] = new unsigned long[M];
		RDiagonal_Para[i][0] = 0;
	}
	for (int i = 0; i < THREADS; i++) {
		Column_Para[i] = new unsigned long[M];
		Column_Para[i][0] = 0;
	}
	for (int i = 0; i < THREADS; i++) {
		Available_Para[i] = new unsigned long[M];
		Available_Para[i][0] = pow(2, M / 2) - 1;
	}
#pragma endregion

#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < M / 2; i++) {
			unsigned long temp;
			temp = Available_Para[omp_get_thread_num()][0];														//temp记录
			Available_Para[omp_get_thread_num()][0] = Available_Para[omp_get_thread_num()][0] & ((int)pow(2, i));	//逐个找出对应的皇后
			countQueens_Para(0, Available_Para[omp_get_thread_num()], LDiagonal_Para[omp_get_thread_num()],		//计算皇后数
				RDiagonal_Para[omp_get_thread_num()], Column_Para[omp_get_thread_num()]);
			Available_Para[omp_get_thread_num()][0] = temp;														//temp还原
		}
	}
	for (int i = 0; i < THREADS; i++) {
		total_Opti_Parallel += total_Opti_Parallels[i] * 2;
	}
	if (M & 1 != 0) {																							//奇数情况
#pragma region 初始化
		result2 = 0;
		for (int i = 0; i < THREADS; i++) {
			total_Opti_Parallels[i] = 0;
		}
		for (int i = 0; i < THREADS; i++) {
			LDiagonal_Para[i] = new unsigned long[M];
			LDiagonal_Para[i][0] = 0;
			LDiagonal_Para[i][1] = pow(2, (M / 2) + 1);
		}
		for (int i = 0; i < THREADS; i++) {
			RDiagonal_Para[i] = new unsigned long[M];
			RDiagonal_Para[i][0] = 0;
			RDiagonal_Para[i][1] = pow(2, (M / 2) - 1);
		}
		for (int i = 0; i < THREADS; i++) {
			Column_Para[i] = new unsigned long[M];
			Column_Para[i][0] = 0;
			Column_Para[i][1] = pow(2, M / 2);
		}
		for (int i = 0; i < THREADS; i++) {
			Available_Para[i] = new unsigned long[M];
			Available_Para[i][0] = pow(2, M / 2);
			Available_Para[i][1] = pow(2, M / 2) - 1 - pow(2, (M / 2) - 1);
		}
#pragma endregion
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < M / 2 - 1; i++) {
				unsigned long temp;
				temp = Available_Para[omp_get_thread_num()][1];														//temp记录
				Available_Para[omp_get_thread_num()][1] = ((int)pow(2, i));	//逐个找出对应的皇后
				countQueens_Para(1, Available_Para[omp_get_thread_num()], LDiagonal_Para[omp_get_thread_num()],		//计算皇后数
					RDiagonal_Para[omp_get_thread_num()], Column_Para[omp_get_thread_num()]);
				Available_Para[omp_get_thread_num()][1] = temp;														//temp还原
			}
		}
		for (int i = 0; i < THREADS; i++) {
			result2 += total_Opti_Parallels[i] * 2;
		}
	}
	return total_Opti_Parallel + result2;
}

void countQueens_Para(int index, unsigned long *Available_Para,
	unsigned long *LDiagonal_Para, unsigned long *RDiagonal_Para,
	unsigned long *Column_Para) {

	while (Available_Para[index] != 0) {
		long newQueen = ~(Available_Para[index] - 1)&Available_Para[index];   //求新皇后放置的第一个位置
		Available_Para[index] = Available_Para[index] & (~newQueen);
		if (newQueen == 0)
			return;
		if (index == M - 1 && newQueen != 0) {
			total_Opti_Parallels[omp_get_thread_num()]++;
		}
		else
		{
			/*更新*/
			LDiagonal_Para[index + 1] = (LDiagonal_Para[index] | newQueen) << 1;
			RDiagonal_Para[index + 1] = (RDiagonal_Para[index] | newQueen) >> 1;
			Column_Para[index + 1] = Column_Para[index] | newQueen;
			Available_Para[index + 1] = (~(LDiagonal_Para[index + 1] | RDiagonal_Para[index + 1] | Column_Para[index + 1]))&((int)pow(2, M) - 1);
			countQueens_Para(index + 1, Available_Para, LDiagonal_Para, RDiagonal_Para, Column_Para);
		}
	}

}


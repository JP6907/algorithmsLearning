#include"queens_N.h"
#define THREADS 4
#define MAXBYTE 30
static int M;
unsigned __int64 total_Opti_Parallels[THREADS];
unsigned __int64 total_Opti_Parallel = 0;
void countQueens_Para(int index, unsigned __int32 *Allowed_Para,
	unsigned __int32 *LDForbid_Para, unsigned __int32 *RDForbid_Para,
	unsigned __int32 *ColForbid_Para);

__int64 queens_Opti_Parallel(int n) {
#pragma region 初始化
	memset(total_Opti_Parallels, 0, sizeof(unsigned __int64));
	M = n;
	unsigned __int32 **LDForbid_Para = new unsigned __int32 *[THREADS];
	unsigned __int32 **RDForbid_Para = new unsigned __int32 *[THREADS];
	unsigned __int32 **ColForbid_Para = new unsigned __int32 *[THREADS];
	unsigned __int32 **Allowed_Para = new unsigned __int32 *[THREADS];
	for (int i = 0; i < THREADS; i++) {
		LDForbid_Para[i] = new unsigned __int32[M];
		LDForbid_Para[i][0] = 0;
	}
	for (int i = 0; i < THREADS; i++) {
		RDForbid_Para[i] = new unsigned __int32[M];
		RDForbid_Para[i][0] = 0;
	}
	for (int i = 0; i < THREADS; i++) {
		ColForbid_Para[i] = new unsigned __int32[M];
		ColForbid_Para[i][0] = 0;
	}
	for (int i = 0; i < THREADS; i++) {
		Allowed_Para[i] = new unsigned __int32[M];
		Allowed_Para[i][0] = pow(2, M / 2) - 1;
	}
#pragma endregion

#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < M / 2; i++) {
			unsigned __int32 temp;
			temp = Allowed_Para[omp_get_thread_num()][0];														//temp记录
			Allowed_Para[omp_get_thread_num()][0] = Allowed_Para[omp_get_thread_num()][0] & ((int)pow(2, i));	//逐个找出对应的皇后
			countQueens_Para(0, Allowed_Para[omp_get_thread_num()], LDForbid_Para[omp_get_thread_num()],		//计算皇后数
				RDForbid_Para[omp_get_thread_num()], ColForbid_Para[omp_get_thread_num()]);
			Allowed_Para[omp_get_thread_num()][0] = temp;														//temp还原
		}

	}
	for (int i = 0; i < THREADS; i++) {
		total_Opti_Parallel += total_Opti_Parallels[i] * 2;
	}
	if (M & 1 != 0) {																							//奇数情况
#pragma region 初始化
		for (int i = 0; i < THREADS; i++) {
			total_Opti_Parallels[i] = 0;
		}
		for (int i = 0; i < THREADS; i++) {
			LDForbid_Para[i] = new unsigned __int32[M];
			LDForbid_Para[i][0] = 0;
			LDForbid_Para[i][1] = pow(2, (M / 2) + 1);
		}
		for (int i = 0; i < THREADS; i++) {
			RDForbid_Para[i] = new unsigned __int32[M];
			RDForbid_Para[i][0] = 0;
			RDForbid_Para[i][1] = pow(2, (M / 2) - 1);
		}
		for (int i = 0; i < THREADS; i++) {
			ColForbid_Para[i] = new unsigned __int32[M];
			ColForbid_Para[i][0] = 0;
			ColForbid_Para[i][1] = pow(2, M / 2);
		}
		for (int i = 0; i < THREADS; i++) {
			Allowed_Para[i] = new unsigned __int32[M];
			Allowed_Para[i][0] = pow(2, M / 2);
			Allowed_Para[i][1] = pow(2, M / 2) - 1 - pow(2, (M / 2) - 1);
		}
#pragma endregion
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < M / 2 - 1; i++) {
				unsigned __int32 temp;
				temp = Allowed_Para[omp_get_thread_num()][1];														//temp记录
				Allowed_Para[omp_get_thread_num()][1] =  ((int)pow(2, i));	//逐个找出对应的皇后
				countQueens_Para(1, Allowed_Para[omp_get_thread_num()], LDForbid_Para[omp_get_thread_num()],		//计算皇后数
					RDForbid_Para[omp_get_thread_num()], ColForbid_Para[omp_get_thread_num()]);
				Allowed_Para[omp_get_thread_num()][1] = temp;														//temp还原
			}
		}
		for (int i = 0; i < THREADS; i++) {
			total_Opti_Parallel += total_Opti_Parallels[i] * 2;
		}
	}
	return total_Opti_Parallel;
}

void countQueens_Para(int index, unsigned __int32 *Allowed_Para,
	unsigned __int32 *LDForbid_Para, unsigned __int32 *RDForbid_Para,
	unsigned __int32 *ColForbid_Para) {

	while (Allowed_Para[index] != 0) {
		__int32 newQueen = ~(Allowed_Para[index] - 1)&Allowed_Para[index];   //求新皇后放置的第一个位置
		Allowed_Para[index] = Allowed_Para[index] & (~newQueen);
		if (newQueen == 0)
			return;
		if (index == M - 1 && newQueen != 0) {
			total_Opti_Parallels[omp_get_thread_num()]++;
		}
		else
		{
			/*更新*/
			LDForbid_Para[index + 1] = (LDForbid_Para[index] | newQueen) << 1;
			RDForbid_Para[index + 1] = (RDForbid_Para[index] | newQueen) >> 1;
			ColForbid_Para[index + 1] = ColForbid_Para[index] | newQueen;
			Allowed_Para[index + 1] = (~(LDForbid_Para[index + 1] | RDForbid_Para[index + 1] | ColForbid_Para[index + 1]))&((int)pow(2, M) - 1);
			countQueens_Para(index + 1, Allowed_Para, LDForbid_Para, RDForbid_Para, ColForbid_Para);
		}
	}

}


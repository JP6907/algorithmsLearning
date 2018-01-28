#include"queens_N.h"
#define THREADS 4
#define MAXBYTE 30
static int M;
unsigned long long total_Optis[THREADS];
unsigned long long total_Opti;
unsigned long long result;

void countQueens(int index, unsigned long Available_Para,
	unsigned long LDiagonal_Para, unsigned long RDiagonal_Para,
	unsigned long Column_Para) {
	unsigned long LDiagonal_temp = 0, RDiagonal_temp = 0, Column_temp = 0, Available_temp = 0;

	while (Available_Para != 0) {
		long newQueen = ~(Available_Para - 1)&Available_Para;   //求新皇后放置的第一个位置
		Available_Para = Available_Para& (~newQueen);
		if (index == M - 1 && newQueen != 0) {
			total_Optis[omp_get_thread_num()]++;
		}
		else
		{
			/*更新*/
			LDiagonal_temp = (LDiagonal_Para | newQueen) << 1;
			RDiagonal_temp = (RDiagonal_Para | newQueen) >> 1;
			Column_temp = Column_Para | newQueen;
			Available_temp = (~(LDiagonal_temp | RDiagonal_temp | Column_temp))&((int)pow(2, M) - 1);
			countQueens(index + 1, Available_temp, LDiagonal_temp, RDiagonal_temp, Column_temp);
		}
	}

}



int mask = 1;
long long setQueens(long row, long leftshift, long rightshift, long long num)
{
	if (row != mask)
	{
		long position = mask & ~(row | leftshift | rightshift);
		while (position)
		{
			long differ = position & -position;
			position -= differ;
			num = setQueens(row + differ, (leftshift + differ) << 1, (rightshift + differ) >> 1, num);
		}
	}
	else
	{
		num++;
	}
	return num;
}
long long queens_Opti(int n) {
	total_Opti = result = 0;
	M = n;
	mask = (1 << n) - 1;
	int  m = n / 2;

	for (int i = 1; i <= m; i++) {
		long p;							//新位置
		long position = mask & ~(0 | 0 | 0);
		int j = i;
		while (j != 0) {
			p = position & -position;
			position -= p;
			j--;
		}
		result = setQueens(0 + p, (0 + p) << 1, (0 + p) >> 1, 0);
		result *= 2;
		total_Opti += result;
	}
	result = 0;
	if (M & 1 != 0) {	//奇数情况
		result = 0;
		for (int i = 0; i < THREADS; i++) {
			total_Optis[i] = 0;
		}

		for (int i = 0; i < M / 2 - 1; i++) {
			countQueens(1, ((int)pow(2, i)), (int)pow(2, (M / 2) + 1), (int)pow(2, (M / 2) - 1), (int)pow(2, M / 2));													//temp还原
		}
		for (int i = 0; i < THREADS; i++) {
			result += total_Optis[i] * 2;
		}
	}
	return total_Opti + result;
}

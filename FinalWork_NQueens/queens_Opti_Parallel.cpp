#include"queens_N.h"
static int M, mask = 1;
TYPERESULT total_Opti_Parallel;
TYPERESULT results = 0, result2;
TYPERESULT countQueens_Para(int index, long LDiagonal_Para, long RDiagonal_Para,
	long Column_Para);

TYPERESULT queens_Opti_Parallel(int n) {
	total_Opti_Parallel = results = result2 = 0;
	if (n >= 1 && n <= 2) return n & 1;
	M = n;
	mask = (1 << n) - 1;
#pragma omp parallel for reduction(+:results)
	for (int i = 0; i < M / 2; i++) {
		long temp = (1 << i)&mask;
		results += countQueens_Para(1, (0 | temp) << 1, (0 | temp >> 1), 0 | temp);
	}
	results = results * 2;
	total_Opti_Parallel += results;
	if (M & 1 != 0) {	//奇数情况
		result2 = 0;
#pragma omp parallel for reduction(+:result2)
		for (int i = 0; i < M / 2 - 1; i++) {
			long temp = (1 << i)&mask;
			result2 += countQueens_Para(2, ((1 << (M / 2) + 1) | temp) << 1,
				((1 << (M / 2) - 1) | temp) >> 1,
				((1 << (M / 2)) | temp));
		}
		result2 *= 2;
	}
	return total_Opti_Parallel + result2;
}

TYPERESULT countQueens_Para(int index, long LDiagonal_Para, long RDiagonal_Para, long Column_Para) {
	TYPERESULT num = 0;
	if (index != M) {
		long Available_Para = (~(LDiagonal_Para | RDiagonal_Para | Column_Para))&mask;
		while (Available_Para != 0) {
			long newQueen = -((signed)Available_Para)&Available_Para;   //求新皇后放置的第一个位置
			Available_Para &= ~newQueen;
			num += countQueens_Para(index + 1, (LDiagonal_Para | newQueen) << 1, (RDiagonal_Para | newQueen) >> 1, Column_Para | newQueen);
		}
	}
	else
	{
		num++;
	}
	return num;
}

#include "queens_N.h"

static int N;
unsigned __int64 total_Opti = 0;
unsigned __int32 *LDForbid;		//正对角  left
unsigned __int32 *RDForbid;		//反对角  right
unsigned __int32 *ColForbid;		//列      col
unsigned __int32 *Allowed;		//允许放置皇后点
void countQueens(int index);

__int64 queens_Opti(int n) {
	N = n;
	LDForbid = new unsigned __int32[N];
	RDForbid = new unsigned __int32[N];
	ColForbid = new unsigned __int32[N];
	Allowed = new unsigned __int32[N];
	LDForbid[0] = RDForbid[0] = ColForbid[0] = 0;
	Allowed[0] = pow(2, N / 2) - 1;
	countQueens(0);
	total_Opti *= 2;
	if (n & 1 != 0) {			//奇数情况
		Allowed[0] = pow(2, N / 2);
		countQueens(0);
	}
	return total_Opti;
}

void countQueens(int index) {
	while (Allowed[index] != 0) {
		__int32 newQueen = ~(Allowed[index] - 1)&Allowed[index];   //求新皇后放置的第一个位置
		Allowed[index] = Allowed[index] & (~newQueen);
		if (newQueen == 0)
			return;
		if (index == N - 1 && newQueen != 0) {
			total_Opti++;
		}
		else
		{
			/*更新*/
			LDForbid[index + 1] = (LDForbid[index] | newQueen) << 1;
			RDForbid[index + 1] = (RDForbid[index] | newQueen) >> 1;
			ColForbid[index + 1] = ColForbid[index] | newQueen;
			Allowed[index + 1] = (~(LDForbid[index + 1] | RDForbid[index + 1] | ColForbid[index + 1]))&((int)pow(2, N) - 1);
			countQueens(index + 1);
		}
	}

}
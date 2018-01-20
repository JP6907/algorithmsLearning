#include "queens_N.h"

static int N;
unsigned long long total_Opti = 0;
unsigned __int32 *LDiagonal;		//正对角  left
unsigned __int32 *RDiagonal;		//反对角  right
unsigned __int32 *Column;		//列      col
unsigned __int32 *Available;		//允许放置皇后点
void countQueens(int index);

long long queens_Opti(int n) {
	total_Opti = 0;
	N = n;
	LDiagonal = new unsigned __int32[N];
	RDiagonal = new unsigned __int32[N];
	Column = new unsigned __int32[N];
	Available = new unsigned __int32[N];
	LDiagonal[0] = RDiagonal[0] = Column[0] = 0;
	Available[0] = pow(2, N / 2) - 1;
	countQueens(0);
	total_Opti *= 2;
	if (n & 1 != 0) {			//奇数情况
		Available[0] = pow(2, N / 2);
		countQueens(0);
	}
	return total_Opti;
}

void countQueens(int index) {
	while (Available[index] != 0) {
		__int32 newQueen = ~(Available[index] - 1)&Available[index];   //求新皇后放置的第一个位置
		Available[index] = Available[index] & (~newQueen);
		if (newQueen == 0)
			return;
		if (index == N - 1 && newQueen != 0) {
			total_Opti++;
		}
		else
		{
			/*更新*/
			LDiagonal[index + 1] = (LDiagonal[index] | newQueen) << 1;
			RDiagonal[index + 1] = (RDiagonal[index] | newQueen) >> 1;
			Column[index + 1] = Column[index] | newQueen;
			Available[index + 1] = (~(LDiagonal[index + 1] | RDiagonal[index + 1] | Column[index + 1]))&((int)pow(2, N) - 1);
			countQueens(index + 1);
		}
	}

}
#define BOARDSIZE 30
#include <iostream>
__int64 total = 0;
static int N;
bool markboard(bool* b, int row, int col) {
	for (int i = row; i < N; ++i) {
		*(b + i*N + col) = true;
	}
	for (int i = row + 1, j = col - 1; i < N && j >= 0; ++i, --j)
		*(b + i*N + j) = true;
	for (int i = row + 1, j = col + 1; i < N && j < N; ++i, ++j)
		*(b + i*N + j) = true;
	return true;
}
void IsQuerePos(bool* board, int idx) {

	bool *b = new bool[BOARDSIZE*BOARDSIZE];
	for (int i = 0; i < N; ++i) {
		if (*(board + idx*N + i))
			continue;
		if (idx == N - 1) {
			total++;
		}
		else {
			memcpy(b, board, sizeof(bool)* BOARDSIZE*BOARDSIZE);
			markboard(b, idx, i);
			IsQuerePos(b, idx + 1);
		}
	}
	delete b;
}
__int64 queens_Normal(int n) {
	N = n;
	bool *board = new bool[BOARDSIZE*BOARDSIZE];
	bool *p = board;
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++)
			*p++ = false;
	}
	IsQuerePos(board, 0);
	delete board;
	return total;
}

#include "queens_N.h"
using namespace std;
int main() {
	int Number;
	cout << "input the Number:" << endl;
	cin >> Number;
	double start = omp_get_wtime();
	cout << Number << " Queens:" << queens_Opti_Parallel(Number) << endl;
	double end = omp_get_wtime();
	cout << "calculate time:" << end - start << "s" << endl;
	return 1;
}
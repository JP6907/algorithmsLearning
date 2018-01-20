#include "queens_N.h"
using namespace std;
long long queens_Opti_Parallel(int n);
int main() {
	int Number;
	cout << "Start" << endl;
	//for (int i = 16; i < 21; i++) {
		cout << "请输入Number的值：" << endl;
		cin >> Number;
		//Number = i;
		time_t start = time(NULL);
		cout << Number << " Queens:" << queens_Opti_Parallel(Number) << endl;
		time_t end = time(NULL);
		cout << "calculate time:" << end - start << "s" << endl;
	//}
		system("pause");
	return 1;
}
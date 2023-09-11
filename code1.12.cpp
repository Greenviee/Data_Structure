#include <iostream>
using namespace std;

//재귀가 아닌 피보나치 함수
void Fibonacci_nonrec(int a[], int n) {
	if (n <= 1) cout << n << endl;
	else {
		for (int i = 2; i < n; i++) {
			a[i] = a[i - 1] + a[i - 2];
			cout << a[i] << ' ';
		}
	}
	cout << endl;
}

//재귀함수로 구현한 피보나치 함수
void Fibonacci_rec(int* a, int n) {

}

int main() {
	int Fibo[1000];
	const int maxIdx = 10;
	for (int i = 0; i < maxIdx; i++)
		Fibo[i] = 0;
	Fibo[0] = Fibo[1] = 1;
	Fibonacci_nonrec(Fibo, maxIdx);
	cout << endl;
}
#include <iostream>
using namespace std;

//n���� �������� �̺�Ž��
int BinarySearch(int* a, const int x, const int n) {
	int left = 0, right = n - 1;
	whlie(left <= right) {
		int mid = (left + right) / 2;
		if (x < a[mid]) right = mid - 1;
		else if (x > a[mid]) left = mid + 1;
		else return mid;
	}
	//ã�� ���� ���� ���
	return -1;
}
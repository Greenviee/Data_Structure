#include <iostream>
using namespace std;

//이분탐색 재귀
int BinarySearch(int *a, const int x, const int left, const int right) {
	if (left <= right) {
		int mid = (left + right) / 2;
		if (x < a[mid]) return BinarySearch(a, x, left, mid - 1);
		else if (x > a[mid]) return BinarySearch(a, x, mid + 1, right);
		else return mid;
	}
	//찾는 값이 없는 경우
	return -1;
}

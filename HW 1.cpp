#include <iostream>
using namespace std;

class Matrix;

//�� �� ǥ���ϴ� Ŭ���� 
//(coef, exp) = (���, ����), ������ �� �׺��� ���� 
class Term {
	friend Matrix;
private:
	float coef;
	int exp;
}

class Matrix {
private:
	int rows, cols;
	static Term* termElement;
};

#include <iostream>
#include "time.h"
#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
//행렬 A, B의 지수(exponent)는 각 항별로 같다.
#define EXP 3
using namespace std;

class Matrix;

class Term {
private:
	float coef;
	int exp;
public:
	friend Matrix;
	Term() { }
	Term(float coef, int exp) : coef(coef), exp(exp) { }
	Term operator+(Term& b) {
		return Term(coef + b.coef, exp);
	}
};

class Matrix {
private:
	int rows, cols;
	static Term* TermElement;
	static int free;
	int start, finish;
	int terms;
public:
	Matrix(int r, int c) : rows(r), cols(c) {
		start = finish = terms = 0;
	}
	int get_data();
	int show_data();
	Matrix& addMatrix(Matrix&);
};

int Matrix::get_data() {
	start = free;
	terms = rows * cols;
	finish = start + terms;
	free += finish;
	for (int i = start; i < finish; i++) {
		TermElement[i].coef = rand() % 20;
		TermElement[i].exp = EXP;
	}
	return 1;
}

int Matrix::show_data() {
	cout << endl;
	for (int i = start; i < finish; i++) {
		if ((i - start) % cols == 0)
			cout << endl;
		cout << TermElement[i].coef << "x" << TermElement[i].exp << "  ";
	}
	cout << endl;
	return 1;
}

Matrix& Matrix::addMatrix(Matrix& b) {
	if (rows != b.rows || cols != b.cols) cout << "Incompatible Matrices" << endl;
	Matrix d(rows, cols);
	d.get_data();
	for (int i = 0; i < terms; i++) {
		TermElement[i + d.start] = TermElement[i + start] + TermElement[i + b.start];
	}
	return d;
}

int Matrix::free = 0;
Term* Matrix::TermElement = new Term[100];

int main(void)	{
	Matrix matrixA(AROWS, ACOLS);
	Matrix matrixB(AROWS, ACOLS);
	Matrix matrixC(AROWS, ACOLS);
	srand(time(NULL));
	matrixA.get_data();
	cout << "Matrix A: " << endl;
	matrixA.show_data();
	matrixB.get_data();
	cout << "Matrix B: " << endl;
	matrixB.show_data();
	matrixC = matrixA.addMatrix(matrixB);
	cout << " Matrix C: " << endl;
	matrixC.show_data();

	system("pause");

	return 0;
}
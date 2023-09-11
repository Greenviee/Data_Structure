#include <iostream>
#include <stdlib.h>
using namespace std;

class Matrix {
	int rows, cols;
	int* Term;
public:
	Matrix(int row, int col);
	int GetData();
	Matrix Transpose();
	int Display();
	Matrix Multiply(Matrix b);
	Matrix Add(Matrix b);
	Matrix Sub(Matrix b);
	Matrix Multiply2(Matrix b);
	int CompareRowCol(Matrix b);
	friend ostream& operator<<(ostream&, const Matrix&);
};

ostream& operator<<(ostream& os, const Matrix& mat) {
	os << "OK" << endl;
	return os;
}

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{
	Term = new int[rows * cols];
}

int Matrix::GetData() {
	int input_value;
	cout << "rows = " << rows << " cols = " << cols << endl;
	for (int j = 0; j < rows * cols; j++) {
		cout << "term value = ";
		cin >> input_value;
		cout << ' ' << endl;
		Term[j] = input_value;
	}
	return 0;
}

//행과 열을 바꾸는 함수
Matrix Matrix::Transpose() {
	Matrix b(cols, rows);

	int n = rows * cols;
	for (int i = 0; i < cols; i++) {
		//구현
	}
	cout << endl;
	return b;
}

//행렬 곱
Matrix Matrix::Multiply(Matrix b) {
	//곱셈 조건 만족 여부
	if (cols != b.rows) cout << "Incompatible matrices" << endl;
	Matrix d(rows, b.cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < b.cols; j++) {
			//구현
		}
	}
	return d;
}

//행렬 합
Matrix Matrix::Add(Matrix b) {
	//합 조건 만족 여부
	if (cols != b.cols || rows != b.rows) cout << "Incompatible matrices" << endl;

	Matrix d(rows, cols);
	int n = rows * cols;
	for (int i = 0; i < n; i++) {
		d.Term[i] = Term[i] + b.Term[i];
	}
	return d;
}

//행렬 차
Matrix Matrix::Sub(Matrix b) {
	//뺄셈 조건 만족 여부
	if (cols != b.cols || rows != b.rows) cout << "Incompatible matrices" << endl;

	Matrix d(rows, cols);
	int n = rows * cols;
	for (int i = 0; i < n; i++) {
		d.Term[i] = Term[i] - b.Term[i];
	}
	return d;
}

//??
Matrix Matrix::Multiply2(Matrix b) {
	if (cols != b.rows) cout << "Incompatible matrices" << endl;
	Matrix bXpose = b.Transpose();
	Matrix d(rows, b.cols);
	return d;
}

int Matrix::CompareRowCol(Matrix b) {
	if (cols != b.rows) return 1;
	else return 0;
}

int Matrix::Display() {
	int n;
	n = rows * cols;
	for (int i = 0; i < n; i++) {
		cout << Term[i] << ' ';
		if (i % cols == 0) cout << endl;
	}
	return 0;
}

int main() {
	Matrix a(2, 3);
	Matrix b(3, 4);
	Matrix c(2, 4);
	Matrix d(2, 4);
	Matrix t(4, 3);
	cout << "Enter first matrix: " << endl;
	a.GetData();
	cout << "Enter second matrix: " << endl;
	b.GetData();
	cout << "Display first matrix: " << endl;
	a.Display();
	cout << "Display second matrix: " << endl;
	b.Display();
	t = b.Transpose();
	cout << "Transpose() of Matrix b" << endl;
	t.Display();

	if (a.CompareRowCol(b))
		cout << "Error" << endl;
	c = a.Multiply(b);
	cout << "Multiply of Matrix a, b" << endl;
	cout << c;
	d = c.Sub(d);
	cout << d;
	cout << "using transpose()" << endl;
	t = b.Transpose();
	c = a.Multiply2(t);
	cout << c;
	system("pause");
}
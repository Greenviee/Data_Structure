#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
using namespace std;

class Matrix {
	int rows, cols;
	int* data;
public:
	Matrix(int rows, int cols);
	void get_data();
	void show_data();
	int sort_data();
	Matrix& addMatrix(Matrix&);
	//void addMatrix(Matrix&);
	void MultiplyMatrix(Matrix&, Matrix&);
};

Matrix::Matrix(int row, int col) : rows(row), cols(col) 
{
	data = new int[rows * cols];
}

void Matrix::get_data() {
	for (int i = 0; i < rows * cols; i++) {
		data[i] = rand() % 10;
	}
}

Matrix& Matrix::addMatrix(Matrix& b) {
	if (rows != b.rows || cols != b.cols) cout << "ERROR" << endl;
	Matrix d(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		d.data[i] = data[i] + b.data[i];
	return d;
}

/*
void Matrix::addMatrix(Matrix& b) {
	if (rows != b.rows || cols != b.cols) cout << "ERROR" << endl;
	for (int i = 0; i < rows * cols; i++)
		data[i] += b.data[i];
}
*/

Matrix& Matrix::MultiplyMatrix() {
	//연습 
}


//랜덤 값으로 행렬 값 채우기
void Matrix::show_data() {
	for (int i = 0; i < rows * cols; i++) {
		cout << data[i] << ' ';
		if (i % cols == cols - 1) cout << endl;
	}
	cout << endl;
}

int main() {
	Matrix matrixA(3, 4);
	Matrix matrixA1(3, 4);
	Matrix matrixB(4, 5);
	Matrix matrixC(3, 5);

	srand(time(NULL));
	matrixA.get_data();
	matrixA1.get_data();
	matrixB.get_data();
	cout << "A" << endl;
	matrixA.show_data();
	cout << "A1" << endl;
	matrixA1.show_data();
	cout << "B" << endl;
	matrixB.show_data();

	Matrix d = matrixA.addMatrix(matrixA1);
	cout << "addMatrix" << endl;
	d.show_data();
	system("pause");
	return 0;
}

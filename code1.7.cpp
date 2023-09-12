#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
using namespace std;

class Matrix {
	int rows, cols;
	static int* data;
	static int free;
	int start, finish, terms;
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
	terms = rows * cols;
	start = free;
	finish = start + terms - 1;
	free = finish + 1;
}

void Matrix::get_data() {
	for (int i = start; i <= finish ; i++) {
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
	//���� 
}

int Matrix::free = 0;
int* Matrix::data = new int[100];


//���� ������ ��� �� ä���
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

	system("pause");
	return 0;
}

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
	Matrix addMatrix(Matrix&);
	Matrix MultiplyMatrix(Matrix&);
};

int Matrix::free = 0;
int* Matrix::data = new int[100];

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

Matrix Matrix::addMatrix(Matrix& b) {
	if (rows != b.rows || cols != b.cols) cout << "ERROR" << endl;
	Matrix d(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		d.data[i] = data[i] + b.data[i];
	return d;
}

Matrix Matrix::MultiplyMatrix(Matrix& b) {
	if(cols != b.rows) cout << "ERROR" << endl;
	Matrix c(rows, b.cols);
	for (int i = 0; i < rows * b.cols; i++) {
		//Ç× À§Ä¡ (x, y)
		int x = i % cols;
		int y = i / cols;
		for(int j = 0; j < cols; j++) {
			c.data[i] += data[cols * y + j] + b.data[x + cols * j];
		} 
	}
	return c;
}



void Matrix::show_data() {
	for (int i = start; i <= finish; i++) {
		cout << data[i] << ' ';
		if (i % cols == cols - 1) cout << endl;
	}
	cout << endl;
}

int main() {
	Matrix matrixA(3, 4);
	Matrix matrixA1(3, 4);
	Matrix matrixA2(3, 4);
	Matrix matrixB(4, 5);
	Matrix matrixC(3, 5);

	srand(time(NULL));
	
	matrixA.get_data();
	matrixA1.get_data();
	matrixA2 = matrixA.addMatrix(matrixA1);
	matrixC = matrixA.MultiplyMatrix(matrixB);
	cout<<"matrixA: "<<endl;
	matrixA.show_data();
	cout<<"matrixA1: "<<endl;
	matrixA1.show_data();
	cout<<"matrixA2: "<<endl;
	matrixA2.show_data();
	cout<<"matrixB: "<<endl;
	matrixB.show_data();
	cout<<"matrixC: "<<endl;
	matrixC.show_data();

	return 0;
}

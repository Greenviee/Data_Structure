#include <iostream>
using namespace std;

class Matrix;

//각 항 표현하는 클래스 
//(coef, exp) = (계수, 지수), 지수는 각 항별로 동일 
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

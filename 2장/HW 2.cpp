//소스 코드2.5: Polynomial 클래스를 사용하여 구현
//template으로 구현하고 +, -, *, <<, >> operator를 사용한 버젼으로 구현한다.

#include <iostream>

using namespace std;
template <class T> class Polynomial;

template <class T> class Term
{
	friend Polynomial<T>;
private:
	T coef;
	int exp;
};

template <class T> class Polynomial {
public:
	Polynomial();
	//construct the polynomial p(x) = 0;
	Polynomial Add(Polynomial);
	Polynomial operator + (Polynomial&);
	Polynomial operator - (Polynomial&);
	Polynomial operator * (Polynomial&);

	float Eval(float f);
	//evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeff, const int theExp);
	friend ostream& operator <<(ostream&, Polynomial&);//P(x)=5x^3+3x^1 형태로 출력, 계수가 0이면 해당항은 출력하지 않음
	friend istream& operator >>(istream&, Polynomial&);
private:
	static Term<T>* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};
template <class T>
Polynomial<T>::Polynomial()
{
	start = -1;
	finish = -1;
	terms = 0;
}

template <class T>
void Polynomial<T>::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term<T>* temp = new Term<T>[capacity];
		copy(termArray, termArray + free, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
}


template <class T> int Polynomial<T>::capacity = 100;
template <class T> Term<T>* Polynomial<T>::termArray = new Term<T>[100];
template <class T> int Polynomial<T>::free = 0;

int main(void) {
	int choice;
	Polynomial<int> P1, P2, P3, P4;
	cout << "다항식 출력 예제 : P(x)=5x^3+3x^1, P(x)=5x^3+3x^1\n";
	cout << "다항식 P1 입력: " << endl;
	cin >> P1;
	cout << "다항식 P2 입력: " << endl;
	cin >> P2;

	while (1) {
		cout << "\n****** 메뉴선택 ******" << endl;
		cout << "1: 덧셈, 2: 뺄셈, 3: 곱셈, 4. EValuate, 5. Exit" << endl;
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\n--------------- Addition ---------------\n";
			P3 = P1 + P2;
			cout << P1 << P2 << P3;
			cout << "----------------------------------------\n";
			break;
		case 2:
			cout << "\n------------- Substraction -------------\n";
			P3 = P1 - P2;
			cout << P1 << P2 << P3;
			cout << "----------------------------------------\n";
			break;
		case 3:
			cout << "\n----------- Multiplication -------------\n";
			P4 = P1 * P2;
			cout << P1 << P2 << P4;
			cout << "----------------------------------------\n";
			break;
		//eval(x) : 다항식에 x를 대입했을 때의 결과 
		case 4: 
			int result = P4.Eval(3);
			cout << P4;
			cout << "result = " << result;
			break;
		case 0:
			cout << "Good Bye...!!!" << endl;
			exit(0);
		}
	}
	system("pause");
	return 0;
}

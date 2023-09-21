//�ҽ� �ڵ�2.5: Polynomial Ŭ������ ����Ͽ� ����
//template���� �����ϰ� +, -, *, <<, >> operator�� ����� �������� �����Ѵ�.

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
	friend ostream& operator <<(ostream&, Polynomial&);//P(x)=5x^3+3x^1 ���·� ���, ����� 0�̸� �ش����� ������� ����
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
	cout << "���׽� ��� ���� : P(x)=5x^3+3x^1, P(x)=5x^3+3x^1\n";
	cout << "���׽� P1 �Է�: " << endl;
	cin >> P1;
	cout << "���׽� P2 �Է�: " << endl;
	cin >> P2;

	while (1) {
		cout << "\n****** �޴����� ******" << endl;
		cout << "1: ����, 2: ����, 3: ����, 4. EValuate, 5. Exit" << endl;
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
		//eval(x) : ���׽Ŀ� x�� �������� ���� ��� 
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

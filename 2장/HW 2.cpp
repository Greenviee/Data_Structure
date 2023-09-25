//�ҽ� �ڵ�2.5: Polynomial Ŭ������ ����Ͽ� ����
//template���� �����ϰ� +, -, *, <<, >> operator�� ����� �������� �����Ѵ�.

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <class T> class Polynomial;

template <class T> class Term
{
	Term operator+ (Term&);
	Term operator- (Term&);
	//*= -1
	Term reverse();
	friend Polynomial<T>;
	friend ostream& operator<<(ostream&, Polynomial<T>&);
	friend istream& operator>>(istream&, Polynomial<T>&);

private:
	T coef;
	int exp;
};

template <class T>
Term<T> Term<T>::operator+ (Term& b) {
	if (exp != b.exp) cout << "Add Error" << endl;
	Term<T> d = Term();
	d.coef = coef + b.coef;
	d.exp = exp;
	return d;
}

template <class T>
Term<T> Term<T>::operator- (Term& b) {
	if (exp != b.exp) cout << "Subtract Error" << endl;
	Term<T> d = Term();
	d.coef = coef - b.coef;
	d.exp = exp;
	return d;
}

template <class T>
Term<T> Term<T>::reverse() {
	Term<T> d = Term();
	d.coef = coef * -1;
	d.exp = exp;
	return d;
}

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
	//P(x)=5x^3+3x^1 ���·� ���, ����� 0�̸� �ش����� ������� ����
	friend ostream& operator<<(ostream& o, Polynomial& p)
	{
		o << "P(x)=";
		for (int i = p.start; i <= p.finish; i++) {
			if (termArray[i].coef >= 0) o << '+';
			o << termArray[i].coef << "x^" << termArray[i].exp;
		}
		return o;
	}
	friend istream& operator>>(istream& i, Polynomial& p)
	{
		p.start = p.finish = free;
		T c; int e;
		i >> c >> e;
		termArray[p.finish].coef = c;
		termArray[p.finish].exp = e;
		p.finish++;
		free = p.finish;
		p.finish--;
		return i;
	}
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
Polynomial<T> Polynomial<T>::Add(Polynomial)
{

}

template <class T>
Polynomial<T> Polynomial<T>::operator+(Polynomial& b)
{
	Polynomial<T> d = Polynomial<T>();
	d.start = d.finish = free;
	//j = ���� ������ ���� b�� �� �� �ְ�����
	int j = b.start;
	for (int i = start; i <= finish; i++) {
		//b�� ������ �� ū ��� d�� �߰�
		while (termArray[j].exp > termArray[i].exp && j <= b.finish) {
			termArray[d.finish] = termArray[j];
			j++;
			d.finish++;
		}
		//a�� b�� ������ ���� ��� ���ؼ� d�� �߰�
		if (j <= b.finish && termArray[j].exp == termArray[i].exp) {
			termArray[d.finish] = termArray[i] + termArray[j];
			j++;
			d.finish++;
		}
		//�ƴ� ���
		else {
			termArray[d.finish] = termArray[i];
			d.finish++;
		}
	}
	//b�� �� �� ������ ���� �� �߰�
	while (j <= b.finish) {
		termArray[d.finish] = termArray[j];
		j++;
		d.finish++;
	}
	free = d.finish;
	d.finish--;
	return d;
}

template <class T>
Polynomial<T> Polynomial<T>::operator-(Polynomial& b)
{
	Polynomial<T> d = Polynomial<T>();
	d.start = d.finish = free;
	//j = ���� ���� ���� b�� �� �� �ְ�����
	int j = b.start;
	for (int i = start; i <= finish; i++) {
		//b�� ������ �� ū ��� d�� �߰�
		while (termArray[j].exp > termArray[i].exp && j <= b.finish) {
			termArray[d.finish] = termArray[j].reverse();
			j++;
			d.finish++;
		}
		//a�� b�� ������ ���� ��� ���� d�� �߰�
		if (j <= b.finish && termArray[j].exp == termArray[i].exp) {
			termArray[d.finish] = termArray[i] - termArray[j];
			j++;
			d.finish++;
		}
		//�ƴ� ���
		else {
			termArray[d.finish] = termArray[i];
			d.finish++;
		}
	}
	//b�� �� �� ������ ���� �� �߰�
	while (j <= b.finish) {
		termArray[d.finish] = termArray[j].reverse();
		j++;
		d.finish++;
	}
	free = d.finish;
	d.finish--;
	return d;
}

template <class T>
float Polynomial<T>::Eval(float f) {

}

template <class T>
Polynomial<T> Polynomial<T>::operator*(Polynomial& b)
{
	Polynomial<T> d = Polynomial<T>();
	d.start = d.finish = free;
	return d;
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
		cout << "1: ����, 2: ����, 3: ����, 4. Evaluate, 5. Exit" << endl;
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\n--------------- Addition ---------------\n";
			P3 = P1 + P2;
			cout << P1 << P2 << P3;
			cout << "\n----------------------------------------\n";
			break;
		case 2:
			cout << "\n------------- Substraction -------------\n";
			P3 = P1 - P2;
			cout << P1 << P2 << P3;
			cout << "\n----------------------------------------\n";
			break;
		case 3:
			cout << "\n----------- Multiplication -------------\n";
			P4 = P1 * P2;
			cout << P1 << P2 << P4;
			cout << "\n----------------------------------------\n";
			break;
		case 5:
			cout << "Good Bye...!!!" << endl;
			exit(0);
		default:
			cout << "Error" << endl;
		}
	}
	system("pause");
	return 0;
}

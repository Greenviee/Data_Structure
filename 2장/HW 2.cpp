//소스 코드2.5: Polynomial 클래스를 사용하여 구현
//template으로 구현하고 +, -, *, <<, >> operator를 사용한 버젼으로 구현한다.

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "time.h"
using namespace std;

template <class T> class Polynomial;

template <class T> class Term
{
	Term operator+ (Term&);
	Term operator- (Term&);
	Term operator* (Term&);
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
Term<T> Term<T>::operator* (Term& b) {
	Term<T> d = Term();
	d.coef = coef * b.coef;
	d.exp = exp + b.exp;
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
	//P(x)=5x^3+3x^1 형태로 출력, 계수가 0이면 해당항은 출력하지 않음
	friend ostream& operator<<(ostream& o, Polynomial& p)
	{
		o << "P(x) = ";
		for (int i = p.start; i <= p.finish; i++) {
			if (termArray[i].coef >= 0 && i != p.start) o << '+';
			if (termArray[i].exp == 0) 
			    o << termArray[i].coef;
			else
			    o << termArray[i].coef << "x^" << termArray[i].exp;
		}
		o << endl;
		return o;
	}
	friend istream& operator>>(istream& i, Polynomial& p)
	{
		//항의 개수는 1~5개 중 랜덤, 항의 지수는 0 ~ 10, 계수는 1 ~ 10 사이 랜덤
		//cnt : 항 개수
		int cnt = rand() % 5 + 1;
		p.start = free; p.finish = free + cnt - 1;
		p.terms = cnt;
		int exps[cnt];
		for (int i = 0; i < cnt; i++) {
		    exps[i] = rand() % 11;
		    //지수 중복검사
		    for (int j = 0; j < i; j++) {
		        if (exps[i] == exps[j]) {
		            i--;
		            break;
		        }
		    }
		}
		sort(exps, exps + cnt, greater<int>());
		for (int i = 0; i < cnt; i++) {
		    termArray[p.start + i].exp = exps[i];
		    termArray[p.start + i].coef = rand() % 10 + 1;
		}
		free += cnt;
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
Polynomial<T> Polynomial<T>::Add(Polynomial b)
{
	Polynomial<T> d = Polynomial<T>();
	d.start = d.finish = free;
	//j = 아직 더하지 않은 b의 항 중 최고차항
	int j = b.start;
	for (int i = start; i <= finish; i++) {
		//b의 지수가 더 큰 경우 d에 추가
		while (termArray[j].exp > termArray[i].exp && j <= b.finish) {
			termArray[d.finish] = termArray[j];
			j++;
			d.finish++;
		}
		//a랑 b의 지수가 같은 경우 합해서 d에 추가
		if (j <= b.finish && termArray[j].exp == termArray[i].exp) {
			termArray[d.finish] = termArray[i] + termArray[j];
			j++;
			d.finish++;
		}
		//아닐 경우
		else {
			termArray[d.finish] = termArray[i];
			d.finish++;
		}
	}
	//b의 항 중 더하지 않은 항 추가
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
Polynomial<T> Polynomial<T>::operator+(Polynomial& b)
{
	Polynomial<T> d = Polynomial<T>();
	d.start = d.finish = free;
	//j = 아직 더하지 않은 b의 항 중 최고차항
	int j = b.start;
	for (int i = start; i <= finish; i++) {
		//b의 지수가 더 큰 경우 d에 추가
		while (termArray[j].exp > termArray[i].exp && j <= b.finish) {
			termArray[d.finish] = termArray[j];
			j++;
			d.finish++;
		}
		//a랑 b의 지수가 같은 경우 합해서 d에 추가
		if (j <= b.finish && termArray[j].exp == termArray[i].exp) {
			termArray[d.finish] = termArray[i] + termArray[j];
			j++;
			d.finish++;
		}
		//아닐 경우
		else {
			termArray[d.finish] = termArray[i];
			d.finish++;
		}
	}
	//b의 항 중 더하지 않은 항 추가
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
	//j = 아직 빼지 않은 b의 항 중 최고차항
	int j = b.start;
	for (int i = start; i <= finish; i++) {
		//b의 지수가 더 큰 경우 d에 추가
		while (termArray[j].exp > termArray[i].exp && j <= b.finish) {
			termArray[d.finish] = termArray[j].reverse();
			j++;
			d.finish++;
		}
		//a랑 b의 지수가 같은 경우 빼서 d에 추가
		if (j <= b.finish && termArray[j].exp == termArray[i].exp) {
			termArray[d.finish] = termArray[i] - termArray[j];
			j++;
			d.finish++;
		}
		//아닐 경우
		else {
			termArray[d.finish] = termArray[i];
			d.finish++;
		}
	}
	//b의 항 중 더하지 않은 항 추가
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
	float ret = 0;
	for (int i = start; i <= finish; i++) {
		ret += termArray[i].coef * pow(f, (float)termArray[i].exp);
	}
	return ret;
}

template <class T>
Polynomial<T> Polynomial<T>::operator*(Polynomial& b)
{
	Polynomial<T> d = Polynomial<T>();
	Polynomial<T> p[terms];
	for (int i = 0; i < terms; i++) {
	    p[i].start = free; p[i].finish = free + b.terms - 1;
	    free += b.terms;
	    for (int j = 0; j < b.terms; j++) 
	        termArray[p[i].start + j] = termArray[start + i] * termArray[b.start + j];
	    if (i == 0) d = p[i];
	    else d = d + p[i];
	}
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


template <class T> int Polynomial<T>::capacity = 200;
template <class T> Term<T>* Polynomial<T>::termArray = new Term<T>[200];
template <class T> int Polynomial<T>::free = 0;

int main(void) {
    srand(time(NULL));
	int choice;
	Polynomial<int> P1, P2, P3, P4;
	cout << "다항식 출력 예제 : P(x)=5x^3+3x^1, P(x)=5x^3+3x^1\n";
	cin >> P1;
	cin >> P2;
	
	float n, result;
	while (1) {
		cout << "\n****** 메뉴선택 ******" << endl;
		cout << "1: 덧셈, 2: 뺄셈, 3: 곱셈, 4. Evaluate, 5. Exit" << endl;
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
		case 4:
			cout << "Put Value : ";
			cin >> n;
			result = P1.Eval(n);
			cout << P1 << endl;
			cout << "result = " << result;
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

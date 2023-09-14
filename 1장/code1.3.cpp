#include <iostream>
using namespace std;

class Employee {
	int eno;
	string ename;
	float salary;
	string dept;
	static int count; //객체가 생성될 때마다 count++
public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator=(const Employee&);
	int operator++();
	static int Show(); //count값 초기화
	friend ostream& operator << (ostream& stream, Employee&);
};

int main() {
	Employee sd1;
	Employee sd2(10);
	Employee sd3(sd2);
	Employee::Show();
	sd1.Show();
	Employee sd4 = sd2;
	sd3 = sd2;
	cout << endl;
	cout << sd4;
	system("pause");
}

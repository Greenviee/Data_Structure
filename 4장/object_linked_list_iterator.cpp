/*
3�ܰ�-��ü ���� ����Ʈ�� iterator ����
*/
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	friend class ListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee*)const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {
	os << "No: " << emp.eno << " Name: " << emp.ename << " Salary: " << emp.salary << endl;
	return os;
}
bool Employee::operator==(Employee& emp) {
	if (eno == emp.eno && ename == emp.ename && salary == emp.salary)
		return true;
	return false;
}
bool Employee::operator<(Employee& emp) {
	if (stoi(eno) < stoi(emp.eno))
		return true;
	return false;
}
char Employee::compare(const Employee* emp) const {
	if (stoi(eno) < stoi(emp->eno))
		return '<';
	else if (stoi(eno) > stoi(emp->eno))
		return '>';
	else {
		if (ename < emp->ename)
			return '>';
		else if (ename < emp->ename)
			return '<';
		else {
			if (salary < emp->salary)
				return '<';
			else if (salary > emp->salary)
				return '>';
			else return '=';
		}
	}
}
class Node {
	friend class ListIterator;
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node() {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};
class ListIterator;
class LinkedList {
	friend class ListIterator;
	Node* first;
public:
	LinkedList() {
		first = nullptr;
	}
	bool Delete(string);
	void Show();
	void Add(Employee);//sno�� ���ĵǵ��� ����
	bool Search(string);
	LinkedList& operator+(LinkedList&);
};
class ListIterator {
public:
	ListIterator(const LinkedList& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++(); //Next()
	ListIterator operator ++(int);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee* GetCurrent();
private:
	Node* current; //pointer to nodes
	const LinkedList& list;//existing list
};
ListIterator::ListIterator(const LinkedList& lst) : list(lst), current(lst.first) {
	cout << "List Iterator is constructed" << endl;
}
void LinkedList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* p = first;
	while (p != nullptr) {
		cout << p->data;
		p = p->link;
	}
}
void LinkedList::Add(Employee element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);
	Node* p = first, * q = nullptr;
	if (p == nullptr) {
		first = newNode;
		return;
	}
	while (p != nullptr) {
		if (element < p->data) {
			if (p == first) {
				newNode->link = p;
				first = newNode;
				return;
			}
			newNode->link = p;
			q->link = newNode;
			return;
		}
		q = p;
		p = p->link;
	}
	q->link = newNode;
	return;
}
bool LinkedList::Search(string eno) { // sno�� ���� ���ڵ带 ã��
	Node* p = first;
	while (p != nullptr) {
		if (p->data.ename == eno)
			return true;
		p = p->link;
	}
	return false;
}
bool LinkedList::Delete(string eno) // delete the element
{
	Node* p = first, * q = nullptr;
	while (p != nullptr) {
		if (p->data.eno == eno) {
			if (p == first) {
				first = p->link;
				delete p;
				return true;
			}
			q->link = p->link;
			delete p;
			return true;
		}
		q = p;
		p = p->link;
	}
	return false;
}
LinkedList& LinkedList::operator+(LinkedList& lb) {
	LinkedList lc;
	Node* a = first, * b = lb.first;
	while (a != nullptr && b != nullptr) {
		if (a->data < b->data) {
			lc.Add(a->data);
			a = a->link;
		}
		else {
			lc.Add(b->data);
			b = b->link;
		}
	}
	while (a != nullptr) {
		lc.Add(a->data);
		a = a->link;
	}
	while (b != nullptr) {
		lc.Add(b->data);
		b = b->link;
	}
	return lc;
}

bool ListIterator::NotNull() {
	if (current != nullptr)
		return true;
	return false;
}
bool ListIterator::NextNotNull() {
	if (current->link != nullptr)
		return true;
	return false;
}
Employee* ListIterator::First() {
	return &list.first->data;
}
Employee* ListIterator::Next() {
	current = current->link;
	Employee* e = &current->data;
	return e;
}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

ListIterator::~ListIterator() {
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->()const {
	return &current->data;
}

ListIterator& ListIterator::operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator ++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::operator != (const ListIterator right) const {
	return current != right.current;
}

bool ListIterator::operator == (const ListIterator right) const {
	return current == right.current;
}

int sum(const LinkedList& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return 0; //����Ʈ�� ����ִ� ���
	int ret = 0;
	while (li.NotNull()) {
		ret += li.GetCurrent()->getSalary();
		li++;
	}
	return ret;
}

double avg(const LinkedList& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return 0; //����Ʈ�� ����ִ� ���
	int sum = 0, n = 0;
	while (li.NotNull()) {
		sum += li.GetCurrent()->getSalary();
		n++;
		li++;
	}
	double ret = (double)sum / (double)n;
	return ret;
}

int min(const LinkedList& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return 0; //����Ʈ�� ����ִ� ���
	int min = 987654321;
	while (li.NotNull()) {
		int salary = li.GetCurrent()->getSalary();
		if (salary < min)
			min = salary;
		li++;
	}
	return min;
}

int max(const LinkedList& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return 0; //����Ʈ�� ����ִ� ���
	int max = 0;
	while (li.NotNull()) {
		int salary = li.GetCurrent()->getSalary();
		if (salary > max)
			max = salary;
		li++;
	}
	return max;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

int main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	LinkedList la, lb, lc;
	do {
		cout << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit" << endl << "����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			la.Add(*data);
			break;
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(*data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "���� �Ϸ�";
			break;
		case Show:
			cout << "����Ʈ la = ";
			la.Show();
			cout << "����Ʈ lb = ";
			lb.Show();
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�." << endl;
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�." << endl;
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = ";
			lc.Show();
			break;
		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


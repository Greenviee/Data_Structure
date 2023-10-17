/*
2�ܰ�- ��ü ���� ����Ʈ: �ܼ��� linked list���� insert�� �ø��������� ���ĵǵ��� ó��, delete�ϴ� �˰����� �ڵ�
*/
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	string eno;
	string ename;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
};
ostream& operator<<(ostream& os, Employee& emp) {
	os << "No: " << emp.eno << " Name: " << emp.ename << endl;
	return os;
}
bool Employee::operator==(Employee& emp) {
	if (eno == emp.eno && ename == emp.ename)
		return true;
	return false;
}
bool Employee::operator<(Employee& emp) {
	if (stoi(eno) < stoi(emp.eno))
		return true;
	return false;
}
class Node {
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class LinkedList {
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
enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};

void main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	LinkedList la, lb, lc;
	Employee* data;
	do {
		cout << "0.Add0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit" << endl << "����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			la.Add(*data);
			break;
		case Add2:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			lb.Add(*data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "���� �Ϸ�" << endl;
			break;
		case Show:
			cout << "����Ʈ la: " << endl;
			la.Show();
			cout << "����Ʈ lb: " << endl;
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

		case Exit: // ���� ��� ����
			cout << "Exit" << endl;
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


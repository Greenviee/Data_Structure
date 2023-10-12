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
	bool operator<(Employee& e) {
		if (stoi(eno) < stoi(e.eno)) return true;
		return false;
	}
	bool operator==(Employee& e) {
		if (eno == e.eno && ename == e.ename) return true;
		return false;
	}
};

ostream& operator<<(ostream& os, Employee& e) {
	os << "No: " << e.eno << " Name: " << e.ename << endl;
	return os;
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
	bool operator>(Employee);
	bool operator==(Employee);
};
void LinkedList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* p = first;
	if (first == nullptr) {
		cout << "Empty List" << endl;
		return;
	}
	while (p != nullptr) {
		cout << p->data;
		p = p->link;
	}
	cout << endl;
}
void LinkedList::Add(Employee element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);
	if (first == nullptr) { //linked list�� ����ִ� ���
		first = newNode;
		return;
	}
	Node* p = first;
	if (element < p->data) {
		newNode->link = p;
		first = newNode;
	}
	else {
		while (p->link != nullptr) {
			if (element < p->link->data) {
				newNode->link = p->link;
				p->link = newNode;
				return;
			}
			else p = p->link;
		}
		p->link = newNode;
	}
}
bool LinkedList::Search(string eno) { // sno�� ���� ���ڵ带 ã��
	Node* p = first;
	while (p != nullptr) {
		if (p->data.eno == eno) return true;
		p = p->link;
	}
	return false;
}
bool LinkedList::Delete(string eno) // delete the element
{
	Node* p = first;
	Node* prev = nullptr;
	while (p != nullptr) {
		if (p->data.eno == eno) {
			if (prev == nullptr) { //������ ��尡 ù��° ����� ���
				first = p->link;
			}
			else {
				prev->link = p->link;
			}
			delete p;
			return true;
		}
		prev = p;
		p = p->link;
	}
	return false;// ������ ����� ����.
}

enum Enum {
	Add, Delete, Show, Search, Exit
};

int main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	Employee data;
	bool result = false;
	srand(time(NULL));
	LinkedList* l = new LinkedList();
	do {
		cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. Exit" << endl << "����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = Employee(eno, ename);
			l->Add(data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = l->Delete(eno);
			if (result)
				cout << "���� �Ϸ�" << endl;
			break;
		case Show:
			l->Show();
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = l->Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�." << endl;
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�." << endl;
			break;
		case Exit: // ���� ��� ����
			cout << "Exit" << endl;
			exit(1);
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


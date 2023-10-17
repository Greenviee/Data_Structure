/*
2단계- 객체 연결 리스트: 단순한 linked list에서 insert는 올림차순으로 정렬되도록 처리, delete하는 알고리즘을 코딩
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
	void Add(Employee);//sno로 정렬되도록 구현
	bool Search(string);
	LinkedList& operator+(LinkedList&);
};
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;
	while (p != nullptr) {
		cout << p->data;
		p = p->link;
	}
}
void LinkedList::Add(Employee element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
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
bool LinkedList::Search(string eno) { // sno를 갖는 레코드를 찾기
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
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	LinkedList la, lb, lc;
	Employee* data;
	do {
		cout << "0.Add0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit" << endl << "선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			la.Add(*data);
			break;
		case Add2:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			lb.Add(*data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "삭제 완료" << endl;
			break;
		case Show:
			cout << "리스트 la: " << endl;
			la.Show();
			cout << "리스트 lb: " << endl;
			lb.Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			break;

		case Exit: // 꼬리 노드 삭제
			cout << "Exit" << endl;
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


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
	void Add(Employee);//sno로 정렬되도록 구현
	bool Search(string);
	bool operator>(Employee);
	bool operator==(Employee);
};
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
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
void LinkedList::Add(Employee element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);
	if (first == nullptr) { //linked list가 비어있는 경우
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
bool LinkedList::Search(string eno) { // sno를 갖는 레코드를 찾기
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
			if (prev == nullptr) { //삭제할 노드가 첫번째 노드인 경우
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
	return false;// 삭제할 대상이 없다.
}

enum Enum {
	Add, Delete, Show, Search, Exit
};

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	Employee data;
	bool result = false;
	srand(time(NULL));
	LinkedList* l = new LinkedList();
	do {
		cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. Exit" << endl << "선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = Employee(eno, ename);
			l->Add(data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = l->Delete(eno);
			if (result)
				cout << "삭제 완료" << endl;
			break;
		case Show:
			l->Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = l->Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
			break;
		case Exit: // 꼬리 노드 삭제
			cout << "Exit" << endl;
			exit(1);
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


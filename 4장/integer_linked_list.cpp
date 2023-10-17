/*
1단계-정수 연결 리스트: 단순한 linked list에서 add, delete하는 알고리즘을 코딩
*/
#include <iostream>
#include <time.h>
using namespace std;

class Node {
	friend class LinkedList;
	int data;
	Node* link;
public:
	Node(int element) {
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
	bool Delete(int);
	void Show();
	void Add(int element);//정렬되도록 구현
	bool Search(int data);
	LinkedList& operator+(LinkedList&);
};
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;
	if (p == nullptr) {
		cout << "Empty List" << endl;
		return;
	}
	while (p != nullptr) {
		cout << p->data << ' ';
		p = p->link;
	}
	cout << endl;
	return;
}

void LinkedList::Add(int element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);
	Node* p = first, * q = nullptr;
	if (p == nullptr) { //연결 리스트가 비어있는 경우
		first = newNode;
		return;
	}
	if (newNode->data < p->data) { //맨 앞에 새 노드를 추가하는 경우
		newNode->link = p;
		first = newNode;
		return;
	}
	while (p != nullptr) {
		if (newNode->data < p->data) {
			newNode->link = p;
			q->link = newNode;
			return;
		}
		q = p;
		p = p->link;
	}
	//맨 끝에 새 노드를 추가하는 경우
	q->link = newNode;
	return;
}

bool LinkedList::Search(int data) {
	Node* p = first;
	while (p != nullptr) {
		if (p->data == data)
			return true;
		p = p->link;
	}
	return false;
}

bool LinkedList::Delete(int element) // delete the element
{
	Node* p = first, * q = nullptr;
	while (p != nullptr) {
		if (p->data == element) {
			if (p == first) { //지워야 하는 노드가 first인 경우
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
	return true;
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
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0.Add0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit" << endl << "선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			data = rand() % 49;
			la.Add(data);
			break;
		case Add2:
			data = rand() % 49;
			lb.Add(data);
			break;
		case Delete:
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "삭제 완료" << endl;
			break;
		case Show:
			cout << "리스트 la = ";
			la.Show();
			cout << "리스트 lb = ";
			lb.Show();
			break;
		case Search: // 회원 번호 검색
			int n; cin >> n;
			result = la.Search(n);
			if (!result)
				cout << "검색 값 = " << n << " 데이터가 없습니다." << endl;
			else
				cout << "검색 값 = " << n << " 데이터가 존재합니다." << endl;
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			break;
		case Exit:
			cout << "Exit" << endl;
			exit(1);
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


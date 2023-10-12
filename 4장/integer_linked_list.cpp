/*
1단계-정수 연결 리스트: 단순한 linked list에서 insert, delete하는 알고리즘을 코딩
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
	friend ostream& operator<< (ostream& os, Node& n) {
		os << n.data << " ";
		return os;
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
	void Add(int element);
	bool Search(int data);
	LinkedList& operator+ (LinkedList&);
};

LinkedList& LinkedList::operator+ (LinkedList& lb) {
	LinkedList lc;
	Node* a = first; Node* b = lb.first;
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

void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;
	if (first == nullptr) {
		cout << "Empty List" << endl;
		return;
	}
	while (p != nullptr) {
		cout << p->data << " ";
		p = p->link;
	}
	cout << endl;
}
void LinkedList::Add(int element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);
	if (first == nullptr) { //linked list가 비어있는 경우
		first = newNode;
		return;
	}
	Node* p = first;
	if (p->data > element) {
		newNode->link = p;
		first = newNode;
	}
	else {
		while (p->link != nullptr) {
			if (p->link->data > element) {
				newNode->link = p->link;
				p->link = newNode;
				return;
			}
			else p = p->link;
		}
		p->link = newNode;
	}
}
bool LinkedList::Search(int data) {
	Node* p = first;
	while (p != nullptr) {
		if (p->data == data) return true;
		p = p->link;
	}
	return false;
}
bool LinkedList::Delete(int element) // delete the element
{
	Node* p = first;
	Node* prev = nullptr;
	while (p != nullptr) {
		if (p->data == element) {
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
	Add0, Add1, Delete, Show, Search, Merge, Exit
};
int main() {
	Enum menu; // 메뉴
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;

	int data = 0;
	//l->Show();
	do {
		cout << "0.ADD0, 1. ADD1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit" << endl << "선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0: // 머리노드 삽입
			data = rand() % 49;
			la.Add(data);
			cout << "삽입후 리스트: ";
			la.Show();
			break;
		case Add1: // 머리노드 삽입
			data = rand() % 49;
			lb.Add(data);
			cout << "삽입후 리스트: ";
			lb.Show();
			break;
		case Delete: // 머리 노드 삭제
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "삭제된 데이터는 " << data << endl;
			break;
		case Show: // 꼬리 노드 삭제
			la.Show();
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
			cout << "합친 후 리스트: ";
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


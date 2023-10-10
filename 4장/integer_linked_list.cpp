/*
1단계-정수 연결 리스트: 단순한 linked list에서 insert, delete하는 알고리즘을 코딩
*/
#include <iostream>
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
	void Add(int element);
	bool Search(int data);
};
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;
	
}
void LinkedList::Add(int element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);
	
	
}
bool LinkedList::Search(int data) { // 전체 리스트를 순서대로 출력한다.
	Node* ptr = first;
	
	return false;
}
bool LinkedList::Delete(int element) // delete the element
{
	
	return false;// 삭제할 대상이 없다.
}

enum Enum {
	Add, Delete, Show, Search, Exit
};
void main() {
	Enum menu; // 메뉴
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList* l = new LinkedList();
	cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. Exit 선택::";

	int data = 0;
	l->Show();
	do {
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add: // 머리노드 삽입
			data = rand() % 49;
			l->Add(data);
			cout << "삽입후 리스트: ";
			l->Show();
			break;
		case Delete: // 머리 노드 삭제
			cin >> data;
			result = l->Delete(data);
			if (result)
				cout << "삭제된 데이터는 " << data;
			break;
		case Show: // 꼬리 노드 삭제
			l->Show();
			break;
		case Search: // 회원 번호 검색
			int n; cin >> n;
			result = l->Search(n);
			if (!result)
				cout << "검색 값 = " << n << " 데이터가 없습니다.";
			else
				cout << "검색 값 = " << n << " 데이터가 존재합니다.";
			break;
		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


/*
1�ܰ�-���� ���� ����Ʈ: �ܼ��� linked list���� add, delete�ϴ� �˰����� �ڵ�
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
	void Add(int element);//���ĵǵ��� ����
	bool Search(int data);
	LinkedList& operator+(LinkedList&);
};
void LinkedList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
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

void LinkedList::Add(int element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);
	Node* p = first, * q = nullptr;
	if (p == nullptr) { //���� ����Ʈ�� ����ִ� ���
		first = newNode;
		return;
	}
	if (newNode->data < p->data) { //�� �տ� �� ��带 �߰��ϴ� ���
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
	//�� ���� �� ��带 �߰��ϴ� ���
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
			if (p == first) { //������ �ϴ� ��尡 first�� ���
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
	Enum menu; // �޴�
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0.Add0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit" << endl << "����::";
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
				cout << "���� �Ϸ�" << endl;
			break;
		case Show:
			cout << "����Ʈ la = ";
			la.Show();
			cout << "����Ʈ lb = ";
			lb.Show();
			break;
		case Search: // ȸ�� ��ȣ �˻�
			int n; cin >> n;
			result = la.Search(n);
			if (!result)
				cout << "�˻� �� = " << n << " �����Ͱ� �����ϴ�." << endl;
			else
				cout << "�˻� �� = " << n << " �����Ͱ� �����մϴ�." << endl;
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = ";
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


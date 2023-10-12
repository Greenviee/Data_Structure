/*
1�ܰ�-���� ���� ����Ʈ: �ܼ��� linked list���� insert, delete�ϴ� �˰����� �ڵ�
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

void LinkedList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
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
void LinkedList::Add(int element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);
	if (first == nullptr) { //linked list�� ����ִ� ���
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
	Add0, Add1, Delete, Show, Search, Merge, Exit
};
int main() {
	Enum menu; // �޴�
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;

	int data = 0;
	//l->Show();
	do {
		cout << "0.ADD0, 1. ADD1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit" << endl << "����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0: // �Ӹ���� ����
			data = rand() % 49;
			la.Add(data);
			cout << "������ ����Ʈ: ";
			la.Show();
			break;
		case Add1: // �Ӹ���� ����
			data = rand() % 49;
			lb.Add(data);
			cout << "������ ����Ʈ: ";
			lb.Show();
			break;
		case Delete: // �Ӹ� ��� ����
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "������ �����ʹ� " << data << endl;
			break;
		case Show: // ���� ��� ����
			la.Show();
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
			cout << "��ģ �� ����Ʈ: ";
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


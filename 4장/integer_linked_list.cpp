/*
1�ܰ�-���� ���� ����Ʈ: �ܼ��� linked list���� insert, delete�ϴ� �˰����� �ڵ�
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
};
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
	Add, Delete, Show, Search, Exit
};
int main() {
	Enum menu; // �޴�
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList* l = new LinkedList();

	int data = 0;
	//l->Show();
	do {
		cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. Exit" << endl << "����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add: // �Ӹ���� ����
			data = rand() % 49;
			l->Add(data);
			cout << "������ ����Ʈ: ";
			l->Show();
			break;
		case Delete: // �Ӹ� ��� ����
			cin >> data;
			result = l->Delete(data);
			if (result)
				cout << "������ �����ʹ� " << data << endl;
			break;
		case Show: // ���� ��� ����
			l->Show();
			break;
		case Search: // ȸ�� ��ȣ �˻�
			int n; cin >> n;
			result = l->Search(n);
			if (!result)
				cout << "�˻� �� = " << n << " �����Ͱ� �����ϴ�." << endl;
			else
				cout << "�˻� �� = " << n << " �����Ͱ� �����մϴ�." << endl;
			break;
		case Exit: 
			cout << "Exit" << endl;
			exit(1);
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


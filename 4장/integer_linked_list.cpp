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
	
}
void LinkedList::Add(int element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);
	
	
}
bool LinkedList::Search(int data) { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* ptr = first;
	
	return false;
}
bool LinkedList::Delete(int element) // delete the element
{
	
	return false;// ������ ����� ����.
}

enum Enum {
	Add, Delete, Show, Search, Exit
};
void main() {
	Enum menu; // �޴�
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList* l = new LinkedList();
	cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. Exit ����::";

	int data = 0;
	l->Show();
	do {
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
				cout << "������ �����ʹ� " << data;
			break;
		case Show: // ���� ��� ����
			l->Show();
			break;
		case Search: // ȸ�� ��ȣ �˻�
			int n; cin >> n;
			result = l->Search(n);
			if (!result)
				cout << "�˻� �� = " << n << " �����Ͱ� �����ϴ�.";
			else
				cout << "�˻� �� = " << n << " �����Ͱ� �����մϴ�.";
			break;
		case Exit: // ���� ��� ����
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


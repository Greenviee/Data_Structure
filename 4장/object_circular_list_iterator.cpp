/*
4�ܰ�- ���� ��ü ���� ����Ʈ�� iterator ����
CircularList�� ������� �� iterator�� �����Ѵ�.
*/
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

class Employee {
	friend class Node;
	friend class CircularList;
	friend class ListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee& e) {
		os << "No: " << e.eno << " Name: " << e.ename << " Salary: " << e.salary << endl;
		return os;
	}
	bool operator<(Employee& e) {
		if (stoi(eno) < stoi(e.eno)) return true;
		return false;
	}
	bool operator==(Employee& e) {
		if (eno == e.eno && ename == e.ename && salary == e.salary) return true;
		return false;
	}
	int getSalary() const {
		return salary;
	}
};

class Node {
	friend class ListIterator;
	friend class CircularList;
	Employee data;
	Node* link;
public:
	Node() {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* first;
	Node* last;//last ��带 ����Ű�� last ������ ����ϴ� �������� ���� �ǽ� 
	//static Node* av;
public:
	CircularList() {
		first = last = nullptr;
	}
	bool Delete(string);
	void Show();
	void Add(Employee);//sno�� ���ĵǵ��� ����
	bool Search(string);
};
class ListIterator {
public:
	ListIterator(const CircularList& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++(); //Next()
	ListIterator operator ++(int);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee* GetCurrent();
private:
	Node* current; //pointer to nodes
	const CircularList& list;//existing list
};

void CircularList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* p = first;
	if (first == nullptr) {
		cout << "Empty List" << endl;
		return;
	}
	do  {
		cout << p->data;
		p = p->link;
	} while (p != first);
	cout << endl;
}
void CircularList::Add(Employee element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);
	if (first == nullptr) { //linked list�� ����ִ� ���
		first = newNode;
		last = newNode;
		first->link = last;
		last->link = first;
		return;
	}
	Node* p = first, *q = last;
	do {
		if (element < p->data) {
			if (p == first) {
				first = newNode;
				newNode->link = p;
				last->link = newNode;
				return;
			}
			q->link = newNode;
			newNode->link = p;
			return;
		}
		q = p;
		p = p->link;
	} while (p != first);
	//�� ���� �� ��带 ���� ���
	last = newNode;
	q->link = last;
	last->link = first;
	return;
}
bool CircularList::Search(string eno) { // sno�� ���� ���ڵ带 ã��
	Node* p = first;
	do {
		if (p->data.eno == eno) return true;
		p = p->link;
	} while (p != first);
	return false;
}
bool CircularList::Delete(string eno) // delete the element
{
	Node* p = first;
	Node* prev = last;
	do {
		if (p->data.eno == eno) {
			prev->link = p->link;
			if (p == first) {
				first = p->link;
			}
			if (p == last) {
				last = prev;
			}
			delete p;
			return true;
		}
		prev = p;
		p = p->link;
	} while (p != first);
	return false;// ������ ����� ����.
}

ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.first) {
}

bool ListIterator::NotNull() {
	if (current != list.first)
		return true;
	else
		return false;
}
bool ListIterator::NextNotNull() {
	if (current->link != list.first)
		return true;
	else
		return false;
}
Employee* ListIterator::First() {
	return &list.first->data;
}
Employee* ListIterator::Next() {
	Employee* e = &current->data;
	current = current->link;
	return e;
}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

ListIterator::~ListIterator() {
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->()const {
	return &current->data;
}

ListIterator& ListIterator::operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator ++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::operator != (const ListIterator right) const {
	return current != right.current;
}

bool ListIterator::operator == (const ListIterator right) const {
	return current == right.current;
}
//int printAll(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
//int sumProductFifthElement(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
int sum(const CircularList& l)
{
	int ret = 0;
	ListIterator li(l);
	do {
		ret += li.GetCurrent()->getSalary();
		li++;
	} while (li.NotNull());
	return ret;
}

double avg(const CircularList& l)
{
	ListIterator li(l);
	double sum = 0, cnt = 0;
	do {
		sum += li.GetCurrent()->getSalary();
		cnt++;
		li++;
	} while (li.NotNull());
		return sum / cnt;
}

int min(const CircularList& l)
{
	ListIterator li(l);
	int Min = 987654321;
	do {
		if (li.GetCurrent()->getSalary() < Min)
			Min = li.GetCurrent()->getSalary();
		li++;
	} while (li.NotNull());
	return Min;
}

int max(const CircularList& l)
{
	ListIterator li(l);
	int Max = 0;
	do {
		if (li.GetCurrent()->getSalary() > Max)
			Max = li.GetCurrent()->getSalary();
		li++;
	} while (li.NotNull());
	return Max;
}

enum Enum {
	Add, Delete, Show, Search, SUM, AVG, MIN, MAX, Exit
};

//Node* CircularList::av = NULL;//static ������ �ʱ�ȭ ����� ����ؾ� �Ѵ�

int main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee data;
	bool result = false;
	srand(time(NULL));
	CircularList* l = new CircularList();
	do {
		cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. sum, 5.avg, 6.min, 7.max, 8.exit" << endl << "����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = Employee(eno, ename, pay);
			l->Add(data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = l->Delete(eno);
			if (result)
				cout << "eno = " << eno << " ���� �Ϸ�." << endl;
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
		case SUM:  cout << "sum() = " << sum(*l) << endl; break;
		case AVG:  cout << "avg() = " << avg(*l) << endl; break;
		case MIN:  cout << "min() = " << min(*l) << endl; break;
		case MAX:  cout << "max() = " << max(*l) << endl; break;
		case Exit: 
			cout << "Exit";
			exit(1);
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

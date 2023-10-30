/*
* doubly linked list
6�ܰ�- ���� ��ü ���� ���� ����Ʈ�� available list, getNode, retNode
head node�� ���� �ְ� ������ ������ available list�� �����Ѵ�.
CircularDoublyList�� ������� �� iterator�� �����Ѵ�.
*/
#include <iostream>
#include <string>
using namespace std;
template<class T> class DoublyListNode;
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
class Employee {
	template<class T> friend class DoublyListNode;
	template<class T> friend class CircularDoublyList;
	template<class T> friend class CircularDoublyListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator>(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {
	os << "�����ȣ: " << emp.eno << " �̸�: " << emp.ename << " ����: " << emp.salary << endl;
	return os;
}
bool Employee::operator==(Employee& emp) {
	if (eno == emp.eno && ename == emp.ename && salary == emp.salary)
		return true;
	return false;
}
bool Employee::operator<(Employee& emp) {
	if (stoi(eno) < stoi(emp.eno))
		return true;
	return false;
}
bool Employee::operator>(Employee& emp) {
	if (stoi(eno) > stoi(emp.eno))
		return true;
	return false;
}
char Employee::compare(const Employee* emp) const {
	if (stoi(eno) < stoi(emp->eno))
		return '<';
	else if (stoi(eno) > stoi(emp->eno))
		return '>';
	else {
		if (ename < emp->ename)
			return '>';
		else if (ename < emp->ename)
			return '<';
		else {
			if (salary < emp->salary)
				return '<';
			else if (salary > emp->salary)
				return '>';
			else return '=';
		}
	}
}
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
template<class T>
class DoublyListNode {
	friend class CircularDoublyList<T>;
	friend class CircularDoublyListIterator<T>;
public:
	DoublyListNode(T* p) {
		data = *p; llink = rlink = this;
	}
	DoublyListNode() {
		llink = rlink = this;
	}
private:
	T data;
	DoublyListNode<T>* llink, * rlink;
};
template<class T>
class CircularDoublyList {
	friend class CircularDoublyListIterator<T>;
public:
	CircularDoublyList() { last = new DoublyListNode<T>; }
	template<class T>
	friend ostream& operator<<(ostream&, CircularDoublyList<T>&);
	bool Delete(string);
	void Show();
	void Add(T*);//sno�� ���ĵǵ��� ����
	bool Search(string);
	DoublyListNode<T>* GetNode();
	void RetNode(DoublyListNode<T>*);
	void Erase();
	CircularDoublyList<T>& operator+(CircularDoublyList<T>&);
private:
	DoublyListNode<T>* last;
	static DoublyListNode<T>* av;
};

template<class T>
class CircularDoublyListIterator {
public:
	CircularDoublyListIterator(const CircularDoublyList<T>& l) : list(l), current(list.last->rlink->rlink) {}
	~CircularDoublyListIterator();
	bool NotNull();
	bool NextNotNull();
	T* First();
	T* Next();
	T* GetCurrent();
private:
	const CircularDoublyList<T>& list;
	DoublyListNode<T>* current;
};
template<class T>
DoublyListNode<T>* CircularDoublyList<T>::GetNode()
{ //provide a node for use
	DoublyListNode<T>* n;
	if (av != NULL) {
		n = av;
		av = av->rlink;
		n->rlink = n->llink = n;
	}
	else
		n = new DoublyListNode<T>();
	return n;
}
template<class T>
void CircularDoublyList<T>::RetNode(DoublyListNode<T>* x)
{ //free the node pointed to by x
	if (av == NULL) {
		av = x;
		x->rlink = x->llink = NULL;
	}
	else {
		x->rlink = av;
		x->llink = NULL;
		av->llink = x;
		av = x;
	}
}
template<class T>
void CircularDoublyList<T>::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;
	while (p != first) {
		cout << p->data;
		p = p->rlink;
	}
}
template<class T>
void CircularDoublyList<T>::Add(T* element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	DoublyListNode<T>* newNode = GetNode(); newNode->data = *element;
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;
	while (p != first) {
		if (newNode->data < p->data) {
			p->llink->rlink = newNode;
			newNode->llink = p->llink;
			newNode->rlink = p;
			p->llink = newNode;
			return;
		}
		p = p->rlink;
	}
	p->llink->rlink = newNode;
	newNode->rlink = first;
	newNode->llink = p->llink;
	first->llink = newNode;
	last = newNode;
	return;
}
template<class T>
bool CircularDoublyList<T>::Search(string eno) { // sno�� ���� ���ڵ带 ã��
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;
	while (p != first) {
		if (p->data.eno == eno)
			return true;
		p = p->rlink;
	}
	return false;
}
template<class T>
bool CircularDoublyList<T>::Delete(string eno) // delete the element
{
	DoublyListNode<T>* first = last->rlink;
	DoublyListNode<T>* p = first->rlink;
	while (p != first) {
		if (p->data.eno == eno) {
			if (p == last)
				last = p->llink;
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			RetNode(p);
			return true;
		}
		p = p->rlink;
	}
	return false;
}
template<class T>
void CircularDoublyList<T>::Erase() {
	DoublyListNode<T>* first = last->rlink;
	if (av == NULL) {
		av = first->rlink;
		last->rlink = NULL;
		av->llink = NULL;
		first->rlink = first->llink = first;
		last = first;
	}
	else {
		last->rlink = av;
		av->llink = last;
		av = first->rlink;
		av->llink = NULL;
		first->rlink = first->llink = first;
		last = first;
	}
}

template<class T>
ostream& operator<<(ostream& os, CircularDoublyList<T>& l)
{
	CircularDoublyListIterator<T> li(l);
	if (!li.NotNull()) {
		os << "Empty List" << endl;
		return os;
	}
	while (li.NotNull()) {
		os << li.GetCurrent() << endl;
		li.Next();
	}
	return os;
}
template<class T>
CircularDoublyList<T>& CircularDoublyList<T>::operator+(CircularDoublyList<T>& lb) {
	T* p, * q;
	CircularDoublyListIterator<T> Aiter(*this); CircularDoublyListIterator<T> Biter(lb);
	CircularDoublyList<T> lc;
	p = Aiter.First(); q = Biter.First();
	if (!Aiter.NotNull())
	while (Aiter.NotNull() && Biter.NotNull()) {
		switch (p->compare(q)) {
		case '<':
			lc.Add(p);
			p = Aiter.Next();
			break;
		case '>':
			lc.Add(q);
			q = Biter.Next();
			break;
		case '=':
			lc.Add(p);
			p = Aiter.Next();
			q = Biter.Next();
			break;
		}
	}
	while (Aiter.NotNull()) {
		lc.Add(p);
		p = Aiter.Next();
	}
	while (Biter.NotNull()) {
		lc.Add(q);
		q = Biter.Next();
	}
	return lc;
}

template<class T>
bool CircularDoublyListIterator<T>::NotNull() {
	return current != list.last->rlink;
}
template<class T>
bool CircularDoublyListIterator<T>::NextNotNull() {
	return current->rlink != list.last->rlink;
}
template<class T>
T* CircularDoublyListIterator<T>::First() {
	current = list.last->rlink->rlink;
	return &current->data;
}
template<class T>
T* CircularDoublyListIterator<T>::Next() {
	current = current->rlink;
	return &current->data;
}
template<class T>
T* CircularDoublyListIterator<T>::GetCurrent() {
	return &current->data;
}
template<class T>
CircularDoublyListIterator<T>::~CircularDoublyListIterator() {
}

//int printAll(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
//int sumProductFifthElement(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
template<class T>
int sum(const CircularDoublyList<T>& l)
{
	CircularDoublyListIterator<T> li(l);
	int ret = 0;
	while (li.NotNull()) {
		ret += li.GetCurrent()->getSalary();
		li.Next();
	}
	return ret;
}
template<class T>
double avg(const CircularDoublyList<T>& l)
{
	CircularDoublyListIterator<T> li(l);
	int sum = 0, n = 0;
	while (li.NotNull()) {
		sum += li.GetCurrent()->getSalary();
		n++;
		li.Next();
	}
	double ret = (double)sum / (double)n;
	return ret;
}
template<class T>
int min(const CircularDoublyList<T>& l)
{
	CircularDoublyListIterator<T> li(l);
	int ret = 987654321;
	while (li.NotNull()) {
		int sal = li.GetCurrent()->getSalary();
		ret = min(ret, sal);
		li.Next();
	}
	return ret;
}
template<class T>
int max(const CircularDoublyList<T>& l)
{
	CircularDoublyListIterator<T> li(l);
	int ret = 0;
	while (li.NotNull()) {
		int sal = li.GetCurrent()->getSalary();
		ret = max(ret, sal);
		li.Next();
	}
	return ret;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};
template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = 0;
/*
Node* CircularDoublyList::av = NULL;//static ������ �ʱ�ȭ ����� ����ؾ� �Ѵ�
*/
void main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularDoublyList<Employee> la, lb, lc;
	Employee* s;
	do {
		cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			cout << *data;
			la.Add(data);
			break;
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			cout << *data;
			lb.Add(data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "eno = " << eno << " ���� �Ϸ�.";
			break;
		case Show:
			cout << "����Ʈ la = ";
			la.Show();
			cout << "����Ʈ lb = ";
			lb.Show();
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�.";
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�.";
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = ";
			lc.Show();
			cout << "����Ʈ la�� ����" << endl;
			la.Erase();
			cout << "����Ʈ lb�� ����" << endl;
			lb.Erase();
			cout << "����Ʈ la = ";
			la.Show();
			cout << endl << "����Ʈ lb = ";
			lb.Show();
			break;
		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit: // ���� ��� ����
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

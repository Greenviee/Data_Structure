/*
6단계- 원형 객체 연결 리스트의 available list, getNode, retNode
head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
CircularList를 대상으로 한 iterator를 구현한다.
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
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {
	os << "No: " << emp.eno << " Name: " << emp.ename << " Salary: " << emp.salary << endl;
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
class Node {
	friend class ListIterator;
	friend class CircularList;
	Employee data;
	Node* link;
public:
	Node() { }
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* first;//last 노드를 가리키는 last 변수를 사용하는 버젼으로 구현 실습 
	static Node* av;
public:
	CircularList() {
		first = new Node(); first->link = first;
	}
	bool Delete(string);
	void Show();
	void Add(Employee*);//sno로 정렬되도록 구현
	bool Search(string);
	Node* GetNode();
	void RetNode(Node*);
	void Erase();
	CircularList& operator+(CircularList&);
	friend ostream& operator<<(ostream& os, CircularList& l);
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

Node* CircularList::GetNode() { //provide a node for use
	Node* n;
	if (av != NULL) {
		n = av;
		av = av->link;
	}
	else n = new Node();
	return n;
}

void CircularList::RetNode(Node* x) {
	x->link = av;
	av = x;
	x = 0;
}

ostream& operator<<(ostream& os, CircularList& l) {
	ListIterator li(l);
	if (!li.NotNull()) {
		os << "Empty List" << endl;
		return os;
	}
	while (li.NotNull()) {
		os << li.GetCurrent() << endl;
		li++;
	}
	return os;
}
void CircularList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first->link;
	while (p != first) {
		cout << p->data;
		p = p->link;
	}
}
void CircularList::Add(Employee* element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = GetNode(); newNode->data = *element;
	Node* p = first->link;
	Node* q = first;
	while (p != first) {
		if (newNode->data < p->data) {
			newNode->link = p;
			q->link = newNode;
			return;
		}
		q = p;
		p = p->link;
	}
	q->link = newNode; //맨 끝에 노드를 추가하는 경우
	newNode->link = first;
	return;
}
bool CircularList::Search(string eno) { // sno를 갖는 레코드를 찾기
	Node* p = first->link;
	while (p != first) {
		if (p->data.eno == eno)
			return true;
		p = p->link;
	}
	return false;
}
bool CircularList::Delete(string eno) { // delete the element
	Node* p = first->link;
	Node* q = first;
	while (p != first) {
		if (p->data.eno == eno) {
			q->link = p->link;
			RetNode(p);
			return true;
		}
		q = p;
		p = p->link;
	}
	return false;
}
void CircularList::Erase() {
	first->link = av;
	first = new Node();
	first->link = first;
}
CircularList& CircularList::operator+(CircularList& lb) {
	Employee* p, * q;
	ListIterator Aiter(*this); ListIterator Biter(lb);
	CircularList lc;
	p = Aiter.First(); q = Biter.First();
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
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.first->link) {
}
bool ListIterator::NotNull() {
	return current != list.first;
}
bool ListIterator::NextNotNull() {
	return current->link != list.first;
}
Employee* ListIterator::First() {
	current = list.first->link;
	return &current->data;
}
Employee* ListIterator::Next() {
	current = current->link;
	return &current->data;
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
//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
int sum(const CircularList& l) {
	ListIterator li(l);
	Employee* p = li.First();
	int ret = 0;
	while (li.NotNull()) {
		ret += p->getSalary();
		p = li.Next();
	}
	return ret;
}

double avg(const CircularList& l) {
	ListIterator li(l);
	Employee* p = li.First();
	int sum = 0, n = 0;
	while (li.NotNull()) {
		sum += p->getSalary();
		n++;
		p = li.Next();
	}
	return (double)sum / (double)n;
}

int min(const CircularList& l) {
	ListIterator li(l);
	Employee* p = li.First();
	int min = 987654321;
	while (li.NotNull()) {
		if (p->getSalary() < min)
			min = p->getSalary();
		p = li.Next();
	}
	return min;
}

int max(const CircularList& l) {
	ListIterator li(l);
	Employee* p = li.First();
	int max = 0;
	while (li.NotNull()) {
		if (p->getSalary() > max)
			max = p->getSalary();
		p = li.Next();
	}
	return max;
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

Node* CircularList::av = NULL;//static 변수의 초기화 방법을 기억해야 한다

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularList la, lb, lc;
	do {
		cout << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit" << endl << "선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			la.Add(data);
			break;
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "eno = " << eno << " 삭제 완료." << endl;
			break;
		case Show:
			cout << "리스트 la: " << endl;
			la.Show();
			cout << "리스트 lb: " << endl;
			lb.Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc: " << endl;
			lc.Show();
			cout << "리스트 la를 삭제" << endl;
			la.Erase();
			cout << "리스트 lb를 삭제" << endl;
			lb.Erase();
			cout << "리스트 la: " << endl;
			la.Show();
			cout << endl << "리스트 lb: " << endl;
			lb.Show();
			break;
		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}
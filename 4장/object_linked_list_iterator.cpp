/*
3단계-객체 연결 리스트의 iterator 버젼
*/
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
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
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class LinkedList {
	friend class ListIterator;
	Node* first;
public:
	LinkedList() {
		first = nullptr;
	}
	bool Delete(string);
	void Show();
	void Add(Employee);//sno로 정렬되도록 구현
	bool Search(string);
};
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;
	if (first == nullptr) {
		cout << "Empty List" << endl;
		return;
	}
	while (p != nullptr) {
		cout << p->data;
		p = p->link;
	}
	cout << endl;
}
void LinkedList::Add(Employee element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);
	if (first == nullptr) { //linked list가 비어있는 경우
		first = newNode;
		return;
	}
	Node* p = first;
	if (element < p->data) {
		newNode->link = p;
		first = newNode;
	}
	else {
		while (p->link != nullptr) {
			if (element < p->link->data) {
				newNode->link = p->link;
				p->link = newNode;
				return;
			}
			else p = p->link;
		}
		p->link = newNode;
	}
}
bool LinkedList::Search(string eno) { // sno를 갖는 레코드를 찾기
	Node* p = first;
	while (p != nullptr) {
		if (p->data.eno == eno) return true;
		p = p->link;
	}
	return false;
}
bool LinkedList::Delete(string eno) // delete the element
{
	Node* p = first;
	Node* prev = nullptr;
	while (p != nullptr) {
		if (p->data.eno == eno) {
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
class ListIterator {
public:
	ListIterator(const LinkedList& lst);
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
	const LinkedList& list;//existing list
};
ListIterator::ListIterator(const LinkedList& lst) : list(lst), current(lst.first) {
	cout << "List Iterator is constructed" << endl;
}
bool ListIterator::NotNull() {
	if (current != NULL)
		return true;
	else
		return false;
}
bool ListIterator::NextNotNull() {
	if (current->link != NULL)
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
//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
int sum(const LinkedList& l)
{
	int ret = 0;
	ListIterator li(l);
	while (li.NotNull()) {
		ret += li.GetCurrent()->getSalary();
		li++;
	}
	return ret;
}

double avg(const LinkedList& l)
{
	ListIterator li(l);
	double sum = 0, cnt = 0;
	while (li.NotNull()) {
		sum += li.GetCurrent()->getSalary();
		cnt++;
		li++;
	}
	return sum / cnt;
}

int min(const LinkedList& l)
{
	ListIterator li(l);
	int Min = 987654321;
	while (li.NotNull()) {
		if (li.GetCurrent()->getSalary() <Min)
			Min = li.GetCurrent()->getSalary();
		li++;
	}
	return Min;
}

int max(const LinkedList& l)
{
	ListIterator li(l);
	int Max = 0;
	while (li.NotNull()) {
		if (li.GetCurrent()->getSalary() > Max)
			Max = li.GetCurrent()->getSalary();
		li++;
	}
	return Max;
}

enum Enum {
	Add, Delete, Show, Search, SUM, AVG, MIN, MAX, Exit
};

int main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee data;
	bool result = false;
	srand(time(NULL));
	LinkedList* l = new LinkedList();

	do {
		cout << "0.ADD, 1.Delete, 2.Show, 3.Search, 4. sum, 5.avg, 6.min, 7.max, 8.exit" << endl << "선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = Employee(eno, ename, pay);
			l->Add(data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = l->Delete(eno);
			if (result)
				cout << "삭제 완료";
			break;
		case Show: // 꼬리 노드 삭제
			l->Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = l->Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
			break;
		case SUM:  cout << "sum() = " << sum(*l) << endl; break;
		case AVG:  cout << "avg() = " << avg(*l) << endl; break;
		case MIN:  cout << "min() = " << min(*l) << endl; break;
		case MAX:  cout << "max() = " << max(*l) << endl; break;
		case Exit: // 꼬리 노드 삭제
			cout << "Exit";
			exit(1);
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}


//�ҽ��ڵ� 5.3: Threaded Tree


//Tree 5.13 Threaded binary tree
/*
1. template version���� Employee ��ü�� ��忡 ����
2. tree iterator�� ����Ͽ� sum�� ���Ѵ�
3. main���� Insert, Remove, Inorder, IteratorInorder, Search, PrintTree�� Employee�� ���Ͽ� �����Ѵ�
4. Employee ��ü�� ȭ�鿡�� �Է����� �ʰ� 10���� ��ü�� �迭�� �ʱ�ȭ for������ �Է��Ѵ�.
5. main���� InsertStudent, InorderStudent�� Student�� ���Ͽ� �����Ѵ�.
*/
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#define MAX_VALUE 65536
using namespace std;

template <class T> class ThreadedTree;
template <class T> class ThreadedInorderIterator;

class Employee {
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) { salary = rand() % 10000; }
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator>(Employee&);
	bool operator==(Employee&);
	bool operator>=(Employee&);
	int getSalary() {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {
	os << "�����ȣ: " << emp.eno << " �̸�: " << emp.ename << " ����: " << emp.salary << endl;;
	return os;
}
bool Employee::operator==(Employee& emp) {
	bool result = false;
	if (eno == emp.eno)
		return (ename == emp.ename);
	else
		return false;
}
bool Employee::operator<(Employee& emp) {
	if (salary < emp.salary)
		return true;
	else
		return false;
}
bool Employee::operator>(Employee& emp) {
	if (salary > emp.salary)
		return true;
	else
		return false;
}
bool Employee::operator>=(Employee& emp) {
	return *this > emp || *this == emp;
}
class Student {
	string snum;
	string sname;
	int age;
public:
	Student() {}
	Student(string sname, string snum) : sname(sname), snum(snum) {}
	friend ostream& operator<<(ostream& os, Student&);
	bool operator<(Student&);
	bool operator==(Student&);
};
ostream& operator<<(ostream& os, Student& emp) {
	os << "��ȣ: " << emp.snum << " �̸�: " << emp.sname << endl;
	return os;
}
bool Student::operator==(Student& emp) {
	bool result = false;
	if (snum == emp.snum)
		return (sname == emp.sname);
	else
		return false;
}
bool Student::operator<(Student& emp) {
	bool result = false;
	if (snum == emp.snum)
		return (sname < emp.snum);
	else
		return (snum < emp.snum);
}
template <class T>
class ThreadedNode {
	friend class ThreadedTree<T>;
	friend class ThreadedInorderIterator<T>;
private:
	bool LeftThread;
	ThreadedNode* LeftChild;
	T data;
	ThreadedNode* RightChild;
	bool RightThread;
public:
	ThreadedNode() { 
		LeftChild = RightChild = 0;
		LeftThread = RightThread = true;
	}
	ThreadedNode(T ch) { 
		data = ch;
		LeftThread = RightThread = true;
	}
	ThreadedNode(T ch, ThreadedNode* lefty, ThreadedNode* righty,
		bool lthread, bool rthread)
	{
		data = ch; LeftChild = lefty; RightChild = righty;
		LeftThread = lthread;  RightThread = rthread;
	};
};
template <class T>
class ThreadedTree {
	friend class ThreadedInorderIterator<T>;
private:
	ThreadedNode<T>* root;
	void Inorder(ThreadedNode<T>*, bool);
public:
	/* Constructor */
	ThreadedTree() {
		root = new ThreadedNode<T>;
		root->RightChild = root->LeftChild = root;
		root->data = T();
		root->LeftThread = true; root->RightThread = false;
	};
	void InsertRight(ThreadedNode<T>*, T);
	bool Insert(T data);
	bool Delete(T data);
	void Inorder();
	void PrintTree();
	bool Search(T data);
	ThreadedNode<T>* InorderSucc(ThreadedNode<T>*);
};

template <class T>
ThreadedNode<T>* ThreadedTree<T>::InorderSucc(ThreadedNode<T>* current)
{
	ThreadedNode<T>* temp = current->RightChild;
	if (!current->RightThread)
		while (!temp->LeftThread) temp = temp->LeftChild;
	return temp;
}

template <class T>
void ThreadedTree<T>::InsertRight(ThreadedNode<T>* s, T ch)
// Create node r; store ch in r; insert r as the right child of s
{
	ThreadedNode<T>* r = new ThreadedNode<T>(ch);
	r->RightChild = s->RightChild;
	r->RightThread = s->RightThread;
	r->LeftChild = s;
	r->LeftThread = true; // LeftChild is a thread
	s->RightChild = r; // attach r to s
	s->RightThread = false;
	if (!r->RightThread) {
		ThreadedNode* temp = InorderSucc(r); // returns the inorder successor of r
		temp->LeftChild = r;
	}
}

/* Function to delete an element */
template <class T>
bool ThreadedTree<T>::Delete(T data)
{
	ThreadedNode<T>* dest = root->LeftChild, * p = root;
	cout << dest->data << endl;
	for (;;)
	{
		if (dest->data < data)
		{
			/* not found */
			if (dest->RightThread)
				return false;
			p = dest;
			dest = dest->RightChild;
		}
		else if (dest->data > data)
		{
			/* not found */
			if (dest->LeftThread)
				return false;
			p = dest;
			dest = dest->LeftChild;
		}
		else
		{
			/* found */
			break;
		}
	}
	ThreadedNode<T>* target = dest;
	if (!dest->RightThread && !dest->LeftThread)
	{
		/* dest has two children*/
		p = dest;
		/* find largest node at left child */
		target = dest->LeftChild;
		while (!target->RightThread)
		{
			p = target;
			target = target->RightChild;
		}
		/* using replace mode*/
		dest->data = target->data;
	}
	if (p->data >= target->data)
	{
		if (target->RightThread && target->LeftThread)
		{
			p->LeftChild = target->LeftChild;
			p->LeftThread = true;
		}
		else if (target->RightThread)
		{
			ThreadedNode<T>* largest = target->LeftChild;
			while (!largest->RightThread)
			{
				largest = largest->RightChild;
			}
			largest->RightChild = p;
			p->LeftChild = target->LeftChild;
		}
		else
		{
			ThreadedNode<T>* smallest = target->RightChild;
			while (!smallest->LeftThread)
			{
				smallest = smallest->LeftChild;
			}
			smallest->LeftChild = target->LeftChild;
			p->LeftChild = target->RightChild;
		}
	}
	else
	{
		if (target->RightThread && target->LeftThread)
		{
			p->RightChild = target->RightChild;
			p->RightThread = true;
		}
		else if (target->RightThread)
		{
			ThreadedNode<T>* largest = target->LeftChild;
			while (!largest->RightThread)
			{
				largest = largest->RightChild;
			}
			largest->RightChild = target->RightChild;
			p->RightChild = target->LeftChild;
		}
		else
		{
			ThreadedNode<T>* smallest = target->RightChild;
			while (!smallest->LeftThread)
			{
				smallest = smallest->LeftChild;
			}
			smallest->LeftChild = p;
			p->RightChild = target->RightChild;
		}
	}
	return true;
}
template <class T>
void ThreadedTree<T>::Inorder()
{
	Inorder(root, root->LeftThread);
}
template <class T>
void ThreadedTree<T>::Inorder(ThreadedNode<T>* CurrentNode, bool b)
{
	if (!b) {
		Inorder(CurrentNode->LeftChild, CurrentNode->LeftThread);
		if (CurrentNode->RightChild != CurrentNode) cout << " " << CurrentNode->data;
		if (CurrentNode->RightChild != root) Inorder(CurrentNode->RightChild, CurrentNode->RightThread);
	}
}

template <class T>
bool ThreadedTree<T>::Insert(T d)//leaf node���� insert, �߰� ��忡 insert �ƴ�
{
	ThreadedNode<T>* p = root;
	ThreadedNode<T>* q = p;
	bool temp = p->LeftThread;
	while (!temp) {
		q = p;
		if (d == p->data) return false;
		if (q->RightChild == q || d < p->data) { 
			temp = p->LeftThread;
			p = p->LeftChild; 
		}
		else { temp = p->RightThread; p = p->RightChild; }
	}
	p = new ThreadedNode<T>;
	p->data = d;
	
	if (q->LeftChild == q){ 
		q->LeftChild = p;
		q->LeftThread = false;
		p->RightChild = p->LeftChild = q;
	}
	else {
		
		if (d < q->data)
		{
			p->RightChild = q; p->RightThread = true;
			p->LeftChild = q->LeftChild; p->LeftThread = q->LeftThread;
			q->LeftChild = p; q->LeftThread = false;
		}
		else
		{
			p->RightChild = q->RightChild; p->RightThread = q->RightThread;
			p->LeftChild = q; p->LeftThread = true;
			q->RightChild = p; q->RightThread = false;
		}
	}
	return true;
}


/* Function to print tree */
template <class T>
void ThreadedTree<T>::PrintTree()
{
	ThreadedNode<T>* tmp = root, * p;
	for (;;)
	{
		p = tmp;
		tmp = tmp->RightChild;
		if (!p->RightThread)
		{
			while (!tmp->LeftThread)
			{
				tmp = tmp->LeftChild;
			}
		}
		if (tmp == root)
			break;
		cout << tmp->data;
	}
	cout << endl;
}

template <class T>
bool ThreadedTree<T>::Search(T data) {
	ThreadedNode<T>* tmp = root, * p;
	for (;;)
	{
		p = tmp;
		tmp = tmp->RightChild;
		if (!p->RightThread)
		{
			while (!tmp->LeftThread)
			{
				tmp = tmp->LeftChild;
			}
		}
		if (tmp == root)
			break;
		if (tmp->data == data)
			return true;
	}
	return false;
}
template <class T>
class ThreadedInorderIterator {
public:
	void Inorder();
	T* Next();
	int Sum();
	ThreadedInorderIterator(ThreadedTree<T> tree) : t(tree) {
		CurrentNode = t.root;
	};
private:
	ThreadedTree<T> t;
	ThreadedNode<T>* CurrentNode;
};

template <class T>
T* ThreadedInorderIterator<T>::Next()
// Find the inorder successor of CurrentNode in a threaded binary tree
{
	ThreadedNode<T>* temp = CurrentNode->RightChild;
	if (!CurrentNode->RightThread)
		while (!temp->LeftThread) temp = temp->LeftChild;
	CurrentNode = temp;
	if (CurrentNode == t.root) return 0; // all tree nodes have been traversed
	else return &CurrentNode->data;
}

template <class T>
void ThreadedInorderIterator<T>::Inorder()
{
	for (T* ch = Next(); ch; ch = Next())
		cout << *ch;
}

template <class T>
int ThreadedInorderIterator<T>::Sum()
{
	int ret = 0;
	for (T* ch = Next(); ch; ch = Next())
		ret += ch->getSalary();
	return ret;
}


enum Enum { Insert = 1, Remove, Inorder, IteratorInorder, Search, PrintTree, Sum, InsertStudent, InorderStudent, Quit };

int main() {
	srand(time(NULL));
	ThreadedTree<Employee> te;
	ThreadedTree<Student> ts;
	ThreadedInorderIterator<Employee> ti(te);
	cout << "ThreadedTree Test\n";
	int select = 0;

	Employee* edata;
	cout << "\nThreadedTree Operations\n";

	while (select != 10)
	{
		cout << "1. Insert list, 2. Remove, 3.Inorder, 4.IteratorInorder, 5.Search, 6.PrintTree, 7.Sum, 8. InsertStudent, 9.InorderStudent, 10.Quit" << endl;
		// postorder traversal
		// preorder traversal
		cout << "Enter Your Choice: ";
		cin >> select;
		int rnd = 0;
		string eno, ename;
		int salary;
		switch (static_cast<Enum>(select))
		{
		case Insert:
		{
			Employee emp[11];
			for (int i = 0; i < 10; i++) {
				Employee* e = new Employee(to_string(i), "A");
				emp[i] = *e;
			}
			//��ü �迭 �ʱ�ȭ�Ͽ� �Է�
			for (int i = 0; i < 10; i++) {
				te.Insert(emp[i]);
			}
			break;
		}
		case Remove:
			cout << "���� �����ȣ �Է�:: ";
			cin >> eno;
			cout << "���� ��� �̸� �Է�:: ";
			cin >> ename;
			cout << "���� ��� �޿� �Է�:: ";
			cin >> salary;
			edata = new Employee(eno, ename, salary);
			/*
			data = new Employee(eno, nullptr);//������ ���� ������ nullptr�� ������ Ÿ���ε� string���� ��ȯ�� ���� ���� ������
			*/
			if (te.Delete(*edata))
				cout << "���� ����" << endl;
			else
				cout << "���� ����" << endl;
			break;
		case Inorder:
			cout << "Recursive Inorder" << endl;
			te.Inorder();
			break;
		case IteratorInorder:
			cout << "IteratorInorder" << endl;
			ti.Inorder();
			break;
		case Search:
			cout << "�˻� �����ȣ �Է�:: ";
			cin >> eno;
			cout << "���� ��� �̸� �Է�:: ";
			cin >> ename;
			edata = new Employee(eno, ename);
			if (te.Search(*edata))//�Էµ� x�� ���� tree ��带 ã�� �����Ѵ�.
				cout << eno << " ���� �����Ѵ�" << endl;
			else
				cout << "���� ����" << endl;

			break;
		case PrintTree:
			cout << "PrintTree " << endl;
			te.PrintTree();
			break;
		case Sum:
			//iterator�� ����� ���� : ��� ����� salary�� ���Ѵ�
			cout << "Sum: " << ti.Sum() << endl;
			break;
		case InsertStudent:
		{
			//��ü �迭 �ʱ�ȭ�Ͽ� �Է�
			Student smp[11];
			for (int i = 0; i < 10; i++) {
				Student* s = new Student(to_string(i), to_string(rand() % 100));
				smp[i] = *s;
			}
			for (int i = 0; i < 10; i++) {
				ts.Insert(smp[i]);
			}
			break;
		}
		case InorderStudent:
			//���
			cout << "Recursive Inorder" << endl;
			ts.Inorder();
			break;
		case Quit:
			cout << "Quit" << endl;
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;

}

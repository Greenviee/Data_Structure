#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100
 
template <class T>
class Set {
public:
	Set(int setCapacity = 10);
	~Set();
	bool IsFull();
	int Size() const; //HowMany( )�� �ش��
	bool IsEmpty() const;
	virtual T& Pop();
	virtual void Push(const T&);
private:
	T* array;
	int capacity;
	int top;
};

template <class T>
Set<T>::Set(int setCapacity) : capacity(setCapacity)
{
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Set<T>::~Set() { delete[] array; }

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)	{
	if (newSize < 0) throw "New length must be >= 0";
	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[] a;
	a = temp;
}

template <class T>
int Set<T>::Size() const {
	return top + 1;
}

template <class T>
bool Set<T>::IsEmpty() const {
	return top < 0;
}

template <class T>
void Set<T>::Push(const T& x)	{
	//�뷮�� �� ���� �ø��� 
	if (top == capacity - 1)
	// ���� ������ ordering ���¿��� push�Ѵ�. non-ordering�ǰ� push�� �����ϰ� ����
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	//�ߺ� ó�� 
	for (int i = 0; i <= top; i++) {
		if (x == array[i]) return;
	}
	array[++top] = x;
}

template <class T>
T& Set<T>::Pop()	{
	T retValue;
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top;
	retValue = array[deletePos];
	// �ǽ� ����: no ordering���·� pop�ǰ� ����
	//copy(array + deletePos + 1, array + top + 1, array + deletePos);
	memcpy(array + deletePos, array + deletePos, top + 1);
	top--;
	return retValue;
}

template <class T>
inline bool Set<T>::IsFull()	{
	if (top == MaxSize - 1) return true;
	else return false;
}

int main() {
	Set<int> s(4);
	//Bag<float> fo(10);�� ���Ͽ��� ������ ��
	//ȭ�鿡�� ���� ���ڸ� �Է¹޾� Push( ) ȣ���ϵ��� ����
	s.Push(3);
	s.Push(5);
	s.Push(1);
	s.Push(6);
	if (s.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}
	while (!s.IsEmpty()) {
		cout << s.Pop() << endl;
	}
	system("pause");
	return 0;
}

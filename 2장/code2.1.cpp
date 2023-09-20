#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100
 
template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();
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

//set�� bag�� �ѹ��� �����ϴ� ��� ������� �ߺ� �ڵ� ���� (set, bag�� �ߺ� �̿��� ���̰� ����)
//set�� �ߺ��� �ȵȴٴ� ������ �����Ƿ� set�� bag�� ���� Ŭ����
template <class T>
class Set : public Bag<T> {
public:
	void Push(const T&);
};

template <class T>
void Set::Push(const T&) {
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
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity)
{
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag() { delete[] array; }

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
int Bag<T>::Size() const {
	return top + 1;
}

 

template <class T>
bool Bag<T>::IsEmpty() const {
	return top < 0;
}

 

template <class T>
void Bag<T>::Push(const T& x)	{
	//�뷮�� �� ���� �ø��� 
	if (top == capacity - 1)
	// ���� ������ ordering ���¿��� push�Ѵ�. non-ordering�ǰ� push�� �����ϰ� ����
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

  
template <class T>
T& Bag<T>::Pop()	{
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
inline bool Bag<T>::IsFull()	{
	if (top == MaxSize - 1) return true;
	else return false;
}

 

int main() {
	Bag<int> b(4);
	//Bag<float> fo(10);�� ���Ͽ��� ������ ��
	//ȭ�鿡�� ���� ���ڸ� �Է¹޾� Push( ) ȣ���ϵ��� ����
	b.Push(3);
	b.Push(5);
	b.Push(1);
	b.Push(6);
	if (b.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}
	while (!b.IsEmpty()) {
		cout << b.Pop() << endl;
	}
	system("pause");
	return 0;
}

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
	int Size() const; //HowMany( )에 해당됨
	bool IsEmpty() const;
	virtual T& Pop();
	virtual void Push(const T&);
private:
	T* array;
	int capacity;
	int top;
};

//set과 bag를 한번에 구현하는 경우 상속으로 중복 코딩 제거 (set, bag은 중복 이외의 차이가 없음)
//set이 중복이 안된다는 제약이 있으므로 set이 bag의 하위 클래스
template <class T>
class Set : public Bag<T> {
public:
	void Push(const T&);
};

template <class T>
void Set::Push(const T&) {
	//용량이 다 차면 늘리기 
	if (top == capacity - 1)
		// 현재 버젼은 ordering 상태에서 push한다. non-ordering되게 push가 가능하게 수정
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	//중복 처리 
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
	//용량이 다 차면 늘리기 
	if (top == capacity - 1)
	// 현재 버젼은 ordering 상태에서 push한다. non-ordering되게 push가 가능하게 수정
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
	// 실습 사항: no ordering상태로 pop되게 수정
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
	//Bag<float> fo(10);에 대하여도 구현할 것
	//화면에서 임의 숫자를 입력받아 Push( ) 호출하도록 수정
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

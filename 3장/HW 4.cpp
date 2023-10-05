//소스 코드3.4: Mazing Problem
#pragma once
#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100

template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag( );
	bool IsFull( );
	int Size( ) const;
	bool IsEmpty( ) const;
	virtual T& Pop( ) const;
	virtual void Push(const T&);
private:
	T* array;
	int capacity;
	int top;
};

//Visual Studio2019에서 bag.h, bag.cpp로 분리하지 않아야 함
template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity)
{
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag( ) { delete[ ] array; }

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[ ] a;
	a = temp;
}

template <class T>
int Bag<T>::Size( ) const {
	return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty( ) const {
	return top < 0;
}

template <class T>
void Bag<T>::Push(const T& x)
{
	if (top == capacity - 1)
		// 현재 버젼은 ordering 상태에서 push한다. non-ordering되게 push가 가능하게 수정
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

template <class T>
T& Bag<T>::Pop( ) const
{
	T retValue;
	if (IsEmpty( )) throw "Bag is empty, cannot delete";
	int deletePos = top / 2;
	retValue = array[deletePos];
	// 실습 사항: no ordering상태로 pop되게 수정
	//copy(array + deletePos + 1, array + top + 1, array + deletePos);
	memcpy(array + deletePos, array + deletePos, top + 1);
	top--;
	return retValue;
}

template <class T>
inline bool Bag<T>::IsFull( )
{
	if (top == MaxSize - 1) return TRUE;
	else return FALSE;
}

#pragma once
#include <iostream>
#include "bagTemplate.h"
#include <memory>

using namespace std;
template <class T>
class Stack : public Bag<T>
{
public:
	Stack(int MaxStackSize = DefaultSize);
	T& Pop( ) const;
	void Push(const T&);
	//friend를 template에 사용시 사용법
	template <class T> 
	friend ostream& operator<<(ostream& os, const Stack<T>& s);
	template <class T>
	friend ostream& operator<<(ostream& os, items& item);
private:
	void StackEmpty( ) { cout << "Stack is empty" << endl; };
	void StackFull( ) { cout << "Stack is full" << endl; };
};

//Visual Studio2019에서 bag.h, bag.cpp로 분리하지 않아야 함
template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) cout<<"Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
T& Stack<T>::Pop( ) const
{
	if (IsEmpty( )) StackEmpty( ); 
	return Bag<T>::Pop( );
}

template <class T>
void Stack<T>::Push(const T& t)
{
	if (IsFull( )) StackFull( );
	Bag<T>::Push(t);
}

template <class T>
Stack<T>::Stack(int MaxStackSize) : MaxSize(MaxStackSize)
{
	stack = new T[MaxSize];
	top = -1;
}

template <class T>
ostream& operator<<(ostream& os, const Stack<T>& s)
{
	os << "top = " << s.top << endl;
	os << "stack elements: from the bottom to the top: " << endl;
	for (int i = 0; i <= s.top; i++)
		os << i << ":" << s.stack[i] << endl;
	return os;
}

//3.5 a mazing problem
#include <iostream>
#include <fstream>
#include "stackTemplate.h"
using namespace std;

const int DefaultSize = 100;

struct items {
	int x, y, dir;
};

ostream& operator<<(ostream& os, items& item)
{
	return os << item.x << "," << item.y << "," << item.dir;
}

struct offsets {
	int a, b;
};

enum directions { N, NE, E, SE, S, SW, W, NW };
offsets moves[8];
int maze[100][100];
int mark[100][100];

void path(int m, int p)
// Output a path (if any) in the maze; rows is m, cols is p;
{
	//start at (1,1)
	mark[1][1] = 1;
	Stack<items> stack(m * p);
	items temp;
	temp.x = 1; temp.y = 1; temp.dir = E;
	stack.Push(temp);

	while (!stack.IsEmpty( )) // stack not empty
	{
		temp = stack.Pop( ); // unstack
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8) // moves forward
		{
			//outFile << i << " " << j << " " << d << endl;
			int g = i + moves[d].a;
			int h = j + moves[d].b;
			if ((g == m) && (h == p)) { // reached exit// output path
				cout << stack;

				cout << "the term near the exit: " << i << " " << j << endl;
				cout << "exit: " << m << " " << p << endl;
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) { // new position
				mark[g][h] = 1;
				//push the old temp to the stack, but the direction changes.
				//Because the neighbor in the direction of d has been checked.
				temp.x = i;  temp.y = j; temp.dir = d + 1;
				stack.Push(temp); // stack it
				i = g; j = h; d = N; // moves to (g,h)
			}
			else d++; // try next direction
		}
	}
	cout << "no path in maze " << endl;
}
/*
maze[ ][ ], mark[ ][ ]를 class의 private data member로 선언
main( )에서는 class의 public function의 호출로 미로 찾기
*/
void main( ) {
	int input[12][15] = {
	{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 },
	{ 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 },
	};

	moves[N].a = -1; moves[N].b = 0;
	moves[NE].a = -1; moves[NE].b = 1;
	moves[E].a = 0; moves[E].b = 1;
	moves[SE].a = 1; moves[SE].b = 1;
	moves[S].a = 1; moves[S].b = 0;
	moves[SW].a = 1; moves[SW].b = -1;
	moves[W].a = 0; moves[W].b = -1;
	moves[NW].a = -1; moves[NW].b = -1;


	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 17; j++)
		{
			if ((!i) || (!j) || (i == 13) || (j == 16))
				maze[i][j] = 1;
			else {
				maze[i][j] = input[i - 1][j - 1];
			};
			mark[i][j] = 0;

		}
	}
	for (int i = 0; i <= 13; i++)
	{
		for (int j = 0; j <= 16; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	path(12, 15);

	int end;
	cin >> end;
}

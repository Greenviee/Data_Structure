//모든 해 구하기 
#include <iostream>
#include <cmath>
#define ROW 8
#define COL 8
using namespace std;
class Point {
private:
	int ix;
	int iy;
public:
	Point() { ix = 0; iy = 0; }
	Point(int x, int y) {
		ix = x;
		iy = y;
	}
	int getX() {
		return ix;
	}
	int getY() {
		return iy;
	}
	void setX(int x) {
		ix = x;
	}
	void setY(int y) {
		iy = y;
	}
	friend ostream& operator<<(ostream& os, Point px);
};

ostream& operator<<(ostream& os, Point px) {
	os << "(" << px.ix << ", " << px.iy << ")" << endl;
	return os;
}
template <class T>
class Stack {
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	T& Pop();
	friend ostream& operator<<<T>(ostream& os, Stack<T>&);
	friend istream& operator>><T>(istream& os, Stack<T>&);
private:
	T* stack;
	int top;
	int capacity;
};
template <class T>
ostream& operator<<(ostream& os, Stack<T>& s) {
	return os;
}
template <class T>
istream& operator>>(istream& os, Stack<T>& s) {
	return os;
}
template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
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
inline bool Stack<T>::IsEmpty() const { return top == -1; }

template <class T>
inline T& Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];
}

template <class T>
void Stack<T>::Push(const T& x)
{
	if (top == capacity - 1)
	{
		ChangeSizeID(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template <class T>
T& Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	return stack[top--];
}
bool checkRow(int d[][COL], int crow) {/ 
	for (int i = 0; i < COL; i++) 
		if (d[i][crow]==1) return false;
	return true;
}

bool checkCol(int d[][COL], int ccol) {
	for (int i = 0; i < ROW; i++) 
		if (d[ccol][i]==1) return false;
	return true;
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++ where 0<= x,y <= 7
	int x = cx + 1, int y = cy - 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if (d[x][y] == 1) return false;
		x++; y--;
	} 
	x = cx - 1; y = cy + 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if(d[x][y] = 1) return false;
			x--; y++;
	}
	return true;
}

bool checkDiagSE(int d[][COL], int cx, int cy) {// x++, y++ or x--, y--
	int x = cx + 1, int y = cy + 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if (d[x][y] == 1) return false;
		x++; y++;
	} 
	x = cx - 1; y = cy - 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if(d[x][y] = 1) return false;
			x--; y--;
	}
	return true;
}

bool checkMove(int d[][COL], int x, int y) {//d에서 퀸을 (x,y)에 놓을 수 있는가? 
	return checkRow(d, x) && checkCol(d, y) && checkDiagSW(d, x, y) && checkDiagSE(d, x, y); 
}

int nextMove(int d[][COL], int row, int col) {//다음 행에서 퀸을 놓을 수 있는 가장 빠른 위치 
	for (int nextCol = 0; nextCol < 7; nextCol++)
		if (checkMove(d, row, nextCol)) return nextCol;
	return -1;
}
//Board 출력 
void showQueens(int data[][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (data[COL][ROW] == 1) cout << 'Q';
			else cout << '-';
		}
		cout << endl;
	}
}
//non-recursive 
void solveQueen(int d[][COL]) {
	int x = 0, y = 0;
	//놓은 퀸의 개수 
	int cnt = 0;
	Point p(x, y) 
	d[p.ix][p.iy] = 1; //(x, y)에 배치 
	Stack st;
	st.Push(p);
	
}



void main() {
	const int row = ROW, col = COL;
	int data[row][col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			data[i][j] = 0;

	solveQueen(data);
	system("pause");
	return;
}


#include <iostream>
#include <cmath>
#define ROW 8
#define COL 8
using namespace std;

class Point {
private:
	int ix;
	int iy;
	friend void solveQueen(int d[][COL]);
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
	friend ostream& operator<<(ostream& os, Stack<T>&);
	friend istream& operator>>(istream& os, Stack<T>&);
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
bool checkRow(int d[][COL], int crow) {
	for (int i = 0; i < COL; i++) 
		if (d[i][crow] == 1) return false;
	return true;
}

bool checkCol(int d[][COL], int ccol) {
	for (int i = 0; i < ROW; i++) 
		if (d[ccol][i] == 1) return false;
	return true;
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++ where 0<= x,y <= 7
	int x = cx + 1; int y = cy - 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if (d[x][y] == 1) return false;
		x++; y--;
	} 
	x = cx - 1; y = cy + 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if(d[x][y] == 1) return false;
		x--; y++;
	}
	return true;
}

bool checkDiagSE(int d[][COL], int cx, int cy) {// x++, y++ or x--, y--
	int x = cx + 1; int y = cy + 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if (d[x][y] == 1) return false;
		x++; y++;
	} 
	x = cx - 1; y = cy - 1;
	while((0 <= x && x <= 7) && (0 <= y && y <= 7)) {
		if(d[x][y] == 1) return false;
		x--; y--;
	}
	return true;
}

bool checkMove(int d[][COL], int x, int y) {//d에서 퀸을 (x,y)에 놓을 수 있는가? 
	return (checkRow(d, x) && checkCol(d, y) && checkDiagSW(d, x, y) && checkDiagSE(d, x, y)); 
}

int nextMove(int d[][COL], int row, int col) {//다음 행에서 col 부터 퀸을 놓을 수 있는 가장 빠른 위치 
	//마지막 열인 경우  
	if (row == ROW - 1) return -1; 
	
	for (int nextCol = col; nextCol < 8; nextCol++)
		if (checkMove(d, nextCol, row + 1)) return nextCol;
	return -1;
}
//Board 출력 
void showQueens(int data[][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (data[i][j] == 1) cout << 'Q';
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
	Point p(x, y);
	d[p.ix][p.iy] = 1; //(x, y)에 배치 
	Stack<Point> st;
	st.Push(p);
	cnt++;
	while (!st.IsEmpty()) {
		if (cnt == 8) showQueens(d);
		//만약 다음 열에서 놓을 공간이 없는 경우
		if (nextMove(d, st.Top().iy, 0) == -1) {
			//지금 열에서 놓을 수 있는 다음 위치 push
			int next = nextMove(d, st.Top().iy - 1, st.Top().ix + 1);
			//지금 열에 더이상 놓을 수 있는 퀸이 없는 경우 
			if(next == -1) {
				d[st.Top().iy][st.Top().ix] = 0;
				st.Pop();
				cnt--;
				//이전 열에 놓인 퀸 이동 
				int before = nextMove(d, st.Top().iy - 1, st.Top().ix + 1);	
				//이전 열에 더 이상 놓을 수 있는 공간이 없는 경우	
				if (before == -1) {
					while (before == -1) {
						d[st.Top().iy][st.Top().ix] = 0;
						st.Pop();
						if (st.IsEmpty()) return;
						cnt--;
						before = nextMove(d, st.Top().iy - 1, st.Top().ix + 1);
					}
				}		 
				Point n(before, st.Top().iy);
				d[st.Top().iy][st.Top().ix] = 0;
				st.Pop();
				st.Push(n);
				d[st.Top().iy][st.Top().ix] = 1;
			} 
			//있는 경우 다음 칸에 퀸 배치 
			else {
				Point n(next, st.Top().iy);
				d[st.Top().iy][st.Top().ix] = 0;
				st.Pop();
				st.Push(n);
				d[st.Top().iy][st.Top().ix] = 1;
			}
		}
		//다음 열에 퀸을 놓을 공간이 있는 경우 
		else {
			int next = nextMove(d, st.Top().iy, 0);
			Point next_queen(next, st.Top().iy + 1);
			st.Push(next_queen);
			d[st.Top().iy][st.Top().ix] = 1;
			cnt++;
			showQueens(d);
			cout << endl;
		} 
	}
}



int main() {
	const int row = ROW, col = COL;
	int data[row][col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			data[i][j] = 0;
	solveQueen(data);
	system("pause");
	return 0;
}

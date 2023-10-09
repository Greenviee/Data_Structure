#include <iostream>
#include <cstring>
using namespace std;

const int DefaultSize = 100;

template <class T>
class Bag {
public:
    Bag(int bagCapacity = 10);
    ~Bag();
    bool IsFull();
    int Size() const;
    bool IsEmpty() const;
    virtual T& Pop();
    virtual void Push(const T&);
protected: // Bag 클래스에서 멤버에 접근하기 위해 protected로 변경
    T* array;
    int capacity;
    int top;
};

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
int Bag<T>::Size() const {
    return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const {
    return top < 0;
}

template <class T>
void Bag<T>::Push(const T& x)
{
    if (top == capacity - 1)
    {
        ChangeSizeID(array, capacity, 2 * capacity);
        capacity *= 2;
    }
    array[++top] = x;
}

template <class T>
T& Bag<T>::Pop()
{
    T retValue;
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = top / 2;
    retValue = array[deletePos];
    memcpy(array + deletePos, array + deletePos + 1, (top - deletePos) * sizeof(T));
    top--;
    return retValue;
}

template <class T>
inline bool Bag<T>::IsFull()
{
    return top == capacity - 1;
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T* temp = new T[newSize];
    int number = oldSize;
    if (oldSize > newSize) number = newSize;
    memcpy(temp, a, number * sizeof(T));
    delete[] a;
    a = temp;
}

template <class T>
class Stack : public Bag<T>
{
public:
    Stack(int MaxStackSize = DefaultSize);
    T& Pop();
    void Push(const T&);
private:
    void StackEmpty() { cerr << "Stack is empty" << endl; }
    void StackFull() { cerr << "Stack is full" << endl; }
};

template <class T>
Stack<T>::Stack(int stackCapacity) : Bag<T>(stackCapacity)
{
    if (stackCapacity < 1) cerr << "Stack capacity must be > 0";
    Bag<T>::array = new T[stackCapacity];
    Bag<T>::top = -1;
}

template <class T>
T& Stack<T>::Pop()
{
    if (Bag<T>::IsEmpty()) StackEmpty();
    return Bag<T>::Pop();
}

template <class T>
void Stack<T>::Push(const T& t)
{
    if (Bag<T>::IsFull()) StackFull();
    Bag<T>::Push(t);
}

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
int road[100][100];

void viewMaze() {
    for (int i = 1; i < 13; i++) {
        for (int j = 1; j < 16; j++) {
            if (road[i][j] == 1) cout << 2 << ' ';
            else cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
}

void path(int m, int p)
{
    mark[1][1] = 1;
    road[1][1] = 1;
    Stack<items> stack(m * p);
    items temp;
    temp.x = 1; temp.y = 1; temp.dir = E;
    stack.Push(temp);

    while (!stack.IsEmpty()) {
        temp = stack.Pop();
        int i = temp.x; int j = temp.y; int d = temp.dir;
        while (d < 8) {
            int g = i + moves[d].b;
            int h = j + moves[d].a;
            if ((h == m) && (g == p)) {
                road[h][g] = 1;
                road[j][i] = 1;
                while (!stack.IsEmpty()) {
                    items T = stack.Pop();
                    road[T.y][T.x] = 1;
                }
                viewMaze();
                return;
            }
            if ((!maze[h][g]) && (!mark[h][g])) {
                mark[h][g] = 1;
                temp.x = i; temp.y = j; temp.dir = d + 1;
                stack.Push(temp);
                i = g; j = h; d = N;
            }
            else d++;
        }
    }
    cout << "no path in maze " << endl;
}

int main() {
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
            road[i][j] = 0;
        }
    }

    path(12, 15);

    int end;
    cin >> end;
    return 0;
}

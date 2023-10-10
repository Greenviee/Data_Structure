//책에 있는 예제 파일에서 Pop()이 제대로 작동하지 않아서 STL 사용하였습니다. 
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

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
    stack<items> st;
    items temp;
    temp.x = 1; temp.y = 1; temp.dir = E;
    st.push(temp);

    while (!st.empty()) {
        temp = st.top();
        st.pop();
        int i = temp.x; int j = temp.y; int d = temp.dir;
        while (d < 8) {
            int g = i + moves[d].b;
            int h = j + moves[d].a;
            if ((h == m) && (g == p)) {
                road[h][g] = 1;
                road[j][i] = 1;
                while (!st.empty()) {
                    items T = st.top();
                    st.pop();
                    road[T.y][T.x] = 1;
                }
                viewMaze();
                return;
            }
            if ((!maze[h][g]) && (!mark[h][g])) {
                mark[h][g] = 1;
                temp.x = i; temp.y = j; temp.dir = d + 1;
                st.push(temp);
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

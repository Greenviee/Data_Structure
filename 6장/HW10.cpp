#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Edge;

class MinHeap {
public:
	virtual void Insert(Edge* x) = 0;
	virtual Edge* DeleteMin() = 0;
};

class Edge {
public:
	int src = 0;
	int dest = 0;
	int weight = 0;
	Edge() {};
	Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
	friend ostream& operator<<(ostream& os, Edge& x);
	int compare(Edge& x) {
		if (weight == x.weight)
			return 0;
		else if (weight < x.weight)
			return -1;
		else
			return 1;
	}
};

ostream& operator<<(ostream& os, Edge& x) {
	os << "시작 지점: " << x.src << " 도착 지점: " << x.dest << " 가중치: " << x.weight << endl;
	return os;
}

class Heap : public MinHeap {
public:
	const int heapSize = 100;
	Heap(int sz) : MaxSize(sz) {
		n = 0;
		heap = new Edge[MaxSize + 1];
	}
	virtual void display();
	void Insert(Edge* x);
	Edge* DeleteMin();
	void HeapEmpty();
	void HeapFull();
	bool isEmpty();
private:
	int n = 0;
	int MaxSize = 0;
	Edge* heap;
};

void Heap::display() {
	for (int i = 1; i <= n; i++)
		cout << heap[i];
}

void Heap::Insert(Edge* x) {
	int i;
	if (n == MaxSize) {
		HeapFull();
		return;
	}
	n++;
	for (i = n; i >= 1;) {
		if ((i == 1) || (x->compare(heap[i / 2]) > -1))
			break;
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = *x;
}

Edge* Heap::DeleteMin() {
	Edge x;
	int i, j;
	if (n == 0) {
		HeapEmpty();
		Edge* elm = nullptr;
		return elm;
	}
	x = heap[1];
	Edge k = heap[n];
	n--;
	for (i = 1, j = 2; j <= n;) {
		if (j < n)
			if (heap[j].compare(heap[j + 1]) > 0)
				j++;
		if (k.compare(heap[j]) < 0)
			break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

void Heap::HeapEmpty() {
	cout << "Hea Empty" << endl;
}

void Heap::HeapFull() {
	cout << "Heap Full" << endl;
}

bool Heap::isEmpty() {
	if (n == 0)
		return true;
	return false;
}

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class ListNode {
	friend class List<T>;
	friend class ListIterator<T>;
	friend class Graph;
private:
	T data;
	int weight;
	ListNode* link;
	ListNode(T);
};

template <class T>
ListNode<T>::ListNode(T Default) {
	data = Default;
	weight = 0;
	link = nullptr;
}

template <class T>
class List {
	friend class ListIterator<T>;
	friend class Graph;
public:
	List() { first = 0; }
	void Insert(T k, int weight);
	void Delete(T);
private:
	ListNode<T>* first;
};

template <class T>
void List<T>::Insert(T k, int weight) {
	ListNode<T>* newNode = new ListNode<T>(k);
	newNode->weight = weight;
	newNode->link = first;
	first = newNode;
}

template <class T>
void List<T>::Delete(T k) {
	ListNode<T>* p = nullptr;
	ListNode<T>* current;
	for (current = first; current && current->data != k; p = current, current = current->link);
	if (current) {
		if (p) p->link = current->link;
		else first = first->link;
		delete current;
	}
}

template <class T>
class ListIterator {
public:
	ListIterator(const List<T>& l) : list(l) { current = l.first; }
	T* First();
	T* Next();
	bool NotNull();
	bool NextNotNull();
private:
	const List<T>& list;
	ListNode<T>* current;
};

template <class T>
T* ListIterator<T>::First() {
	if (current) return &current->data;
	else return 0;
}

template <class T>
T* ListIterator<T>::Next() {
	current = current->link;
	return &current->data;
}

template <class T>
bool ListIterator<T>::NotNull() {
	if (current) return true;
	else return false;
}

template <class T>
bool ListIterator<T>::NextNotNull() {
	if (current->link) return true;
	else return false;
}

ostream& operator<<(ostream& os, List<char>& l) {
	ListIterator<char> li(l);
	if (!li.NotNull()) return os;
	os << *li.First() << endl;
	while (li.NextNotNull())
		os << *li.Next() << endl;
	return os;
}

class Graph {
private:
	List<int>* HeadNodes;
	int n;
	bool* visited;
public: 
	Graph(int vertices = 0) : n(vertices) {
		HeadNodes = new List<int>[n];
	}
	void InsertVertex(int startNode, int endNode, int weight);
	void displayAdjacencyLists();
	int getn() { return n; }
	int makeEdgeSet(Edge* edgeSet, int e);
	Edge* getNextEdge(bool* visited);
};

void Graph::displayAdjacencyLists() {
	for (int i = 0; i < n; i++) {
		ListIterator<int> iter(HeadNodes[i]);
		if (!iter.NotNull()) {
			cout << i << " -> null" << endl;
			continue;
		}
		cout << i;
		for (int* first = iter.First(); iter.NotNull(); first = iter.Next())
			cout << " -> " << (*first);
		cout << endl;
	}
}

void Graph::InsertVertex(int start, int end, int weight) {
	if (start < 0 || start >= n || end < 0 || end >= n) {
		cout << "the start node number is out of bound.";
		throw "";
	}
	ListIterator<int> iter(HeadNodes[start]);
	for (int* first = iter.First(); iter.NotNull(); first = iter.Next())
		if (*first == end) return;
	HeadNodes[start].Insert(end, weight);
	HeadNodes[end].Insert(start, weight);
}

class Sets {
public:
	Sets(int sz = 100) {
		n = sz;
		parent = new int[sz + 1];
		for (int i = 0; i <= n; i++)
			parent[i] = i;
	}
	void display();
	void SimpleUnion(int, int);
	int SimpleFind(int);
private:
	int* parent;
	int n;
};

void Sets::SimpleUnion(int i, int j) {
	i = SimpleFind(i);
	j = SimpleFind(j);
	if (i < j) parent[j] = i;
	else parent[i] = j;
}

int Sets::SimpleFind(int i) {
	if (parent[i] == i)
		return i;
	return parent[i] = SimpleFind(parent[i]);
}

void Sets::display() {
	cout << "display:index = ";
	for (int i = 1; i <= n; i++)
		cout << " " << i;
	cout << endl;
	cout << "display:value = ";
	for (int i = 1; i <= n; i++)
		cout << " " << parent[i];
	cout << endl;
}

int addEdgeSet(Edge* edgeSet, int e, int from, int to, int w) {
	for (int i = 0; i < e; i++)
		if ((edgeSet[i].src == from) && (edgeSet[i].dest == to))
			return 0;
	edgeSet[e].src = from;
	edgeSet[e].dest = to;
	edgeSet[e].weight = w;
	e++;
	return e;
}

int Graph::makeEdgeSet(Edge* edgeSet, int e) {
	int result = 0;
	for (int i = 0; i < n; i++) {
		ListNode<int>* p = HeadNodes[i].first;
		while(p != nullptr) {
			if (p->data > i)
				result = addEdgeSet(edgeSet, e, i, p->data, p->weight);
			if (result != 0)
				e = result;
			p = p->link;
		}
	}
	return e;
}

void KruskalMST(Graph graph, int n) {
	Edge* edgeSet = new Edge[30];
	Edge* result = new Edge[30];
	int t = 0;
	int edgeNum = 0;
	edgeNum = graph.makeEdgeSet(edgeSet, edgeNum);
	Heap* hp = new Heap(100);
	for (int i = 0; i < edgeNum; i++)
		hp->Insert(&edgeSet[i]);
	Sets* m = new Sets(20);
	while (t < n - 1) {
		Edge* nextEdge = hp->DeleteMin();
		if (nextEdge == nullptr)
			break;
		int from = nextEdge->src, to = nextEdge->dest;
		if (m->SimpleFind(from) == m->SimpleFind(to))
			continue;
		m->SimpleUnion(from, to);
		result[t++] = *nextEdge;
	}
	if (t < n - 1) {
		cout << "no spanning tree" << endl;
		return;
	}
	for (int k = 0; k < t; k++)
		cout << result[k];
	return;
}

Edge* Graph::getNextEdge(bool* visited) {
	Edge* minEdge = nullptr;
	int maxWeight = 9999;
	ListNode<int>* p;
	for (int i = 0; i < n; i++) {
		if (visited[i]) {
			p = HeadNodes[i].first;
			while (p != nullptr) {
				if (p->weight < maxWeight && !visited[p->data]) {
					maxWeight = p->weight;
					minEdge = new Edge(i, p->data, p->weight);
				}
				p = p->link;
			}
		}
	}
	if (minEdge != nullptr)
		visited[minEdge->src] = visited[minEdge->dest] = true;
	return minEdge;
}

void Prim(Graph graph, int n) {
	Edge* edgeSet = new Edge[30];
	Edge* result = new Edge[30];
	int t = 0;
	int edgeNum = 0;
	edgeNum = graph.makeEdgeSet(edgeSet, edgeNum);
	Heap* hp = new Heap(100);
	for (int j = 0; j < edgeNum; j++)
		hp->Insert(&edgeSet[j]);
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;
	visited[0] = true;
	Edge* nextEdge = graph.getNextEdge(visited);
	while(t < n - 1) {
		if (nextEdge == nullptr)
			break;
		int from = nextEdge->src, to = nextEdge->dest;
		visited[from] = visited[to] = true;
		result[t++] = *nextEdge;
		nextEdge = graph.getNextEdge(visited);
	}
	if (t < n - 1) {
		cout << "no spanning tree" << endl;
		return;
	}
	for (int k = 0; k < t; k++)
		cout << result[k];
	delete[] visited;
	visited = nullptr;
}

void Sollin(Graph graph, int n) {
	Edge* edgeSet = new Edge[30];
	Edge* result = new Edge[30];
	int t = 0;
	int edgeNum = 0;
	edgeNum = graph.makeEdgeSet(edgeSet, edgeNum);
	Heap* hp = new Heap(100);
	Heap* hp2 = new Heap(100);
	for (int j = 0; j < edgeNum; j++)
		hp->Insert(&edgeSet[j]);
	Sets* m = new Sets(20);
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;
	Edge* p = hp->DeleteMin();
	//from과 to가 !visited[]인 Edge만 result에 추가
	while (!hp->isEmpty()) {
		int from = p->src, to = p->dest;
		if (!visited[from] || !visited[to]) {
			result[t++] = *p;
			visited[from] = visited[to] = true;
			m->SimpleUnion(from, to);
		}
		else {
			hp2->Insert(p);
		}
		p = hp->DeleteMin();
	}
	Edge* q = hp2->DeleteMin();
	while (t < n - 1) {
		if (q == nullptr)
			break;
		int from = q->src, to = q->dest;
		if (m->SimpleFind(from) == m->SimpleFind(to)) {
			q = hp2->DeleteMin();
			continue;
		}
		m->SimpleUnion(from, to);
		visited[from] = visited[to] = true;
		result[t++] = *q;
		q = hp2->DeleteMin();
	}
	if (t < n - 1) {
		cout << "no spanning tree" << endl;
		return;
	}
	for (int k = 0; k < t; k++)
		cout << result[k];
}

int main() {
	int select = 0, n, weight;
	int startBFSNode = 100;
	int startEdge, endEdge;
	cout << "Input the total node number: ";
	cin >> n;
	Graph graph(n);
	while (select != 6) {
		cout << "명령선택:: 1.edges/Weight 입력, 2. Adjacency Lists 출력, 3. KruskalMST, 4. PrimMST, 5. Sollin, 6. Quit =>";
		cin >> select;
		switch (select) {
		case 1:
			cout << "edge 추가: from vertext: ";
			cin >> startEdge;
			cout << "to vertex: ";
			cin >> endEdge;
			cout << "가중치: ";
			cin >> weight;
			if (startEdge < 0 || startEdge >= n || endEdge < 0 || endEdge >= n) {
				cout << "the input node is out of bound." << endl;
				break;
			}
			if (startEdge < startBFSNode)
				startBFSNode = startEdge;
			if (endEdge < startBFSNode)
				startBFSNode = endEdge;
			graph.InsertVertex(startEdge, endEdge, weight);
			/*
			교재에 있는 그래프 테스트
			graph.InsertVertex(0, 1, 28);
			graph.InsertVertex(0, 5, 10);
			graph.InsertVertex(1, 2, 16);
			graph.InsertVertex(1, 6, 14);
			graph.InsertVertex(6, 3, 18);
			graph.InsertVertex(2, 3, 12);
			graph.InsertVertex(3, 4, 22);
			graph.InsertVertex(4, 5, 25);
			graph.InsertVertex(4, 6, 24);
			*/
			break;
		case 2:
			graph.displayAdjacencyLists();
			break;
		case 3:
			cout << "Minimal Spanning Tree 작업 시작" << endl;
			KruskalMST(graph, n);
			break;
		case 4:
			cout << "Minimal Spanning Tree 작업 시작" << endl;
			Prim(graph, n);
			break;
		case 5:
			cout << "Minimal Spanning Tree 작업 시작" << endl;
			Sollin(graph, n);
			break;
		case 6:
			break;
		}
	}
	system("pause");
}

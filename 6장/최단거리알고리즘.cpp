#include <iostream>
#include <string>
#include <memory>
using namespace std;
#define INF 987654321

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
	void Dijkstra(int start);
	void BellmanFord(int start);
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
}

void Graph::Dijkstra(int start) {
	int dist[101];
	int visited[101];
	for (int i = 0; i < n; i++) {
		dist[i] = INF;
		visited[i] = false;
	}
	visited[start] = true;
	dist[start] = 0;
	ListNode<int>* p = HeadNodes[start].first;
	while (p != nullptr) {
		dist[p->data] = p->weight;
		p = p->link;
	}
	for (int i = 0; i < n - 1; i++) {
		int minimum = INF, minNode = 0;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (dist[j] < minimum)) {
				minimum = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = true;
		ListNode<int>* q = HeadNodes[minNode].first;
		while (q != nullptr) {
			if (!visited[q->data])
				if (dist[minNode] + q->weight < dist[q->data])
					dist[q->data] = dist[minNode] + q->weight;
			q = q->link;
		}
	}
	for (int i = 0; i < n; i++)
		cout << "dist[" << i << "] : " << dist[i] << endl;
}

void Graph::BellmanFord(int start) {
	int dist[101];
	int visited[101];
	for (int i = 0; i < n; i++) {
		dist[i] = INF;
		visited[i] = false;
	}
	visited[start] = true;
	dist[start] = 0;
	ListNode<int>* p = HeadNodes[start].first;
	while (p != nullptr) {
		dist[p->data] = p->weight;
		p = p->link;
	}
	for (int i = 0; i < n - 1; i++) {
		int minimum = INF, minNode = 0;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (dist[j] < minimum)) {
				minimum = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = true;
		ListNode<int>* q = HeadNodes[minNode].first;
		while (q != nullptr) {
			if (dist[minNode] + q->weight < dist[q->data])
				dist[q->data] = dist[minNode] + q->weight;
			q = q->link;
		}
	}
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}
	visited[start] = true;
	for (int i = 0; i < n - 1; i++) {
		int minimum = INF, minNode = 0;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (dist[j] < minimum)) {
				minimum = dist[j];
				minNode = j;
			}
		}
		visited[minNode] = true;
		ListNode<int>* q = HeadNodes[minNode].first;
		while (q != nullptr) {
			if (dist[minNode] + q->weight < dist[q->data]) {
				cout << "Graph has negative cycle" << endl;
				return;
			}
				
			q = q->link;
		}
	}
	for (int i = 0; i < n; i++)
		cout << "dist[" << i << "] : " << dist[i] << endl;
}

int main() {
	int select = 0, n, weight;
	int startBFSNode = 100;
	int startEdge, endEdge;
	cout << "Input the total node number: ";
	cin >> n;
	Graph graph(n);
	while (select != 5) {
		cout << "명령선택:: 1.edges/Weight 입력, 2. Adjacency Lists 출력, 3. Dijkstra, 4. BellmanFord, 5. Quit =>";
		cin >> select;
		switch (select) {
		case 1:
			graph.InsertVertex(0, 1, 4);
			graph.InsertVertex(0, 2, 2);
			graph.InsertVertex(1, 4, 5);
			graph.InsertVertex(2, 4, 4);
			graph.InsertVertex(1, 3, 4);
			graph.InsertVertex(3, 5, 1);
			graph.InsertVertex(4, 5, 2);
			break;
		case 2:
			graph.displayAdjacencyLists();
			break;
		case 3:
			graph.Dijkstra(0);
			break;
		case 4:
			graph.BellmanFord(0);
			break;
		case 5:
			break;
		}
	}
	system("pause");
}
#include <iostream>
#include <string>
using namespace std;

class Pair {
public:
	int vertex, dur;
	Pair() {}
	Pair(int vertex, int dur) : vertex(vertex), dur(dur) {}
};

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class ListNode {
	friend class List<T>;
	friend class ListIterator<T>;
private:
	T data;
	ListNode* link;
	ListNode(T);
};

template <class T>
ListNode<T>::ListNode(T Default) {
	data = Default;
	link = 0;
}

template <class T>
class List {
	friend class ListIterator<T>;
public:
	List() { first = 0; }
	void Insert(T);
	void Delete(T);
private:
	ListNode<T>* first;
};

template <class T>
void List<T>::Insert(T k) {
	ListNode<T>* newNode = new ListNode<T>(k);
	newNode->link = first;
	first = newNode;
}

template <class T>
void List<T>::Delete(T k) {
	ListNode<T>* p = 0;
	ListNode<T>* current;
	for (first; current && current->data != k; p = current, current = current->link);
	if (current) {
		if (p) p->link = current->link;
		else first = current->link;
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
	current = list.first;
	return &current->data;
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

template <class T>
ostream& operator<<(ostream& os, List<char>& l) {
	ListIterator<char> li(l);
	if (!li.NotNull()) return os;
	os << *li.First() << endl;
	while (li.NextNotNull()) {
		os << *li.Next() << endl;
	}
	return os;
}

class Graph {
private:
	List<Pair>* HeadNodes;
	int* count;
	int* ee;
	int* le;
	int n;
public:
	Graph(const int vertices = 0) : n(vertices) {
		HeadNodes = new List<Pair>[n];
		count = new int[n];
		ee = new int[n];
		le = new int[n];
		for (int i = 0; i < n; i++) {
			count[i] = 0;
			ee[i] = 0;
			le[i] = 0;
		}
	}
	~Graph() {
		delete[] count;
		delete[] ee;
		delete[] le;
		delete[] HeadNodes;
	}
	void Setup4();
	void EarlyActivity();
	void EarlyActivity_display();
	void LateActivity();
	void LateActivity_display();
	void StartActivity_display();

	void display_early_late_criticalActivity();
	void TopologicalOrder();
	void addEdge(int start, int end, int duration);
	void printAdjacencyLists();
	Graph* inverseGraph() const;
private:
	void displayArr(int* arr, int size);
	void displayStack(int top, int* countArr) const;
	List<Pair>* getAdjacencyLists() {
		return this->HeadNodes;
	}
	int* getCountArr() {
		return this->count;
	}
};

void Graph::addEdge(int start, int end, int duration) {
	if (start < 0 || end >= n) {
		cout << "the insert node is out of bound" << endl;
		return;
	}
	ListIterator<Pair> iter(HeadNodes[start]);
	for (Pair* first = iter.First(); iter.NotNull(); first = iter.Next()) {
		if (first->vertex == end) {
			cout << "already exists" << endl;
			return;
		}
	}
	Pair pair(end, duration);
	HeadNodes[start].Insert(pair);
	count[end]++;
}

void Graph::printAdjacencyLists() {
	cout << "adjacency list: " << endl;
	cout << "  count" << endl;
	for (int i = 0; i < n; i++) {
		List<Pair> list = HeadNodes[i];
		cout << "[" << i << "] " << count[i] << " ";
		ListIterator<Pair> iter(list);
		if (!iter.NotNull()) {
			cout << "->null" << endl;
		}
		else {
			for (Pair* first = iter.First(); iter.NotNull(); first = iter.Next()) {
				cout << "->(vertex " << first->vertex << ", dur=" << first->dur << ")";
			}
			cout << endl;
		}
	}
}

Graph* Graph::inverseGraph() const {
	Graph* newG = new Graph(n);
	for (int i = 0; i < n; i++) {
		List<Pair> list = HeadNodes[i];
		ListIterator<Pair> iter(list);
		if (iter.NotNull()) {
			for (Pair* first = iter.First(); iter.NotNull(); first = iter.Next())
				newG->addEdge(first->vertex, i, first->dur);
		}
	}
	return newG;
}

void Graph::displayArr(int* arr, int size) {
	if (!arr) return;
	for (int i = 0; i < size; i++) {
		if (arr[i] < 10) cout << arr[i] << "  ";
		else cout << arr[i] << " ";
	}
}

void Graph::displayStack(int top, int* countArr) const {
	cout << "|  stack=[ ";
	for (int i = 0; i < n; i++) {
		if (countArr[top] == -1)
			cout << top;
		else
			cout << top << ", ";
		top = countArr[top];
		if (top == -1) break;
	}
	cout << " ]" << endl;
}

void Graph::TopologicalOrder() {
	int top = -1;
	for (int i = 0; i < n; i++)
		if (count[i] == 0) {
			count[i] = top;
			top = i;
		}
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			cout << "network has a cycle" << endl;
			return;
		}
		else {
			int j = top;
			top = count[top];
			cout << j << " ";
			ListIterator<Pair> li(HeadNodes[j]);
			if (!li.NotNull()) continue;
			int k = (*li.First()).vertex;
			while (1) {
				count[k]--;
				if (count[k] == 0) {
					count[k] = top;
					top = k;
				}
				if (li.NextNotNull())
					k = (*li.Next()).vertex;
				else break;
			}
		}
	}
}

void Graph::Setup4() {
	addEdge(0, 1, 5);
	addEdge(0, 2, 6);
	addEdge(1, 3, 3);
	addEdge(2, 3, 6);
	addEdge(2, 4, 3);
	addEdge(3, 4, 3);
	addEdge(3, 5, 4);
	addEdge(3, 6, 4);
	addEdge(4, 6, 1);
	addEdge(4, 7, 4);
	addEdge(5, 9, 4);
	addEdge(6, 8, 5);
	addEdge(7, 8, 2);
	addEdge(8, 9, 2);
}

void Graph::EarlyActivity() {
	int* countArr = new int[n];
	for (int i = 0; i < n; i++)
		countArr[i] = count[i];
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (countArr[i] == 0) {
			countArr[i] = top;
			top = i;
		}
	}
	for (int i = 0; i < n; i++)
		ee[i] = 0;
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			cout << "network has a cycle" << endl;
			return;
		}
		else {
			int j = top;
			top = countArr[top];
			ListIterator<Pair> li(HeadNodes[j]);
			if (!li.NotNull()) continue;
			Pair p = *li.First();
			while (1) {
				int k = p.vertex;
				if (ee[k] < ee[j] + p.dur)
					ee[k] = ee[j] + p.dur;
				countArr[k]--;
				if (countArr[k] == 0) {
					countArr[k] = top;
					top = k;
				}
				if (li.NextNotNull())
					p = *li.Next();
				else
					break;
			}
		}
	}
	delete[] countArr;
}

void Graph::EarlyActivity_display() {
	int* countArr = new int[n];
	for (int i = 0; i < n; i++)
		countArr[i] = count[i];
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (countArr[i] == 0) {
			countArr[i] = top;
			top = i;
		}
	}
	cout << "Display ee (early event occurence time) " << endl;
	cout << "ee       ";
	for (int i = 0; i < n; i++)
		cout << "[" << i << "]";
	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "initial   ";
	displayArr(ee, n);
	displayStack(top, countArr);

	for (int i = 0; i < n; i++) {
		if (top == -1) {
			cout << "network has a cycle" << endl;
			return;
		}
		else {
			int j = top;
			top = countArr[top];
			cout << "output " << j << "; ";
			ListIterator<Pair> li(HeadNodes[j]);
			if (!li.NotNull()) continue;
			Pair p = *li.First();
			while (1) {
				int k = p.vertex;
				if (ee[k] < ee[j] + p.dur)
					ee[k] = ee[j] + p.dur;
				countArr[k]--;
				if (countArr[k] == 0) {
					countArr[k] = top;
					top = k;
				}
				if (li.NextNotNull())
					p = *li.Next();
				else
					break;
			}
			displayArr(ee, n);
			displayStack(top, countArr);
		}
	}
	displayArr(ee, n);
	delete[] countArr;
}

void Graph::LateActivity() {
	for (int i = 0; i < n; i++)
		ee[i] = 0;
	EarlyActivity();
	Graph* inversedG = this->inverseGraph();
	List<Pair>* inversedHeadNods = inversedG->getAdjacencyLists();
	int* inversedCount = inversedG->getCountArr();
	int max = -1;
	for (int i = 0; i < n; i++) {
		if (ee[i] > max) max = ee[i];
	}
	for (int i = 0; i < n; i++)
		le[i] = max;
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (inversedCount[i] == 0) {
			inversedCount[i] = top;
			top = i;
		}
	}
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			cout << " network has a cycle" << endl;
			return;
		}
		else {
			int j = top;
			top = inversedCount[top];
			ListIterator<Pair> li(inversedHeadNods[j]);
			if (!li.NotNull()) continue;
			Pair p = *li.First();
			while (1) {
				int k = p.vertex;
				if (le[k] > le[j] - p.dur)
					le[k] = le[j] - p.dur;
				inversedCount[k]--;
				if (inversedCount[k] == 0) {
					inversedCount[k] = top;
					top = k;
				}
				if (li.NextNotNull())
					p = *li.Next();
				else
					break;
			}
		}
	}
	delete inversedG;
}

void Graph::LateActivity_display() {
	for (int i = 0; i < n; i++)
		ee[i] = 0;
	EarlyActivity();
	Graph* inversedG = this->inverseGraph();
	List<Pair>* inversedHeadNods = inversedG->getAdjacencyLists();
	int* inversedCount = inversedG->getCountArr();
	int max = -1;
	for (int i = 0; i < n; i++) {
		if (ee[i] > max) max = ee[i];
	}
	for (int i = 0; i < n; i++)
		le[i] = max;
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (inversedCount[i] == 0) {
			inversedCount[i] = top;
			top = i;
		}
	}
	cout << endl << "Display le (late event occurence time) " << endl;
	cout << "le       ";
	for (int i = 0; i < n; i++)
		cout << "[" << i << "]";
	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "initial   ";
	displayArr(le, n);
	displayStack(top, inversedCount);
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			cout << " network has a cycle" << endl;
			return;
		}
		else {
			int j = top;
			top = inversedCount[top];
			cout << "output " << j << "; ";
			ListIterator<Pair> li(inversedHeadNods[j]);
			if (!li.NotNull()) continue;
			Pair p = *li.First();
			while (1) {
				int k = p.vertex;
				if (le[k] > le[j] - p.dur)
					le[k] = le[j] - p.dur;
				inversedCount[k]--;
				if (inversedCount[k] == 0) {
					inversedCount[k] = top;
					top = k;
				}
				if (li.NextNotNull())
					p = *li.Next();
				else
					break;
			}
			displayArr(le, n);
			displayStack(top, inversedCount);
		}
	}
	displayArr(le, n);
	delete inversedG;
}



void Graph::display_early_late_criticalActivity() {
	EarlyActivity();
	LateActivity();
	cout << endl << endl;
	for (int i = 0; i < n; i++) {
		List<Pair> list = HeadNodes[i];
		ListIterator<Pair> iter(list);
		if (iter.NotNull()) {
			for (Pair* first = iter.First(); iter.NotNull(); first = iter.Next()) {
				int earlyTime = ee[i];
				int lateTime = le[first->vertex] - first->dur;
				int slack = lateTime - earlyTime;
				string critical;
				if (slack == 0) critical = "Yes";
				else critical = "No";
				cout << "edge(" << i << "->"
					<< first->vertex << "), early time="
					<< earlyTime << ", late time="
					<< lateTime
					<< ", slack=" << slack
					<< ", critical=" << critical << endl;
			}
		}
	}
}

void Graph::StartActivity_display() {
	LateActivity();
	for (int i = 0; i < n; i++) {
		List<Pair> list = HeadNodes[i];
		ListIterator<Pair> iter(list);
		if (iter.NotNull()) {
			for (Pair* first = iter.First(); iter.NotNull(); first = iter.Next())
				cout << "<" << i << ", " << first->vertex << "> : e(i) = " << ee[i] << " l(i) = " << le[first->vertex] - first->dur << endl;
		}
	}
}

int main(void)
{
	Graph* g = nullptr;
	int select = 0, n, start = -1, end = -1, weight = -1;
	Graph* inversedG = nullptr;;
	cout << "1: custom setup, 2: default setup ";
	cin >> select;
	if (select == 1) {
		cout << "Input the total node number: ";
		cin >> n;
		g = new Graph(n);
	}
	else if (select == 2) {
		g = new Graph(10);
		g->Setup4();

	}

	while (select != '0')
	{
		cout << "\nSelect command 1: Add edge, 2: AdjacencyLists, 3: Inversed AdjacencyList" <<
			"4: Early Activity, 5: Late Activity, 6. Start Activity, 7:Critical activity 8. TopologicalOrder, 9. Quit => ";
		cin >> select;
		switch (select) {
		case 1:
			cout << "Add an edge: " << endl;
			cout << "--------Input start node: ";
			cin >> start;
			cout << "--------Input destination node: ";
			cin >> end;
			cout << "--------Input weight: ";
			cin >> weight;

			g->addEdge(start, end, weight);
			break;
		case 2:
			//display
			g->printAdjacencyLists();
			break;
		case 3:
			inversedG = g->inverseGraph();
			inversedG->printAdjacencyLists();
			delete inversedG;
			break;
		case 4:
			g->EarlyActivity_display();
			break;
		case 5:
			g->LateActivity_display();
			break;
		case 6:
			g->StartActivity_display();
			break;
		case 7:
			g->display_early_late_criticalActivity();
			break;
		case 8:
			g->TopologicalOrder();
			break;
		case 9:
			exit(0);
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}
	delete g;
	return 0;
}
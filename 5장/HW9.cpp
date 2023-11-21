/*
* 랭크 정수 이진트리 
4. split -> 트리를 분리해서 depth를 줄이는 알고리즘 
Height(Tl) - Height(Tr) : 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이 
LL타입 : leftnode가 2개 연결  
*/
#include <iostream>
#define MaxCapacity 20
using namespace std;

class TreeNode {
	friend class Tree;
private:
	TreeNode* LeftChild;
	int data;
	//leftSize = 트리 왼쪽의 노드 수 + 1, height = Height(Tl) - Height(Tr) 
	int leftSize, height;
	TreeNode* RightChild; 

public:
	TreeNode() {
		LeftChild = RightChild = NULL; leftSize = 0;
	}
	bool equals(TreeNode& x) {
		if (this->data == x.data)
			return true;
		else
			return false;
	}
	int getData() {
		return data;
	}
	friend ostream& operator<<(ostream&, TreeNode&);
};
ostream& operator<<(ostream& os, TreeNode& tn) {
	os << "[data: " << tn.data << ", leftSize: " << tn.leftSize << "]" << endl;
	return os;
}
class Tree {
public:
	Tree() {
		root = NULL;
	}
	Tree::Tree(const Tree& s)//copy constructor
	{
		root = copy(s.root);
	}
	TreeNode* inorderSucc(TreeNode* current);
	bool isLeafNode(TreeNode* current);
	void inorder() {
		inorder(root);
	}
	void preorder() {
		preorder(root);
	}
	void postorder() {
		postorder(root);
	}
	bool insert(int x);
	bool remove(int num);
	void rank() {
		rank(root);
	}
	int search(int rank);//nth 작은 값을 찾는다 
	// Driver
	int operator==(const Tree& t)
	{
		return equal(this->root, t.root);
	}
private:
	TreeNode* root;
	void inorder(TreeNode* CurrentNode);
	void preorder(TreeNode* CurrentNode);
	void postorder(TreeNode* CurrentNode);
	TreeNode* copy(TreeNode* orignode);
	int equal(TreeNode* a, TreeNode* b);
	int rank(TreeNode*);
};
int Tree::rank(TreeNode* current) {
	//leftsize 갱신 -> 재귀0 
}
TreeNode* Tree::inorderSucc(TreeNode* current)
{
	TreeNode* temp = current->RightChild;
	if (current->RightChild != NULL)
		while (temp->LeftChild != NULL) temp = temp->LeftChild;
	return temp;
}
bool Tree::isLeafNode(TreeNode* current) {
	if (current->LeftChild == NULL && current->RightChild == NULL)
		return true;
	else
		return false;
}
void Tree::inorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << *CurrentNode;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}



TreeNode* Tree::copy(TreeNode* orignode)
{
	if (orignode) {
		TreeNode* temp = new TreeNode;
		temp->data = orignode->data;
		temp->LeftChild = copy(orignode->LeftChild);
		temp->RightChild = copy(orignode->RightChild);
		return temp;
	}
	else return 0;
}


// Workhorse
int Tree::equal(TreeNode* a, TreeNode* b)
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{
	if ((!a) && (!b)) return 1;  // both a and b are 0
	if (a && b &&                // both a and b are non-0
		(a->data == b->data)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}


bool Tree::insert(int x) {// binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을
							// 설계하여 구현
	TreeNode* p = root;
	TreeNode* q = NULL;

}

bool Tree::remove(int num) {
	TreeNode* p = root, * q = NULL, * parent = NULL;


}

int Tree::search(int rank) {
	TreeNode* p = root;
	//Node의 leftsize가 찾는 rank보다 크면 왼쪽으로, 아니면 오른쪽으로 

}
enum { Insert, Remove, Inorder, Preorder, Postorder, Search, Copy, Quit };
int main() {
	srand(time(NULL));
	Tree t;
	bool eq = false;
	int select = 0, rankNumber = 0;
	int max = 0, x = 0;
	while (select != 7)
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select 0.Insert, 1. Remove, 2.Inorder, 3.Preorder, 4.Postorder, 5.Search, 6.Copy, 7.Quit =>";
		cin >> select;
		switch (select)
		{
		case Insert:
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				rnd = rand() % 20;
				if (!t.insert(rnd)) cout << "Insert Duplicated data" << endl;
			}

			break;
		case Remove:
			int x;
			cin >> x;
			cout << t.remove(x);//입력된 x에 대한 tree 노드를 찾아 삭제한다.
			cout << endl;
			break;
		case Inorder:
			cout << "inorder print:: ";
			t.inorder();
			cout << endl;
			break;
		case Preorder:
			cout << "preorder print:: ";
			t.preorder();
			cout << endl;
			break;
		case Postorder:
			cout << "postorder print:: ";
			t.postorder();
			cout << endl;
			break;
		case Search:
			t.rank();
			cout << "찾고자 하는 rank 순위 입력: ";
			cin >> x;
			rankNumber = t.search(x); // x번째 순위의 값을 찾는다
			cout << x << " 번째 순위 값은 " << rankNumber << endl;

			break;
		case Copy:
			eq = (t == Tree(t));//copy constructor를 호출
			if (eq) {
				cout << "compare result: true" << endl;
			}
			else
				cout << "compare result: false" << endl;
			break;
		case Quit:
			cout << "Quit" << endl;
			break;

		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;

}


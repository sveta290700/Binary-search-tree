#include <iostream>
using namespace std;

bool flag;

bool Check(int d, int m)
{
	if (!((d >= 1) && (d <= 31)) || !((m >= 1) && (m <= 12)))
	{
		return false;
	}
	if (((m == 4) || (m == 6) || (m == 9) || (m == 11)) && (d > 30))
	{
		return false;
	}
    if ((m == 2) and (d > 29))
		{
			return false;
		}
	return true;
};

class BST {

	struct node {
		int day;
		int month;
		node* left;
		node* right;
	};

	node* root;

	node* makeEmpty(node* t) {
		if (t == NULL)
			return NULL;
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		return NULL;
	}

	node* insert(int d, int m, node* t)
	{
		if (Check(d, m))
		{
			if (!(search(d, m)))
			{
				if (t == NULL)
				{
					t = new node;
					t->day = d;
					t->month = m;
					t->left = t->right = NULL;
					return t;
				}
				else
				{
					if (m < t->month)
						t->left = insert(d, m, t->left);
					if (m > t->month)
						t->right = insert(d, m, t->right);
					if ((d < t->day) && (m == t->month)) t->left = insert(d, m, t->left);
					if ((d > t->day) && (m == t->month)) t->right = insert(d, m, t->right);
				}

			}
			else
			{
				cout << "Повтор элемента!" << endl;
			}
		}
		else cout << "Некорректная дата!" << endl;
		return t;
	}

	node* findMax(node* t) {
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int d, int m, node* t) {
		node* temp;
		if (t == NULL)
			return NULL;
		if (m < t->month)
			t->left = remove(d, m, t->left);
		else if (m > t->month)
			t->right = remove(d, m, t->right);
		else if ((m == t->month) && (!(d == t->day)))
		{
			if (d < t->day) remove(d, m, t->left);
			if (d > t->day) remove(d, m, t->right);
		}
		else if (t->left && t->right)
		{
			temp = findMax(t->left);
			t->day = temp->day;
			t->month = temp->month;
			t->left = remove(t->day, t->month, t->left);
		}
		else
		{
			if ((t->left == NULL) && !(t->right == NULL))
				t = t->right;
			else if ((t->right == NULL) && !(t->left == NULL))
				t = t->left;
			else t = NULL;
		}

		return t;
	}

	void inorder(node* t) {
		if (t == NULL)
			return;
		cout << t->day << "."<<t->month<<" ";
		inorder(t->left);
		inorder(t->right);
	}

	void postorder(node* t) {
		if (t == NULL)
			return;
		postorder(t->left);
		postorder(t->right);
		cout << t->day << "." << t->month << " ";
	}

	void simmleftorder(node* t) {
		if (t == NULL)
			return;
		simmleftorder(t->left);
		cout << t->day << "." << t->month << " ";
		simmleftorder(t->right);
	}

	void simmrightorder(node* t) {
		if (t == NULL)
			return;
		simmrightorder(t->right);
		cout << t->day << "." << t->month << " ";
		simmrightorder(t->left);
	}

	bool find(node* t, int d, int m) {
		if (Check(d, m))
		{
			if (t == NULL)
			{
				flag = false;
			}
			else if (m < t->month) find(t->left, d, m);
			else if (m > t->month) find(t->right, d, m);
			else if (m == t->month)
			{
				if (d == t->day) flag = true;
				if (d < t->day) find(t->left, d, m);
				if (d > t->day) find(t->right, d, m);
			}
		}
		else cout << "Некорректная дата!" << endl;
		return flag;
	}

public:
	BST() {
		root = NULL;
	}

	~BST() {
		root = makeEmpty(root);
	}

	void clear() {
		root = makeEmpty(root);
	}

	void insert(int d, int m) {
		root = insert(d, m, root);
	}

	void remove(int d, int m) {
		root = remove(d, m, root);
	}

	void pretree() {
		inorder(root);
		cout << endl;
	}

	void posttree() {
		postorder(root);
		cout << endl;
	}

	void simmlefttree() {
		simmleftorder(root);
		cout << endl;
	}

	void simmrighttree() {
		simmrightorder(root);
		cout << endl;
	}
	bool search(int d, int m) {
		if (find(root, d, m))
		{
			return true;
		}
		else 
		{ 
			return false; 
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");
	BST t;
	t.insert(30, 10);
	t.insert(31, 10);
	t.insert(28, 10);
	t.insert(29,10);
	t.pretree();
	t.clear();
	t.insert(31, 10);
	t.insert(31, 12);
	t.insert(29, 7);
	t.insert(14, 9);
	t.pretree();
	cout << t.search(16, 5) << endl;
	t.remove(31,10);
	t.pretree();
	t.posttree();
	t.simmlefttree();
	t.simmrighttree();
	t.insert(15, 55);
	cout << t.search(31, 12) << endl;
	t.insert(27, 7);
	t.insert(28, 7);
	t.pretree();
	t.insert(27, 7);
	t.remove(29, 7);
	t.pretree();
	system("pause");
}
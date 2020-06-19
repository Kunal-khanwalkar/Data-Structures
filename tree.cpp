#include <iostream>
using namespace std;

template<typename T>
struct node
{
	T data;
	node* left;
	node* right;
};


template<typename T>
class tree
{
	unsigned int count;
	node<T>* root;
public:
	tree();
	~tree();	
	node<T>* returnroot();
	node<T>* create();	
	void inorder(node<T>* ptr);	
	void preorder(node<T>* ptr);	
	void postorder(node<T>* ptr);	
	node<T>* parent(node<T>* ptr, const T &item);
	int depth(node<T>* ptr);
	bool printAncestors(node<T>* ptr, const T &item);
	int leafNodes(node<T>* ptr);
};

//Constructor, destructor and operators
template<typename T>
tree<T>::tree()
{
	count = 0;
	root = nullptr;
}

template<typename T>
tree<T>::~tree()
{
	delete root;
}

//Member Functions
template<typename T>
node<T>* tree<T>::returnroot()
{
	return root;
}

template<typename T>
node<T>* tree<T>::create()
{
	node<T>* temp = new node<T>;
	T item;
	cout<<"\nEnter data: ";
	cin>>item;
	if(item==-1)
		return nullptr;
	temp->data = item;
	cout<<"\nLeft child: ";
	temp->left = create();
	cout<<"\nRight child: ";
	temp->right = create();
	return temp;
}

template<typename T>
void tree<T>::inorder(node<T>* ptr)
{
	if(ptr)
	{
		inorder(ptr->left);
		cout<<ptr->data<<' ';
		inorder(ptr->right);
	}
}	

template<typename T>
void tree<T>::preorder(node<T>* ptr)
{
	if(ptr)
	{
		cout<<ptr->data<<' ';
		inorder(ptr->left);
		inorder(ptr->right);
	}
}	

template<typename T>
void tree<T>::postorder(node<T>* ptr)
{
	if(ptr)
	{
		inorder(ptr->left);
		inorder(ptr->right);
		cout<<ptr->data<<' ';
	}
}	

template<typename T>
node<T>* tree<T>::parent(node<T>* ptr, const T &item)
{	
	if(ptr==nullptr)
		return nullptr;
	if((ptr->left && ptr->left->data==item) || (ptr->right && ptr->right->data==item))	
	{
		cout<<"\nValue of parent node is: "<<ptr->data;
		return ptr;
	}				
	parent(ptr->left,item);
	parent(ptr->right,item);
	return nullptr;
}

template<typename T>
int tree<T>::depth(node<T>* ptr)
{
	int ldepth,rdepth;
	if(ptr==nullptr)
		return 0;
	ldepth = depth(ptr->left);
	rdepth = depth(ptr->right);
	if(ldepth>rdepth)
		return ldepth+1;
	else
		return rdepth+1;
}

template<typename T>
bool tree<T>::printAncestors(node<T>* ptr, const T &item)
{
	if(ptr==nullptr)
		return false;
	if(ptr->data == item)
		return true;

	if(printAncestors(ptr->left,item) || printAncestors(ptr->right,item))
	{
		cout<<ptr->data<<' ';
		return true;
	}
	return false;
}

template<typename T>
int tree<T>::leafNodes(node<T>* ptr)
{
	if(ptr==nullptr)
		return 0;
	if(ptr->left==nullptr && ptr->right==nullptr)
		return 1;

	return leafNodes(ptr->left) + leafNodes(ptr->right);
}



int main()
{	
	tree<int> t;
	node<int>* root = t.returnroot();
	root = t.create();
	t.inorder(root);
	cout<<'\n';
	t.preorder(root);
	cout<<'\n';
	t.postorder(root);	
	node<int>* randomnode = t.parent(root,4);		
	cout<<"\nDepth: "<<t.depth(root);

	cout<<"\nAncestors: ";
	bool check = t.printAncestors(root,4);

	cout<<"\nNumber of Leaf nodes: "<<t.leafNodes(root);
	return 0;
}
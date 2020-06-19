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
	void parent(node<T>* ptr, const T &item);
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
void tree<T>::parent(node<T>* ptr, const T &item)
{
	if(ptr->left->data==item || ptr->right->data==item)	
	{
		cout<<"\nValue of parent node is: "<<ptr->data;
		return;
	}		
	if(ptr==nullptr)
		return;
	parent(ptr->left,item);
	parent(ptr->right,item);
}



int main()
{	
	tree<int> t;
	node<int>* root = t.returnroot();
	root = t.create();
	t.inorder(root);
	t.parent(root,4);
	return 0;
}
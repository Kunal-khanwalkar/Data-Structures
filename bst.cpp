#include<iostream>
#include<queue>
#include<stack>
using namespace std;


template<typename T>
struct node
{
	T data;
	node* left;
	node* right;
};


template<typename T>
class bst
{
	node<T>* root;
public:
	bst();
	~bst();
	node<T>* returnroot();
	node<T>* create();

	void inorder(node<T>* ptr);	
	void preorder(node<T>* ptr);	
	void postorder(node<T>* ptr);	

	node<T>* search(node<T>* ptr, const T &item);
	node<T>* insert(node<T>* ptr, const T &item);
	node<T>* minNode(node<T>* ptr);
	node<T>* maxNode(node<T>* ptr);
	node<T>* deleteNode(node<T>* ptr, const T &item);
	int height(node<T>* ptr);
	int nodeCount(node<T>* ptr);
	bool isBst(node<T>* ptr, T prev);
	node<T>* nextSuccessor(node<T>* ptr, node<T>* n);
	node<T>* nextSuccessor(node<T>* ptr, const T &item);
};

//Constructors, Destructors and Operators
template<typename T>
bst<T>::bst()
{	
	root = nullptr;
}

template<typename T>
bst<T>::~bst()
{
	delete root;
}


//bst creation
template<typename T>
node<T>* bst<T>::returnroot()
{
	return root;
}

template<typename T>
node<T>* bst<T>::create()
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


//Traversals
template<typename T>
void bst<T>::inorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;
	
	inorder(ptr->left);
	cout<<ptr->data<<' ';
	inorder(ptr->right);
}	

template<typename T>
void bst<T>::preorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;

	cout<<ptr->data<<' ';
	preorder(ptr->left);
	preorder(ptr->right);
}	

template<typename T>
void bst<T>::postorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;

	postorder(ptr->left);
	postorder(ptr->right);
	cout<<ptr->data<<' ';	
}	



//Member Functions
template<typename T>
node<T>* bst<T>::search(node<T>* ptr, const T &item)
{
	if(ptr==nullptr || ptr->data == item)
		return ptr;

	if(ptr->data < item)
		return search(ptr->right, item);

	return search(ptr->left, item);
}


template<typename T>
node<T>* bst<T>::insert(node<T>* ptr, const T &item)
{
	if(ptr==nullptr)
	{
		node<T>* temp = new node<T>;
		temp->data = item;
		temp->left = nullptr;
		temp->right = nullptr;
		ptr = temp;
		return ptr;
	}

	if(ptr->data > item)
		ptr->left = insert(ptr->left,item);
	else
		ptr->right = insert(ptr->right,item);

	return ptr;
}


template<typename T>
node<T>* bst<T>::minNode(node<T>* ptr)
{
	node<T>* temp = ptr;
	while(temp!=nullptr && temp->left!=nullptr)
		temp = temp->left;
	return temp;
}

template<typename T>
node<T>* bst<T>::maxNode(node<T>* ptr)
{
	node<T>* temp = ptr;
	while(temp!=nullptr && temp->right!=nullptr)
		temp = temp->right;
	return temp;
}



template<typename T>
node<T>* bst<T>::deleteNode(node<T>* ptr, const T &item)
{
	if(ptr==nullptr)
		return ptr;

	if(item < ptr->data)
		ptr->left = deleteNode(ptr->left,item);
	else if(item > ptr->data)
		ptr->right = deleteNode(ptr->right,item);

	else
	{
		if(ptr->left == nullptr)
		{
			node<T>* temp = ptr->right;
			free(ptr);
			return temp;
		}
		else if(ptr->right == nullptr)
		{
			node<T>* temp = ptr->left;
			free(ptr);
			return temp;
		}

		node<T>* temp = minNode(ptr->right);
		ptr->data = temp->data;
		ptr->right = deleteNode(ptr->right,temp->data);
	}
	return ptr;
}


template<typename T>
int bst<T>::height(node<T>* ptr)
{
	if(ptr==nullptr)
		return 0;

	queue<node<T>*> q;
	q.push(ptr);
	int height = 0;

	while(true)
	{
		int cnt = q.size();
		if(cnt==0)
			break;
		height++;

		while(cnt>0)
		{
			node<T>* curr = q.front();
			q.pop();
			if(curr->left != nullptr)
				q.push(curr->left);
			if(curr->right != nullptr)
				q.push(curr->right);
			cnt--;
		}
	}

	return height;
}


template<typename T>
int bst<T>::nodeCount(node<T>* ptr)
{	
	if(ptr==nullptr)
		return 0;

	int cnt = 0;	
	cnt += nodeCount(ptr->left) + nodeCount(ptr->right) + 1;	

	return cnt;
}



template<typename T>
bool bst<T>::isBst(node<T>* ptr, T prev)
{
	if(ptr)
	{
		if(!isBst(ptr->left,prev))
			return false;
		if(ptr->data <= prev)
			return false;
		prev = ptr->data;

		return isBst(ptr->right,prev);
	}
	return true;
}


template<typename T>
node<T>* bst<T>::nextSuccessor(node<T>* ptr, node<T>* n)
{
	if(n->right)
		return minNode(n->right);

	node<T>* succ = nullptr;

	while(ptr)
	{
		if(n->data < ptr->data)
		{
			succ = ptr;
			ptr = ptr->left;
		}		
		else if(n->data > ptr->data)
			ptr = ptr->right;
		else
			break;
	}

	return succ;
}


template<typename T>
node<T>* bst<T>::nextSuccessor(node<T>* ptr, const T &item)
{	
	stack<node<T>*> s;
	node<T>* curr = ptr;
	bool flag = false;

	while(curr != nullptr || !s.empty())
	{
		while(curr != nullptr)
		{
			s.push(curr);
			curr = curr->left;
		}		

		curr = s.top();
		s.pop();

		if(flag == true)
			return curr;
		
		if(curr->data == item)
			flag = true;

		curr = curr->right;
	}

	return nullptr;
}



int main()
{
	bst<int> t;
	node<int>* root = t.returnroot();
	//root = t.create();

	root = t.insert(root,8);	
	t.insert(root,3);	
	t.insert(root,1);
	t.insert(root,6);
	t.insert(root,4);
	t.insert(root,7);
	t.insert(root,10);
	t.insert(root,14);
	t.insert(root,13);

	t.inorder(root);

	node<int>* ptr = t.search(root,15);
	if(ptr!=nullptr)
		cout<<"\nFound node: "<<ptr->data;
	else
		cout<<"\nNode doesn't exist";


	ptr = t.minNode(root);
	cout<<"\nMin value: "<<ptr->data<<'\n';

	ptr = t.maxNode(root);
	cout<<"\nMax value: "<<ptr->data<<'\n';

	cout<<"\nHeight of tree: "<<t.height(root);


	root = t.deleteNode(root,10);
	cout<<"\nInorder after deletion: ";
	t.inorder(root);	

	cout<<"\nNode Count: "<<t.nodeCount(root);

	if(t.isBst(root,0))
		cout<<"\nTree is BST";
	else
		cout<<"\nTree is not BST";

	ptr = root->right->left;
	cout<<"\nCurrent node: "<<ptr->data;
	ptr = t.nextSuccessor(root,ptr);
	cout<<"\nNext successor: "<<ptr->data;

	ptr = t.nextSuccessor(root,3);
	if(ptr)
		cout<<"\nNext successor: "<<ptr->data;
	else
		cout<<"\nNode not found";

	return 0;
}
#include <iostream>
#include<stack>
#include<queue>
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
	void iter_inorder(node<T>* ptr);
	void iter_preorder(node<T>* ptr);
	void iter_postorder(node<T>* ptr);
	void levelorder(node<T>* ptr);

	node<T>* parent(node<T>* ptr, const T &item);
	int depth(node<T>* ptr);
	int iter_depth(node<T>* ptr);
	bool printAncestors(node<T>* ptr, const T &item);
	int leafNodes(node<T>* ptr);
	void deleteNode(node<T>* ptr, const T &item);
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


//Tree Creation
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



//Traversals
template<typename T>
void tree<T>::inorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;
	
	inorder(ptr->left);
	cout<<ptr->data<<' ';
	inorder(ptr->right);
}	

template<typename T>
void tree<T>::preorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;

	cout<<ptr->data<<' ';
	preorder(ptr->left);
	preorder(ptr->right);
}	

template<typename T>
void tree<T>::postorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;

	postorder(ptr->left);
	postorder(ptr->right);
	cout<<ptr->data<<' ';	
}	


template<typename T>
void tree<T>::iter_inorder(node<T>* ptr)
{
	stack<node<T>*> s;
	node<T>* curr = ptr;

	while(curr != nullptr || !s.empty())
	{
		while(curr != nullptr)
		{
			s.push(curr);
			curr = curr->left;
		}

		curr = s.top();
		s.pop();

		cout<<curr->data<<' ';

		curr = curr->right;
	}
}

template<typename T>
void tree<T>::iter_preorder(node<T>* ptr)
{
	stack<node<T>*> s;
	node<T>* curr = ptr;

	while(curr != nullptr || !s.empty())
	{
		while(curr != nullptr)
		{
			cout<<curr->data<<' ';
			s.push(curr);
			curr = curr->left;
		}

		curr = s.top();
		s.pop();		

		curr = curr->right;
	}
}

template<typename T>
void tree<T>::iter_postorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;

	stack<node<T>*> s1,s2;
	s1.push(ptr);
	node<T>* curr;

	while(!s1.empty())
	{
		curr = s1.top();
		s1.pop();
		s2.push(curr);

		if(curr->left)
			s1.push(curr->left);
		if(curr->right)
			s1.push(curr->right);
	}

	while(!s2.empty())
	{
		curr = s2.top();
		s2.pop();
		cout<<curr->data<<' ';
	}
}

template<typename T>
void tree<T>::levelorder(node<T>* ptr)
{
	if(ptr==nullptr)
		return;

	queue<node<T>*> q;
	q.push(ptr);
	node<T>* curr;

	while(!q.empty())
	{
		curr = q.front();
		cout<<curr->data<<' ';
		q.pop();

		if(curr->left != nullptr)
			q.push(curr->left);
		if(curr->right != nullptr)
			q.push(curr->right);		
	}	
}


//Auxiliary functions
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
int tree<T>::iter_depth(node<T>* ptr)
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


template<typename T>
void tree<T>::deleteNode(node<T>* ptr, const T &item)
{
	if(ptr==nullptr)
		return;

	queue<node<T>*> q;
	q.push(ptr);
	node<T>* last;

	while(!q.empty())
	{
		last = q.front();		
		q.pop();

		if(last->left != nullptr)
			q.push(last->left);
		if(last->right != nullptr)
			q.push(last->right);		
	}


	queue<node<T>*> empty;
	swap(q,empty);
	q.push(ptr);
	node<T>* curr;

	while(!q.empty())
	{
		curr = q.front();

		if(curr->data == item && curr!=last)
			curr->data = last->data;

		if(curr->left == last)		
			curr->left = nullptr;		
		else if(curr->right == last)
			curr->right = nullptr;		

		q.pop();

		if(curr->left != nullptr)
			q.push(curr->left);
		if(curr->right != nullptr)
			q.push(curr->right);		
	}

}



int main()
{	
	tree<int> t;
	node<int>* root = t.returnroot();
	root = t.create();

	cout<<"\nInorder: ";
	t.inorder(root);
	cout<<"\nPreorder: ";
	t.preorder(root);
	cout<<"\nPostorder: ";
	t.postorder(root);	

	cout<<"\nIterative inorder: ";
	t.iter_inorder(root);
	cout<<"\nIterative preorder: ";
	t.iter_preorder(root);
	cout<<"\nIterative postorder: ";
	t.iter_postorder(root);

	cout<<"\nLevel order: ";
	t.levelorder(root);
	
	node<int>* randomnode = t.parent(root,4);		
	cout<<"\nDepth: "<<t.depth(root);
	cout<<"\nIterative Depth: "<<t.iter_depth(root);

	cout<<"\nAncestors: ";
	bool check = t.printAncestors(root,4);

	cout<<"\nNumber of Leaf nodes: "<<t.leafNodes(root);
	
	t.deleteNode(root,9);
	cout<<"\nInorder after deletion: ";
	t.inorder(root);


	return 0;
}
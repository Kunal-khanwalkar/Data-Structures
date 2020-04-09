#include<iostream>
#include<algorithm>
using namespace std;




template<class T>
class newlist
{
	struct node
	{
		T &data;
		node *next;
	};
	int curr;
	node *head;
	node *tail;

public:

	typedef T *iterator;

	newlist();
	newlist(const T &initial);
	newlist(const newlist<T> &v);
	~newlist();

	unsigned int size() const;
	bool empty() const;
	T &front();
	T &back();
	iterator begin();
	iterator end();

	T &operator[] (unsigned int index);
	newlist<T> &operator=(const newlist<T> &);

	void push_back(const T &data);
	void push_front(const T &data);
	void pop_back();
	void pop_front();
	T &at(unsigned int index);
	T &getHead();
	void setHead(const T &value);

};

template<class T>
newlist<T>::newlist()
{
	curr = 0;
	head = nullptr;	
	tail = nullptr;
}

template<class T>
newlist<T>::~newlist()
{	
	delete head;
	delete tail;
}

template<class T>
newlist<T>::newlist(const T &initial)
{
	head->data = initial;
	head->next = nullptr;
}

template<class T>
T& newlist<T>::getHead()
{
	return head->data;
}

template<class T>
void newlist<T>::setHead(const T &value)
{
	head->data = value;
}


int main()
{

	newlist<int> l;
	//newlist<int> l1(2);
	l.setHead(5);
	cout<<l.getHead();


	return 0;
}
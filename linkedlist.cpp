#include<iostream>
#include<algorithm>
using namespace std;

template<typename T>
struct node
{
	T data;
	node* next;		
};



template<class T>
class list
{
	unsigned int count;
	node<T>* head;
public:
	list();			
	~list();

	unsigned int size() const;
	bool empty() const;
	T& value_at(unsigned int index);
	void push(const T &value);
	void pop();
	void traverse();
	T& front();
	T& back();
	void insert(unsigned int index, const T &value);
	void del(unsigned int index);

	T &operator[](unsigned int index);
	list<T> &operator=(const list<T> &);
};

//Constructor, destructor and operators
template<class T>
list<T>::list()
{
	count = 0;
	head = nullptr;		
}

template<class T>
list<T>::~list()
{
	delete head;
}

template<class T>
T& list<T>::operator[](unsigned int index)
{
	return value_at(index);
}

template<class T>
list<T>& list<T>::operator=(const list<T> &newlist)
{
	count = 0;
	delete head;
	node<T> *t = newlist.head;
	while(t->next!=nullptr)
	{
		push(t->data);
		t = t->next;
	}
	push(t->data);
	return *this;
}


//Member functions
template<class T>
unsigned int list<T>::size() const
{
	return count;
}

template<class T>
bool list<T>::empty() const
{
	return (count==0)?true:false;
}

template<class T>
void list<T>::push(const T &value)
{
	node<T> *temp = new node<T>;
	temp->data = value;
	temp->next = nullptr;
	if(empty()==true)
	{		
		head = temp;
		head->next = nullptr;		
		count++;
		return;
	} 	

	node<T> *t = head;		
	while(t->next!=nullptr)
		t = t->next;	
	t->next = temp;
	count++;
}

template<class T>
void list<T>::traverse()
{
	cout<<'\n';
	node<T> *temp = head;	
	while(temp->next!=nullptr)
	{
		cout<<temp->data<<' ';
		temp = temp->next;
	}
	cout<<temp->data<<'\n';
}

template<class T>
void list<T>::pop()
{
	if(empty()==true)
		return;	

	node<T> *temp = head;
	while(temp->next->next != nullptr)
		temp = temp->next;
	delete temp->next;
	temp->next = nullptr;			
	count--;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
template<class T>
T& list<T>::value_at(unsigned int index)
{
	if(index > size() || index <= 0)
	{
		throw "Out of bounds";
	}

	node<T> *temp = head;
	int i=0;
	while(temp->next!=nullptr)
	{	
		if(i++ == index-1)
			return temp->data;
		temp = temp->next;
	}

}
#pragma GCC diagnostic pop


template<class T>
T& list<T>::front()
{
	return head->data;
}

template<class T>
T& list<T>::back()
{
	node<T> *temp = head;
	while(temp->next!=nullptr)
		temp = temp->next;
	return temp->data;
}

template<class T>
void list<T>::insert(unsigned int index, const T &value)
{
	if(index == size()+1)
	{
		push(value);
		return;
	}

	if(index > size() || index <= 0)
	{
		throw "\nOut of bounds";
	}

	node<T> *temp = new node<T>;
	temp->data = value;

	if(index-1==0)
	{
		temp->next = head;
		head = temp;
		return;
	}	

	node<T> *t = head;
	int i=0;
	while(t->next!=nullptr)	
	{
		if(i++==index-2)
		{
			temp->next = t->next;
			t->next = temp;
			return;
		}		
		t = t->next;
	}
}

template<class T>
void list<T>::del(unsigned int index)
{
	if(index == size()+1)
	{
		pop();
		return;
	}

	if(index > size() || index <= 0)
	{
		throw "\nOut of bounds";
	}
	
	if(index==1)
	{				
		head = head->next;		
		return;
	}

	node<T> *t = head;
	int i=0;	
	while(t->next!=nullptr)
	{
		if(i++==index-2)
		{
			t->next = t->next->next;
			return;			
		}
		t = t->next;
	}
}






int main()
{

	//Testing functions
	node<int> A,B;
	A.data = 3;
	B.data = 5;
	A.next = &B;	
	cout<<A.next->data;
	
	cout<<"\nList stuff now";

	list<int> l;	
	l.push(7);	
	l.push(5);	
	l.pop();
	l.push(3);
	l.push(8);
	l.push(2);
	l.push(6);
	l.pop();
	l.push(5);
	cout<<'\n'<<l.size();	
	l.traverse();	

	try{
		cout<<'\n'<<l.value_at(8);
	}catch(const char* msg){
		cerr<<msg<<endl;
	}

	cout<<'\n'<<l.front();
	cout<<'\n'<<l.back();

	try{
		l.insert(4,9);
	}catch(const char* msg){
		cerr<<msg<<endl;
	}
	l.traverse();

	try{
		l.del(3);
	}catch(const char* msg){
		cerr<<msg<<endl;
	}
	l.traverse();

	try{
		cout<<l[3];
	}catch(const char* msg){
		cerr<<msg<<endl;
	}


	list<int> newl;	
	newl = l;
	newl.traverse();
	return 0;
}
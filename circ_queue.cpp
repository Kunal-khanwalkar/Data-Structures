
#include<iostream>
using namespace std;


template<typename T>
class circular_queue
{
	int front,rear;
	int cap;
	T *buffer;
public:
	circular_queue();
	~circular_queue();
	bool empty() const;
	void reserve(unsigned int size);
	void push(const T &item);
	void pop();
	void traverse();
};

//Constructors, destructor and operators
template<typename T>
circular_queue<T>::circular_queue()
{
	cap = 5;
	front = rear = 0;
	buffer = new T[cap];
}

template<typename T>
circular_queue<T>::~circular_queue()
{
	delete[] buffer;
}


//Member Function
template<typename T>
bool circular_queue<T>::empty() const
{
	if(rear == front)
		return true;
	return false;
}

template<typename T>
void circular_queue<T>::reserve(unsigned int size)
{
	if(buffer==0)
	{
		cap = 1;
		front = rear = 0;
	}
	
	T *newbuff = new T[size];

	int i;
	for(i=front%cap; i!=rear%cap; i = (i+1)%cap)	
		newbuff[i - (front%cap)] = buffer[i];			

	rear = i;
	front = 0;
	cap = size;
	delete[] buffer;
	buffer = newbuff;
}

template<typename T>
void circular_queue<T>::push(const T &item)
{	
	if(rear%cap==0)
		reserve(cap*2);
	buffer[rear%cap] = item;
	rear++;	
}

template<typename T>
void circular_queue<T>::pop()
{
	if(empty())
	{
		cout<<"\nCircular queue is empty\n";
		return;
	}	
	front++;
}

template<typename T>
void circular_queue<T>::traverse()
{	
	int i;
	for(i=front%cap; i!=rear%cap; i=(i+1)%cap)
		cout<<buffer[i]<<' ';	
}


int main()
{
	circular_queue<int> cq;	
	cq.push(5);
	cq.push(7);	
	cq.push(1);	
	cq.push(3);		
	cq.push(9);	
	cq.pop();
	cq.pop();
	cq.push(8);
	cq.traverse();	

	
	cq.push(4);
	cq.push(8);
	cq.pop();
	cq.push(0);
	cq.push(2);
	cout<<'\n';	
	cq.traverse();
	return 0;
}
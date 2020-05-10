#include<iostream>
using namespace std;


template<class T>
class queue
{
	unsigned int cap;
	unsigned int rear;
	unsigned int front;
	T *buffer;
public:
	queue();
	~queue();
	void reserve(unsigned int size);
	void push(const T &item);
	bool empty() const;
	void pop();
	void traverse();
};

//Constructors, destructor and operators
template<class T>
queue<T>::queue()
{
	cap = 0;
	rear = 0;
	front = 0;
	buffer = new T[rear];
}

template<class T>
queue<T>::~queue()
{
	delete[] buffer;
}


//Member functions
template<class T>
bool queue<T>::empty() const
{
	if(rear==front)
		return true;
	return false;
}

template<class T>
void queue<T>::reserve(unsigned int size)
{
	if(buffer==0)
	{
		cap = 0;
		rear = 0;
		front = 0;
	}
	T *newbuff = new T[size];
	for(int i=front;i<rear;i++)
		newbuff[i-front] = buffer[i];
	cap = size;
	delete[] buffer;
	buffer = newbuff;
}


template<class T>
void queue<T>::push(const T &item)
{
	if(rear>cap)
		reserve(rear + 5);
	buffer[rear++] = item;
}

template<class T>
void queue<T>::pop()
{	
	if(empty())
	{
		cout<<"\nEmpty queue\n";
		return;
	}
	front++;
}

template<class T>
void queue<T>::traverse()
{
	for(int i=front;i<rear;i++)
		cout<<buffer[i]<<' ';
}



int main()
{
	queue<int> q;
	cout<<q.empty();	
	q.push(4);
	q.push(7);
	cout<<'\n'<<q.empty();
	cout<<'\n';
	q.pop();
	q.push(6);
	q.push(2);
	q.push(3);
	q.pop();
	q.push(9);
	q.traverse();
	return 0;
}
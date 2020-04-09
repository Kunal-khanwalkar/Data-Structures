#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class newstack
{
	unsigned int top;
	unsigned int curr;
	T *buffer;

public:

	newstack();
	~newstack();

	newstack<T> &operator=(const newstack<T> &);

	T &getTop();
	void push(const T &value);
	void pop();
	void reserve(unsigned int size);
	unsigned int size() const;
	bool empty() const;

};

template<class T>
newstack<T>::newstack()
{
	top = 0;
	curr = 0;
	buffer = new T[curr];
}

template<class T>
newstack<T>::~newstack()
{
	delete[] buffer;
}

template<class T>
newstack<T>& newstack<T>::operator=(const newstack<T> &st)
{
	delete[] buffer;
	curr = st.curr;
	top = st.top;
	reserve(top + 5);
	for(int i=0;i<top;i++)
		buffer[i] = st.buffer[i];
	return *this;
}

template<class T>
void newstack<T>::reserve(unsigned int size)
{
	if(buffer==0)			
	{
		curr = 0;	
		top = 0;
	}
	T *newbuff = new T[size];
	for(int i=0;i<top;i++)
		newbuff[i] = buffer[i];
	curr = size;
	delete[] buffer;
	buffer = newbuff;
}

template<class T>
T& newstack<T>::getTop()
{
	return buffer[top-1];
}

template<class T>
bool newstack<T>::empty() const
{
	if(top==0)
		return true;
	else
		return false;
}

template<class T>
void newstack<T>::pop()
{
	top--;
}

template<class T>
void newstack<T>::push(const T &value)
{
	if(top>curr)
		reserve(curr + 5);
	buffer[top++] = value;
}

template<class T>
unsigned int newstack<T>::size() const
{
	return top;	
}


int main()
{
	newstack<int> s;
	cout<<"\nEmpty? "<<s.empty()<<endl;
	s.push(5);
	s.push(7);
	s.pop();
	s.push(8);
	cout<<s.getTop();
	cout<<"\nSize: "<<s.size();

	newstack<int> st;
	st = s;
	cout<<"\nBig pp: "<<st.getTop();
	return 0;
}
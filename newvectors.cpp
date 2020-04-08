#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

template<class T>
class newvectors
{
	unsigned int curr;
	unsigned int cap;
	T *buffer;

public:

	typedef T *iterator;
	
	newvectors();
	newvectors(unsigned int size);
	newvectors(unsigned int size, const T &initial);		//Value initializer
	newvectors(const newvectors<T> &v);						//Copy Constructor
	~newvectors();
	
	unsigned int capacity() const;
	unsigned int size() const;
	bool empty() const;
	iterator begin();
	iterator end();
	T &front();
	T &back();
	void push_back(const T &value);
	void pop_back();
	T &at(unsigned int index);								//Finding value at index
	int find(const T &item);								//Finding index of item
	void insert(unsigned int index, const T &value);
	void prepend(const T &value);
	void del(unsigned int index);


	void reserve(unsigned int capacity);					//Reallocation of Memory
	void resize(unsigned int size);							//Resizing the vector

	T &operator[](unsigned int index);						//Definition of [] operator for value indexing
	newvectors<T> &operator=(const newvectors<T> &);		//Definition of == operator for value assignment

};

//Constructors and Destructors

template<class T>
newvectors<T>::newvectors()
{
	curr = 0;
	cap = 0;
	buffer = new T[curr];
}

template<class T>
newvectors<T>::newvectors(unsigned int size)
{
	cap = size;
	curr = size;
	buffer = new T[curr];
}

template<class T>
newvectors<T>::newvectors(const newvectors<T> &v)
{
	curr = v.curr;
	cap = v.cap;
	buffer = new T[curr];
	for(int i=0;i<curr;i++)
		buffer[i] = v.buffer[i];
}


template<class T>
newvectors<T>::newvectors(unsigned int size, const T &initial)
{
	curr = size;
	cap = size;
	buffer = new T[curr];
	for(int i=0;i<curr;i++)
		buffer[i] = initial;
	T();
}


template<class T>
newvectors<T>::~newvectors()
{
	delete[] buffer;
}



//Member functions

template<class T>
T& newvectors<T>::operator[](unsigned int index)
{
	return buffer[index];
}

template<class T>
newvectors<T>& newvectors<T>::operator=(const newvectors<T> &v)
{
	delete[] buffer;
	curr = v.curr;
	cap = v.cap;
	buffer = new T[curr];
	for(int i=0;i<curr;i++)
		buffer[i] = v.buffer[i];
	return *this;
}

template<class T>
typename newvectors<T>::iterator newvectors<T>::begin()
{
	return buffer;	
}

template<class T>
typename newvectors<T>::iterator newvectors<T>::end()
{
	return buffer + size();	
}

template<class T>
unsigned int newvectors<T>::capacity() const
{
	return cap;
}

template<class T>
unsigned int newvectors<T>::size() const
{
	return curr;
}

template<class T>
bool newvectors<T>::empty() const
{
	return (curr == 0)?true:false;
}

template<class T>
void newvectors<T>::reserve(unsigned int capacity)
{
	if(buffer == 0)
	{
		curr = 0;
		cap = 0;
	}

	T *newbuff = new T[capacity];
	for(int i=0;i<curr;i++)
		newbuff[i] = buffer[i];
	cap = capacity;
	delete[] buffer;
	buffer = newbuff;

}

template<class T>
void newvectors<T>::resize(unsigned int size)
{
	reserve(size);
	curr = size;
}

template<class T>
void newvectors<T>::push_back(const T &value)
{
	if(curr > cap)
		reserve(cap + 5);
	buffer[curr++] = value;
}

template<class T>
void newvectors<T>::pop_back()
{
	curr--;
}

template<class T>
T& newvectors<T>::front()
{
	return buffer[0];
}

template<class T>
T& newvectors<T>::back()
{
	return buffer[curr - 1];
}

template<class T>
T& newvectors<T>::at(unsigned int index)
{
	if(index-1 > curr)
	{
		cout<<"\nOut of bounds ";
		return buffer[0];
	}
	return buffer[index-1];
}

template<class T>
int newvectors<T>::find(const T &item)
{	
	for(int i=0;i<curr;i++)	
		if(buffer[i] == item)
			return i+1;
	return -1;
}

template<class T>
void newvectors<T>::insert(unsigned int index, const T &value)
{
	if(index-1 > curr)
	{
		cout<<"\nOut of bounds\n";
		return;
	}

	if(index-1 == curr)
	{
		push_back(value);
		return;
	}

	if(curr > cap)
		reserve(cap + 5);

	for(int i=curr;i>(index-1);i--)	
		buffer[i] = buffer[i-1];	
	buffer[index-1] = value;
	curr++;
}

template<class T>
void newvectors<T>::prepend(const T &value)
{
	insert(1,value);
}

template<class T>
void newvectors<T>::del(unsigned int index)
{
	if(empty())	
	{
		cout<<"\nVector is empty\n";
		return;
	}

	if(index-1 > curr)
	{
		cout<<"\nOut of bounds\n";
		return;
	}

	for(int i=index-1;i<curr-1;i++)
		buffer[i] = buffer[i+1];
	curr--;
}





int main()
{



	//Testing Vector Functions
	newvectors<int> vf;	
	newvectors<char> vp(5);
	newvectors<char> vo(vp);
	newvectors<float> v(3,4.2);	
	
	v.push_back(12.1);
	v.push_back(13);
	v.pop_back();
	v.push_back(7.4);
	v.push_back(9);



	cout<<"\nSize: "<<v.size();
	cout<<"\nCapacity: "<<v.capacity();

	if(v.empty())
		cout<<"\nEmpty vector";
	else
		cout<<"\nNon-empty vector";

	cout<<endl;
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<' ';

	newvectors<float> nv;
	nv = v;

	cout<<endl;	
	for(int i=0;i<nv.size();i++)
		cout<<nv[i]<<' ';

	cout<<"\nFront: "<<v.front();
	cout<<"\nBack: "<<v.back();
	cout<<"\n3rd position: "<<v.at(3);
	cout<<"\n7th position: "<<v.at(7);
	cout<<"\nPosition of 7: "<<v.find(7.4);
	cout<<"\nPosition of 8: "<<v.find(8.1);

	cout<<endl;
	for(auto i=v.begin(); i!=v.end(); i++)
		cout<<*i<<' ';

	v.insert(3,4);	
	v.prepend(17);

	cout<<endl;
	for(auto i=v.begin(); i!=v.end(); i++)
		cout<<*i<<' ';
	cout<<"\nSize: "<<v.size();

	v.del(2);
	cout<<endl;
	for(auto i=v.begin(); i!=v.end(); i++)
		cout<<*i<<' ';
	cout<<"\nSize: "<<v.size()<<endl;

	sort(v.begin(),v.end());
	cout<<endl;
	for(auto i=v.begin(); i!=v.end(); i++)
		cout<<*i<<' ';

	return 0;
}
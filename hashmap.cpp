#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<map>
using namespace std;


template<class key, class val>
class hashmap
{
	vector<pair<key,val>> v;
	typename vector<pair<key,val>>::iterator _findele(const key &);
public:
	hashmap();
	hashmap(const hashmap<key,val> &);
	~hashmap();
	val& operator[](unsigned int index);
	hashmap<key,val>& operator=(const hashmap<key,val> &);

	void insert(key,val);
	bool exists(const key &);
	val& get(const key &);
	void remove(const key &);	
	void print();
};

//Constructors, destructors and operators
template<class key, class val>
hashmap<key,val>::hashmap()
{}

template<class key,class val>
hashmap<key,val>::hashmap(const hashmap<key,val> &newhmap)
{
	v = newhmap.v;
}

template<class key, class val>
hashmap<key,val>::~hashmap()
{
	v.erase(v.begin(), v.end());
	v.shrink_to_fit();
}

template<class key, class val>
val& hashmap<key,val>::operator[](unsigned int index)
{
	return get(index);
}

template<class key, class val>
hashmap<key,val>& hashmap<key,val>::operator=(const hashmap<key,val> &newhmap)
{
	v = newhmap.v;
	return *this;
}

//Member functions
template<class key,class val>
typename vector<pair<key,val>>::iterator hashmap<key,val>::_findele(const key &inpkey)
{
	typename vector<pair<key,val>>::iterator itr;
	auto isEqual = [=](const pair<key,val>& element)
	{
		return element.first == inpkey;
	};
	itr = find_if(v.begin(),v.end(),isEqual);		
	return itr;
}

template<class key, class val>
bool hashmap<key,val>::exists(const key &inpkey)
{
	typename vector<pair<key,val>>::iterator itr;
	itr = _findele(inpkey);
	if(itr!=v.end())
		return true;
	return false;
}

template<class key, class val>
void hashmap<key,val>::insert(key inpkey, val inpval)
{
	if(exists(inpkey))
	{
		typename vector<pair<key,val>>::iterator itr;	
		itr = _findele(inpkey);
		itr->second = inpval;
		return;
	}	
	v.push_back({inpkey,inpval});
}

template<class key, class val>
val& hashmap<key,val>::get(const key &inpkey)
{
	typename vector<pair<key,val>>::iterator itr;	
	itr = _findele(inpkey);
	return itr->second;
}

template<class key, class val>
void hashmap<key,val>::remove(const key &inpkey)
{
	if(!exists(inpkey))
	{
		cout<<"\nKey not present\n";
		return;
	}
	typename vector<pair<key,val>>::iterator itr;
	itr = _findele(inpkey);
	itr = v.erase(itr);
}

template<class key, class val>
void hashmap<key,val>::print()
{
	cout<<'\n';
	for(auto i=v.begin();i!=v.end();i++)
		cout<<i->first<<": "<<i->second<<'\n';
}




int main()
{
	
	cout<<"\nWell lets check this boy\n";

	hashmap<int,int> hmap;
	hmap.insert(5,4);
	hmap.insert(6,2);
	hmap.insert(2,4);
	cout<<'\n'<<hmap.get(5);
	cout<<'\n'<<hmap[2];
	cout<<'\n'<<hmap[6];
	cout<<'\n'<<hmap.exists(5);
	cout<<'\n'<<hmap.exists(8);
	hmap.insert(6,9);
	cout<<'\n'<<hmap[6];

	hmap.print();
	hmap.remove(2);
	hmap.print();

	hashmap<int,int> newhmap(hmap);
	newhmap.print();

	hashmap<int,int> newmap;
	newmap = hmap;
	newmap.print();


	return 0;
}
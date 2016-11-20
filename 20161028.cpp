#include <iostream>
#include <string>
//#include <algorithm>   //STL泛型算法 sort  find   find_if   c++ primer 3rd
//#include <functional>  //STL函数对象 greater   less  bind1st bind2nd  not1 not2
//#include <vector>      // vector
//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
CMyString类

运算符重载

Iterator -> 面向对象的指针    ->   容器(OOP  对象)
STL  
standard template library 标准模板库
容器         vector向量容器
迭代器
泛型算法
*/

//反向迭代器  -> 实现的共享版本   -> 还是由特定容器的正向迭代器来实现的
template<typename ContainerIterator>
class _reverse_iterator
{
public:
	typedef typename ContainerIterator::VALUE_TYPE T;
	_reverse_iterator(ContainerIterator it):_it(it){}
	bool operator!=(const _reverse_iterator<ContainerIterator> &src)
	{
		return _it != src._it;
	}
	void operator++()
	{
		--_it;   // _it.operator--();
	}
	T& operator*(){return *_it;}
	const T& operator*()const{return *_it;}
	//T* operator->(){return &*_it;}
	//const T* operator->()const{return &*_it;}  // _it.operator*()   &Test
	T* operator->(){return &**this;}  // &*_it;  -> &operator*();       // &(*this.operator*())
	const T* operator->()const{return &**this;}
private:
	ContainerIterator _it;
};

template<typename T>
class vector
{
public:
	class iterator;//类型的前置声明
	typedef _reverse_iterator<iterator> reverse_iterator;

	// vector<int> vec1;
	vector():_pvec(NULL), _size(0), _index(0){}
	// vector<int> vec2(10);
	vector(int initCapacity, T defaultVal = T())
		:_size(initCapacity),_index(0)
	{
		_pvec = new T[_size];
		for(int i=0; i<_size; ++i)
		{
			_pvec[_index++] = defaultVal;
		}
	}
	// int array[]={12,5,6,7,8,9};   vector<int> vec3(array, array+4);
	vector(T *first, T *last):_index(0)
	{
		_size = last-first;
		_pvec = new T[_size];
		for(; first != last; ++first)
		{
			_pvec[_index++] = *first;
		}
	}
	~vector()
	{
		delete []_pvec;
		_pvec = NULL;
	}
	void push_back(const T &val)
	{
		if(full())
			resize();
		_pvec[_index++] = val;
	}
	void pop_back()
	{
		if(empty())
			return;
		--_index;
	}
	bool empty()const{return _index == 0;}
	bool full()const{return _index == _size;}
	void resize()
	{
		if(_pvec == NULL)
		{
			_pvec = new T[1];
			_size = 1;
			_index = 0;
		}
		else
		{
			T *ptmp = new T[_size*2];
			memcpy(ptmp, _pvec, sizeof(T)*_size);
			_size*=2;
			delete []_pvec;
			_pvec = ptmp;
		}
	}
	class iterator
	{
	public:
		typedef T VALUE_TYPE;
		iterator(T *ptr):_ptr(ptr){}
		bool operator!=(const iterator &src)
		{
			return _ptr != src._ptr;
		}
		void operator++()
		{
			++_ptr;
		}
		void operator--()
		{
			--_ptr;
		}
		iterator operator-(int index)
		{
			return iterator(_ptr-index);
		}
		int operator-(const iterator &it)
		{
			return _ptr-it._ptr;
		}
		iterator operator+(int index)
		{
			return iterator(_ptr+index);
		}
		bool operator<(const iterator &it)
		{
			return _ptr < it._ptr;
		}
		bool operator==(const iterator &it)
		{
			return _ptr == it._ptr;
		}
		T& operator*(){return *_ptr;}
		const T& operator*()const{return *_ptr;}     
		T* operator->(){return _ptr;}
		const T* operator->()const{return _ptr;}
	private:
		T *_ptr;
	};

	//返回正向迭代器
	iterator begin(){return iterator(_pvec);}
	iterator end(){return iterator(_pvec + _index);}
	//返回反向迭代器
	reverse_iterator rbegin(){return reverse_iterator(iterator(_pvec+_index-1));}
	reverse_iterator rend(){return reverse_iterator(iterator(_pvec-1));}
private:
	T *_pvec;
	int _size;
	int _index;

	vector(const vector<T>&);
	vector<T>& operator=(const vector<T>&);
};

class Test
{
public:
	Test(string name=""):_name(name){}
	void show()
	{
		cout<<"Test::show name:"<<_name<<endl;
	}
private:
	string _name;
};

//容器   迭代器       STL库    容器  迭代器  泛型算法   函数对象和绑定器
//泛型算法= 模板 + 迭代器 + 函数对象     实现  冒泡排序  
template<typename RandomIterator>
void mysort(RandomIterator first, RandomIterator last)
{
	RandomIterator iti = first;
	RandomIterator itj = first;
	int k=0;
	RandomIterator::VALUE_TYPE temp;
	for(; iti<last-1; ++iti, ++k)
	{
		for(itj=first; itj<last-1-k; ++itj)
		{
			if(*itj > *(itj+1))
			{
				temp = *itj;
				*itj = *(itj+1);
				*(itj+1) = temp;
			}
		}
	}
}

template<typename RandomIterator, typename Compare>
void mysort(RandomIterator first, RandomIterator last, 
			Compare comp)
			//bool (*pfunc)(typename RandomIterator::VALUE_TYPE, typename RandomIterator::VALUE_TYPE))
{
	RandomIterator iti = first;
	RandomIterator itj = first;
	int k=0;
	RandomIterator::VALUE_TYPE temp;
	for(; iti<last-1; ++iti, ++k)
	{
		for(itj=first; itj<last-1-k; ++itj)
		{
			//if(*itj > *(itj+1))
			//if((*pfunc)(*itj, *(itj+1)))
			if(comp(*itj, *(itj+1)))
			{
				temp = *itj;
				*itj = *(itj+1);
				*(itj+1) = temp;
			}
		}
	}
}

template<typename RandomIterator>
RandomIterator myfind(RandomIterator first, RandomIterator last,
					  typename RandomIterator::VALUE_TYPE val)
{
	for(; first != last; ++first)
	{
		if(*first == val)
			return first;
	}
	return last;
}

template<typename RandomIterator, typename Compare>
RandomIterator myfind_if(RandomIterator first, RandomIterator last,
					  Compare comp)
{
	for(; first != last; ++first)
	{
		if(comp(*first))
			return first;
	}
	return last;
}

template<typename InputIterator, typename OutputIterator>
void mycopy(InputIterator first, InputIterator last, 
			OutputIterator dest)
{
	for(; first != last; ++first)
	{
		*dest++ = *first;
	}
}
///////////////////////////回调函数///////////////////////////
bool compare_int_greater(int a, int b)
{
	return a>b;
}
bool compare_int_less(int a, int b)
{
	return a<b;
}
////////////////////////////函数对象//////////////////////////
template<typename T>
class CMyGreater
{
public:
	bool operator()(T a, T b)
	{
		return a>b;
	}
};
template<typename T>
class CMyLess
{
public:
	bool operator()(T a, T b)
	{
		return a<b;
	}
};
/////////////////////////////////////////////////////
template<typename Compare, typename T>
class _mybind
{
public:
	_mybind(Compare comp, T val)
		:_comp(comp), _val(val){}
	bool operator()(T val)
	{
		return _comp(val, _val);
	}
private:
	Compare _comp;
	T _val;
};

template<typename Compare, typename T>
_mybind<Compare, T>  mybind(Compare comp, T val)
{
	return _mybind<Compare, T>(comp, val);
}


int main()
{
	vector<int> vec1;         // push_back   insert(iterator, 56);
	vec1.push_back(20);
	vec1.push_back(5);
	vec1.push_back(67);
	vec1.push_back(32);
	vec1.push_back(12);
	vec1.push_back(42);
	vec1.push_back(78);

	vector<int> vec2;
	// 插入型迭代器
	//mycopy(vec1.begin(), vec1.end(), vec2.begin());
	mycopy(vec1.begin(), vec1.end(), myback_inserter(vec2));
	

#if 0
	// vector<int>::const_iterator
	vector<int>::iterator it1 = vec1.begin();
	for(; it1 != vec1.end(); ++it1)
	{
		cout<<*it1<<" ";
		//*it1 = 10;
	}
	cout<<endl;

	vector<int>::reverse_iterator rit1 = vec1.rbegin();   // rend()
	for(; rit1 != vec1.rend(); ++rit1)
	{
		cout<<*rit1<<" ";
	}
	cout<<endl;

	//泛型算法
	mysort(vec1.begin(), vec1.end());
	for(it1 = vec1.begin(); it1 != vec1.end(); ++it1)
	{
		cout<<*it1<<" ";
	}
	cout<<endl;

	//mysort(vec1.begin(), vec1.end(), &compare_int_greater);  //可以从大到小排序
	mysort(vec1.begin(), vec1.end(), CMyGreater<int>()); 
	for(it1 = vec1.begin(); it1 != vec1.end(); ++it1)
	{
		cout<<*it1<<" ";
	}
	cout<<endl;

	// myfind    vec1.begin(), vec1.end(),  56
	vector<int>::iterator it10 = myfind(vec1.begin(), 
		vec1.end(), 67);
	if(it10 == vec1.end())
	{
		cout<<"未找到67!"<<endl;
	}
	else
	{
		cout<<"67找到 index:"<<it10 - vec1.begin()<<endl;
	}

	// myfind_if(vec1.begin(), vec1.end(), )    第一个大于40的元素
	//myfind_if(vec1.begin(), vec1.end(), CMyComp<int>(50));
	//vector<int>::iterator it11 = myfind_if(vec1.begin(), vec1.end(), 
		//mynot1(mybind(CMyLess<int>(), 40)));     !
	// bind1st  bind2nd 绑定器      not1   not2 取反器
	cout<<*it11<<endl;

	cout<<"-----------------------------------"<<endl;

	Test t1("test1");
	Test t2("test2");
	Test t3("test3");
	vector<Test> vec2;
	vec2.push_back(t1);
	vec2.push_back(t2);
	vec2.push_back(t3);

	vector<Test>::iterator it2 = vec2.begin();
	for(; it2 != vec2.end(); ++it2)
	{   // operator[]   operator*
		// it2.operator->(show())
		// (it2.operator->())->show();
		it2->show();
	}

	vector<Test>::reverse_iterator rit2 = vec2.rbegin();
	for(; rit2 != vec2.rend(); ++rit2)
	{
		rit2->show(); // Test   Test*
	}
#endif
	return 0;
}
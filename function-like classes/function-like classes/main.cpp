#include <iostream>

/*
	Function-Like Classes
	���º���
*/

template<typename T>
struct identity
{
	const T& operator()(const T& x) const
	{
		return x;
	}
};

template<class Pair>
struct select1st
{
	const typename Pair::first_type& 
		operator()(const Pair& x) const
	{
		return x.first;
	}
};

template<typename Pair>
struct select2st
{
	const typename Pair::second_type&
		operator()(const Pair& x) const
	{
		return x.second;
	}
};

template<typename T1, typename T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair() : first(T1()), second(T2())
	{

	}

	pair(const T1& a, const T2& b) : first(a), second(b)
	{
		std::cout << "constructor ..." << std::endl;
	}

	//-------- ģ�幹�캯�� ---------//
	template<typename U1, typename U2>
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second)
	{

	}

};

int main()
{
	pair<int, double> a( 10, 30.9f );

	
	int first = select1st<pair<int, double>>()(a); // ��һ��С�������������������ʱ����
	int second = select2st <pair<int, double>>()(a); 

	std::cout << "first = " << first << std::endl;
	std::cout << "second = " << second << std::endl;

	return 0;
}

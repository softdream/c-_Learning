#include <iostream>

/* 
	ģ���ػ���ƫ�ػ�
*/

//----------------- ���� -----------------//
template<class Key>
struct hash{

};

//-------------- ���char���͵��ػ� -----------------//
template<>
struct hash<char>
{
	size_t operator()(char x) const
	{
		return x;
	}
};

//-------------- ���int���͵��ػ� -----------------//
template<>
struct hash<int>
{
	size_t operator()(char x) const
	{
		return x;
	}
};

//------------------ ƫ�ػ�֮�����ϵ�ƫ -------------------//
template<typename T1, typename T2, typename T3> //����
class Test
{

};

template<typename T2, typename T3>
class Test<int, T2, T3>//ƫ�ػ�
{

};

template<typename T3>
class Test<int, char, T3> //ƫ�ػ�
{

};

template<>
class Test<int, int, int>//�ػ�
{

};

//------------------ ƫ�ػ�֮��Χ�ϵ�ƫ -------------------//
template<typename T1, typename T2, typename T3>
class Test<T1*, T2*, T3*> // ���ָ�����͵�ƫ�ػ�
{

};


int main()
{
	return 0;
}

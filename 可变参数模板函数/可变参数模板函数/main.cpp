#include <iostream>
using namespace std;

//�ݹ���ֹ����   �ػ���ģ�庯��
void print() {
	cout << "empty" << endl;
}
//չ������
template <class T, class... Args>
void print(T head, Args... rest) {
//	cout << "parameter " << head << endl;
	std::cout << "length = " << head.length() << std::endl;
	print(rest...);
}

template<typename T>
void test( T a )
{
	std::cout << "length of a = " << a.length() << std::endl;
}

int main()
{
	print<std::string, std::string>( "string", "dudaofeng" );
	//test<std::string>("string");
	return 0;
}

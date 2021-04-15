#include <iostream>
#include <list>

/*
	template template parameter
	��ģ���ģ�����
*/

template<typename T, 
		template<typename T>
		class Container  //�����һ��ģ���е�ģ�����������һ��ģ������
		>
class XCLs
{
private:
	Container<T> c;

public:

};

template<typename T>
using Lst = std::list<T, std::allocator<T>>;

int main()
{
	XCLs<std::string, Lst> mylst;

	return 0;
}
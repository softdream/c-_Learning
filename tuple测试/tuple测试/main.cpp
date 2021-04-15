#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <typeinfo>
#include <vector>

template<typename T>
struct function_traits;

// RΪ��������
// ...Args Ϊ����������ͣ���������
template<typename R, typename ...Args>
struct function_traits<std::function<R(Args...)>>
{
	static const size_t nargs = sizeof...(Args);
	// ��������
	typedef R result_type;

	// �����������,iΪ��0��ʼ�Ĳ�����������
	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
	};
};

void testCB(int a)
{
	std::cout << "a = " << a << std::endl;
}

int main()
{
	function_traits<decltype(testCB)>::args<0>::type;
	return 0;
}
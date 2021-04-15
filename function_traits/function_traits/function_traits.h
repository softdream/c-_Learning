/*
* function_traits������ȡ���к����������͵���Ϣ��
*      (�������͡��������͡����������Ͳ����ľ�������)��
*
* �����������Ͱ���
*  ��ͨ����
*  ����ָ��
*  function/lambda
*  ��Ա����
*  ��������
*
* ʵ��function_traits�Ĺؼ�����
*  Ҫͨ��ģ���ػ��Ϳɱ����ģ������ȡ�������ͺͷ������͡�
*  �ȶ���һ��������function_traits��ģ���ࣺ
*     template<typename T>
*     struct function_traits;
*  ��ͨ���ػ������������ͺͿɱ����ģ����Ϊģ��������Ϳ��Ի�ȡ�������͡���������ֵ�Ͳ����ĸ����ˡ�
*
* ��:
*  int func(int a, string b);
* ## ��ȡ��������
*      function_traits<decltype(func)>::function_type; // int __cdecl(int, string)
* # ��ȡ��������ֵ
*      function_traits<decltype(func)>::return_type;   // int
* # ��ȡ�����Ĳ�������
*      function_traits<decltype(func)>::arity;         // 2
* # ��ȡ������һ���������
*      function_traits<decltype(func)>::args<0>::type; // int
* # ��ȡ�����ڶ����������
*      function_traits<decltype(func)>::args<1>::type; // string
*/

#ifndef __FUNCTION_TRAITS_H__
#define __FUNCTION_TRAITS_H__

#include <functional>

// ԭ��
template<typename T>
struct function_traits;

// ��ͨ����
template<typename ReturnType, typename... Args>
struct function_traits<ReturnType(Args...)>
{
	enum { arity = sizeof...(Args) };
	using return_type = ReturnType;
	using function_type = ReturnType(Args...);
	using stl_function_type = std::function<function_type>;
	using pointer = ReturnType(*)(Args...);

	template<size_t I>
	struct args
	{
		static_assert(I < arity, "index is out of range, index must less than sizeof Args");
		using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
	};

	using tuple_type = std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...>;
	using bare_tuple_type = std::tuple<std::remove_const_t<std::remove_reference_t<Args>>...>;
};

// ����ָ��
template<typename ReturnType, typename... Args>
struct function_traits<ReturnType(*)(Args...)> : function_traits<ReturnType(Args...)> {};

// std::function
template<typename ReturnType, typename... Args>
struct function_traits<std::function<ReturnType(Args...)>> : function_traits<ReturnType(Args...)> {};

// ��Ա����
#define FUNCTION_TRAITS(...)\
template <typename ReturnType, typename ClassType, typename... Args>\
struct function_traits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : function_traits<ReturnType(Args...)>{};\

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

// ��������
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(const Function& lambda)
{
	return static_cast<typename function_traits<Function>::stl_function_type>(lambda);
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(Function&& lambda)
{
	return static_cast<typename function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function& lambda)
{
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}

#endif

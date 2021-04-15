/**
* @file    function_delegate.h
* @brief   ����ί��
* @author  DC
* @date    2019-04-16
* @note
* @example
*          class my_class
*          {
*          public:
*              void test(int a, double b)
*              {
*              }
*          };
*
*          my_class my;
*          function_delegate<> delegate(&my, &my_class::test);
*          delegate(1, 2.0);
*
*/

#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <functional>

namespace function_delegate_pri
{
	///< �����Ա����ָ��
	class member_ptr
	{
	public:
		///< ��ϣ����
		typedef std::_Bitwise_hash<member_ptr> hash;
		///< ���캯��
		template<class T, class Func>
		member_ptr(T* obj, Func func)
		{
			obj_ = obj;
			*(Func*)&func_ = func;
		}
		///< С�ں���
		bool operator <(const member_ptr& ptr) const
		{
			if (func_[0] != ptr.func_[0]) {
				return func_[0] < ptr.func_[0];
			}
			if (func_[1] != ptr.func_[1]) {
				return func_[1] < ptr.func_[1];
			}
			return obj_ < ptr.obj_;
		}
		///< ��Ⱥ���
		bool operator ==(const member_ptr& ptr) const
		{
			if (func_[0] != ptr.func_[0]) {
				return false;
			}
			if (func_[1] != ptr.func_[1]) {
				return false;
			}
			return obj_ == ptr.obj_;
		}
		///< ���ú���
		template
			<
			typename T,
			typename U,
			typename Result,
			typename ... Args
			>
			Result invoke(Args... args)
		{
			typedef Result(U::*Call)(Args...);
			Call call = *(Call*)&func_;
			return (((T*)obj_)->*call)(args...);
		}

		void* obj_{ nullptr };     ///< ����ָ��
								   ///< �����Ա������Ҫʹ������ָ�룬C++��������̳е���
		void* func_[3]{ nullptr }; ///< ���Ա����ָ��
	};

	///< ����ί��
	template<class Strategy = void>
	class delegate_impl
	{
	public:
		///< ���ö���ͳ�Ա����
		template
			<
			typename T,
			typename U,
			typename Result,
			typename ... Args
			>
			delegate_impl(T* ptr, Result(U::*fn)(Args...)) : refcnt_(ptr), ptr_(ptr, fn)
		{
			typedef Result(*Invoke)(member_ptr*, Args...);
			Invoke call = &delegate_impl::invoke<T, U, Result, Args...>;
			invoke_ = call;
		}

		bool operator <(const delegate_impl& func) const
		{
			if (invoke_ != func.invoke_) {
				return invoke_ < func.invoke_;
			}
			return ptr_ < func.ptr_;
		}

		///< ���ó�Ա����
		template
			<
			typename Result = void,
			typename ... Args
			>
			Result operator()(Args... args) const
		{
			typedef Result(*Invoke)(member_ptr*, Args...);
			Invoke call = (Invoke)invoke_;
			return call((member_ptr*)&ptr_, args...);
		}

		Strategy* object() const { return refcnt_; }

	private:
		template
			<
			typename T,
			typename U,
			typename Result,
			typename ... Args
			>
			static Result invoke(member_ptr* ptr, Args... args)
		{
			return ptr->invoke<T, U, Result>(args...);
		}

		Strategy*       refcnt_{ nullptr };   ///< 
		member_ptr    ptr_;                 ///< ��Ա����ָ��
		void*           invoke_{ nullptr };   ///< invoke������ַ
	};

	template<>
	class delegate_impl<void>
	{
	public:
		///< ���ö���ͳ�Ա����
		template
			<
			typename T,
			typename U,
			typename Result,
			typename ... Args
			>
			delegate_impl(T* ptr, Result(U::*fn)(Args...)) : ptr_(ptr, fn)
		{
			typedef Result(*Invoke)(member_ptr*, Args...);
			Invoke call = &delegate_impl::invoke<T, U, Result, Args...>;
			invoke_ = call;
		}

		bool operator <(const delegate_impl& func) const
		{
			if (invoke_ != func.invoke_) {
				return invoke_ < func.invoke_;
			}
			return ptr_ < func.ptr_;
		}

		///< ���ó�Ա����
		template
			<
			typename Result = void,
			typename ... Args
			>
			Result operator()(Args... args) const
		{
			typedef Result(*Invoke)(member_ptr*, Args...);
			Invoke call = (Invoke)invoke_;
			return call((member_ptr*)&ptr_, args...);
		}

	private:
		template
			<
			typename T,
			typename U,
			typename Result,
			typename ... Args
			>
			static Result invoke(member_ptr* ptr, Args... args)
		{
			return ptr->invoke<T, U, Result>(args...);
		}

		member_ptr    ptr_;                 ///< ��Ա����ָ��
		void*         invoke_{ nullptr };   ///< invoke������ַ
	};
}

using function_ptr = function_delegate_pri::member_ptr;
template<class Strategy = void>
using function_delegate = function_delegate_pri::delegate_impl<Strategy>;

#endif ///< !FUNCTION_DELEGATE_H_
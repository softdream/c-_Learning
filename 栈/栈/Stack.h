#ifndef __STACK_H_
#define __STACK_H_

#include <iostream>

#define MAXSIZE 10

template<class T>
class Stack {
public:
	Stack();//Ĭ�Ϲ��캯��
	Stack(int stack_size_);//�Զ��幹�캯��
	Stack(const Stack &obj);//�������캮��
	~Stack();// ��������

	Stack& operator=(const Stack& other)// ������ֵ����
	{
		if (this == &other) return *this;// ����Ը�ֵ
		delete[] stack;// ɾ��ԭ�е��ڴ���Դ
		stack = new T[stack_size];// �����µ��ڴ���Դ
		memcpy(stack, other.stack, stack_size * sizeof(T));// ���ƹ�ȥ
		return *this;// ����������
	}

	void push(T data);
	bool isFull();
	bool isEmpty();
	T pop();
private:
	T *stack;
	int stack_size;
	int top;// ջ��ָ��

	int getMaxsize()
	{
		return stack_size;
	}
};

template< class T >
Stack<T>::Stack() : top(0), stack_size(MAXSIZE)
{
	stack = new T[MAXSIZE];
}

template< class T >
Stack<T>::Stack(int stack_size_) : top(0)
{
	stack_size = stack_size_;
	stack = new T[stack_size];
}

/* �������캯�� */
template< class T >
Stack<T>::Stack(const Stack &obj)
{
	stack = new T[stack_size];
	//std::cout << "sizeof(stack) = " << sizeof(T) << std::endl;
	memcpy(stack, obj.stack, stack_size * sizeof(T));
}

/* ������ֵ���� */
/*template< class T >
Stack<T>::Stack& Stack<T>::operator=(const Stack& other)
{
if (this == &other) return *this;// ����Ը�ֵ
delete[] stack;// ɾ��ԭ�е��ڴ���Դ
stack = new T[ stack_size ];// �����µ��ڴ���Դ
memcpy(stack, other.stack, stack_size * sizeof(T));// ���ƹ�ȥ
return *this;// ����������
}*/

template< class T >
bool Stack<T>::isFull()
{
	if (top == (getMaxsize() + 1)) {
		std::cout << "ջ���� ..." << std::endl;
		return true;
	}
	return false;
}

template< class T >
bool Stack<T>::isEmpty()
{
	if (top == -1) {
		std::cout << "ջ���� ..." << std::endl;
		return true;
	}
	return false;
}

template< class T >
void Stack<T>::push(T data)
{
	// �ж�ջ�Ƿ�Ϊ��
	if (isFull() == true) {
		std::cout << "ջ���ˣ������������ ..." << std::endl;
		exit(-1);
	}
	stack[++top] = data;// ������ִ�����
}

template< class T >
T Stack<T>::pop()
{
	// �ж�ջ�Ƿ�Ϊ��
	if (isEmpty() == true) {
		std::cout << "ջ�ǿյģ����ܳ�ջ ..." << std::endl;
		exit(-1);
	}
	T temp = stack[top--];
	return temp;
}


template< class T >
Stack<T>::~Stack()
{
	delete[] stack;
}

#endif

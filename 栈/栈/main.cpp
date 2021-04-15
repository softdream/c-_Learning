//#include "Stack.h"
#include <iostream>
#include <stack>

int main()
{
	/*Stack<char> s;
	s.push( 10 );
	s.push( 20 );
	s.push( 30 );
	std::cout << "��ջ��" << (int)s.pop() << std::endl;
	std::cout << "��ջ��" << (int)s.pop() << std::endl;
	std::cout << "��ջ��" << (int)s.pop() << std::endl;
	
	Stack<char> b;

	b = s;*/
	std::stack<int> s;
	s.push( 10 );
	s.push( 20 );
	s.push( 30 );
	std::cout << "��ջ��" << s.top() << std::endl;
	s.pop();
	std::cout << "��ջ��" << s.top() << std::endl;
	s.pop();
	std::cout << "��ջ��" << s.top() << std::endl;
	s.pop();

	return 0;
}
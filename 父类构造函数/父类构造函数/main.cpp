#include <iostream>

class Father {
public:
	Father() : a(0), b(0), c(0)
	{
		std::cout << "�����ʼ��1" << std::endl;
	}
	Father( int a_, int b_, int c_ )
	{
		std::cout << "�����ʼ��2" << std::endl;
	}

private:
	int a;
	int b;
	int c;
};

class Child : public Father{
public:
	Child():Father( 0, 0, 0 ) {
		std::cout << "�����ʼ��" << std::endl;
	}
};

int main()
{
	Child c;
	return 0;
}


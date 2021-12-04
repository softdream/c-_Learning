#include <iostream>

// �༯�� 
// c++14

class Base // Base �ǻ��ࣨ���ࣩ
{
public:
	Base()
	{
		std::cout << " Base Default Constructor ..." << std::endl;
	}

	Base(const int a_, const int b_) : a(a_), b(b_)
	{
		std::cout << " Base Overloaded Constructor ..." << std::endl;
	}

	~Base()
	{
		std::cout << " Base Default DeConstructor ..." << std::endl;
	}

	void setA(const int a_)
	{
		a = a_;
	}

	void setB(const int b_)
	{
		b = b_;
	}

	const int getA() const // �ڶ���const�����������������ĳ�Ա����a������������Ա���aֻ�пɶ���Ȩ��
	{
		return a;
	}

	void printBase()
	{
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
	}

	virtual void test(int a)
	{
		// �������������һ��
		std::cout << "Base test ..." << std::endl;
	}

protected:

	int a = 10;
	int b = 10;
};

//  Derived �������ࣨ�̳��ࣩ������
class Derived : public Base // һ�㵥�̳оͿ�����
{
public:
	// �����Ĭ�Ϲ��캯��д��
	Derived()
	{
		std::cout << " Derived  Default Constructor ..." << std::endl;
	}

	// ��������ع��캯��
	Derived(const int a_, const int b_, const int c_) : Base(a_, b_), c(c_)
	{
		std::cout << " Derived Overloaded Constructor ..." << std::endl;
	}

	~Derived()
	{
		std::cout << " Derived Default DeConstructor ..." << std::endl;
	}

	void printDerived()
	{
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "c = " << c << std::endl;
	}

	void test(int a)
	{
		std::cout << "Derived test ..." << std::endl;
	}

private:
	int c = 20;
};

// �麯��, c++�Ķ�̬�ͻ������麯��ʵ�ֵģ���̬����
// ģ�� ��̬��̬ ���ͱ��

int main()
{
	Derived d( 100, 200, 400 );

	d.printDerived();

	d.Base::test(10);

	return 0;
}
#include <iostream>

class Base {
public:
	Base():val1(0), val2(0)
	{
		a = new char[10];
		memset(a, 0, 10);
	}

	Base( int val1_, int val2_ ):val1(val1_), val2(val2_)
	{
		std::cout << "���๹�캯��" << std::endl;
		a = new char[10];

		for (int i = 0; i < 10; i++) {
			a[i] = i;
		}
	}

	Base(const Base &rhs):val1(rhs.val1), val2(rhs.val2)
	{
		std::cout << "���࿽�����캯��" << std::endl;
		std::cout << "����һ�����" << std::endl;
		a = new char[10];
		memcpy( a, rhs.a, 10 ); // ���
	}
	
	Base& operator=(const Base &rhs)
	{
		std::cout << "���ำֵ����" << std::endl;
		if (&rhs == this) return *this;

		val1 = rhs.val1;
		val2 = rhs.val2;

		a = new char[10];
		memcpy(a, rhs.a, 10); // ���

		return *this;
	}

	~Base() 
	{
		std::cout << "������������" << std::endl;
		delete[] a;
	}

	void print() const
	{
		std::cout << "val1 = " << val1 << std::endl;
		std::cout << "val2 = " << val2 << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << "a[" << i << "] = " << (int)a[i] << std::endl;
		}
	}

protected:
	int val1;
	int val2;
	char *a;
};

class Derivate :public Base {
public:
	Derivate():Base(), val3(0)
	{

	}

	Derivate(int val1_, int val2_, int val3_) :Base(val1_, val2_), val3(val3_)
	{
		std::cout << "���๹�캯��" << std::endl;
	}

	/*Derivate(const Derivate &rhs) :Base(rhs.val1, rhs.val2), val3(rhs.val3)
	{
		std::cout << "���࿽�����캯��" << std::endl;
	}*/

	Derivate(const Derivate &rhs) :Base(rhs), val3(rhs.val3)
	{
		std::cout << "���࿽�����캯��" << std::endl;
	}

	Derivate& operator=(const Derivate &rhs)
	{
		std::cout << "���ำֵ����" << std::endl;
		if (&rhs == this) return *this;

		this->Base::operator=(rhs);// ��ʽ�ĵ��û���ĸ�ֵ����
		val3 = rhs.val3;

		return *this;
	}

	~Derivate()
	{
		std::cout << "������������" << std::endl;
	}

	void print() const
	{
		std::cout << "val1 = " << val1 << std::endl;
		std::cout << "val2 = " << val2 << std::endl;
		std::cout << "val3 = " << val3 << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << "a[" << i << "] = " << (int)a[i] << std::endl;
		}
	}


private:
	int val3;
};

int main()
{
	/*Base base;
	base.print();

	Base base2 = base;
	base2.print();

	Base base3;
	base3 = base;
	base3.print();*/

	Derivate a( 1, 2, 3 );
	a.print();

	std::cout << "-------------------" << std::endl;

	Derivate b;
	b = a;
	b.print();

	return 0;
}
#include <iostream>

class Base
{
public:
	virtual void test()
	{
		std::cout << "Base::test " << std::endl;
		this->inside();
	}

	void inside()
	{
		std::cout << "inside ..." << std::endl;
	}
};

class Derived: public Base
{
public:
	virtual void test()
	{
		std::cout << "Derived::test " << std::endl;
		this->inside();
	}
};

int main()
{
	std::cout << "-------------- 1 ---------------" << std::endl;
	Derived d;
	d.test();

	std::cout << "-------------- 2 ---------------" << std::endl;
	Base b;
	b.test();

	std::cout << "-------------- 3 ---------------" << std::endl;
	Base c;
	c.Base::test(); // �����е��ø����ͬ������

	std::cout << "-------------- 4 ---------------" << std::endl;
	Base *e = dynamic_cast<Base *>( &d ); // ����ָ��ת��Ϊ����ָ��
	e->test();

	std::cout << "-------------- 5 ---------------" << std::endl;
	Base f = static_cast<Base>( d ); // ����ǿ��ת��Ϊ����
	f.test();

	std::cout << "-------------- 6 ---------------" << std::endl;
	Derived *h = dynamic_cast<Derived *>( &b ); // ����ָ��ת��Ϊ���࣬�������ͼ�飬����ȫ
	if (h == nullptr) {
		std::cerr << "null ptr ..." << std::endl;
	}
	else {
		h->test();
	}
	

	std::cout << "-------------- 7 ---------------" << std::endl;
	//Derived g = static_cast<Derived>(b); // ����ת��Ϊ���࣬Error C2440: ��static_cast��: �޷��ӡ�Base��ת��Ϊ��Derived��
	//g.test();

	return 0;
}
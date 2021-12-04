#include <iostream>

class B {
public:
	int b;

	B()
	{
		std::cout << "----- B Constructor -----" << std::endl;
		f();// ���캯������õ���Զ�������f()
		// ��Ϊʵ����D��ʱ�򣬸���B�Ĺ��캯����ִ�У���ʱ��D��û�����ü���f����������д
	}

	virtual void f()
	{
		std::cout << "virtual B::f()" << std::endl;
	}

	void g()
	{
		std::cout << "B::g()" << std::endl;
		//B::f();//���õ��������f()
		f();//���õ���D��f()
	}
};

class D :public B {
public:
	D()
	{
		std::cout << "----- D Constructor -----" << std::endl;
		f();
	}
	virtual void f()
	{
		std::cout << "virtual D::f()" << std::endl;
	}

	void h()
	{
		std::cout << "non virtual D::h()" << std::endl;
	}
};

int main()
{
	//D d;
	//d.g();

	//B *b = new D();
	//b->g();

	B *b = new B();
	D *d = dynamic_cast<D *>(b);
	d->h();

	return 0;
}
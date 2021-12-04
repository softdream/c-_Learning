#include <iostream>

#include <vector>
#include <algorithm>

// c with class
// c with stl

// standard template library
// 1. ����
// 2. ������ Adapter
// 3. �º���
// 4. ������--�㷨�������Ĺ�ͨ����
// 5. �㷨
// 1. vector 2. map 3. list 4. deque 5. stack

// �ؼ���
// 1. ���캯�������������ĸ���--ע�⹹�캯����ʼ���б��д�����Լ����캯��������
// 2. �������캯���Ϳ�����ֵ�����ĸ���--����
// 3. �����ǳ����--��Ҫ��Զ�̬�������Դ
// ���⣺
// 1. public, protected, private���ߵ�����
class Base
{
public:
	Base(): a(10), b(10) // ���캯���� ��������ʼ��, ���캯����ʼ���б�
	{
		std::cout << "constructor ..." << std::endl;	

		init();
	}

	Base( int a_, int b_ ) : a(a_), b(b_) // ���ع��캯��
	{
		std::cout << "constructor2 ..." << std::endl;
		init();
	}

	// �и�Ĭ�ϵĿ������캯��,�����ʱ��Ҫ��д��
	Base(const Base &rhs) : a(rhs.a), b(rhs.b)
	{
		std::cout << "default copy constructor ..." << std::endl;

		init();
		memcpy( source, rhs.source, 10 * sizeof( int ) ); // memcpy�βΣ�Ŀ�ĵ�ַ��Դ��ַ��Ҫ�����ĳ��ȣ���С��
	}

	// ������ֵ����
	const Base& operator=(const Base &rhs)
	{
		std::cout << "copy assignment  ..." << std::endl;

		if (this == &rhs) return *this; // ��ֹ�Ը�ֵ��

		init();
		a = rhs.a;
		b = rhs.b;
		memcpy(source, rhs.source, 10 * sizeof(int)); // memcpy�βΣ�Ŀ�ĵ�ַ��Դ��ַ��Ҫ�����ĳ��ȣ���С��
	
		return *this;
	}

	~Base() // ��������, �����ͷ���Դ, ��������
	{
		std::cout << "deConstructor ..." << std::endl;

		delete[] source;// �ͷ�һ���ڴ�
	}

	void printAB()
	{
		std::cout << "a = " << a << ", b = " << b << std::endl;
	}

	void printSource()
	{
		for (int i = 0; i < 10; i++) {
			std::cout << "source[" << i << "] = " << source[i] << std::endl;
		}
	}

private:
	void init()
	{
		source = new int[10]; // ����һ���ڴ�
		if (source == nullptr) {//NULL
			exit(-1);
		}

		for (int i = 0; i < 10; i++) {
			source[i] = i;
		}

	}

private:
	int a;
	int b;

	int *source;
};

int main()
{
	/*Base base;

	base.printAB();

	Base base2(100, 200);
	base2.printAB();

	Base base3 = Base( 100, 400 ); 
	base3.printAB();


	Base base4( 1000, 2000 );
	Base base4_cpy = base4;
	base4_cpy.printAB();*/

	Base base5( 100, 200 );
	base5.printSource();

	std::cout << "------------------------" << std::endl;
	Base base5_cpy = base5;// �������õ��ǿ������캯��
	base5_cpy.printAB();
	base5_cpy.printSource(); 

	Base base5_cpy2( base5 );// �������õ��ǿ������캯��
	base5_cpy2.printAB();
	base5_cpy2.printSource();

	Base base5_cpy3; // ��ִ������Ĺ��캯��

	base5_cpy3 = base5; // ����ͻ���ÿ�����ֵ
	base5_cpy3.printAB();
	base5_cpy3.printSource();

	return 0;
}
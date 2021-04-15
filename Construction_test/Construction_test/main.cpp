#include <iostream>
//#define USE_TAG

/* һ���̳еĹ��캯��ԭ�� */
class ParentA
{
public:
	ParentA():a(5)
	{
		std::cout << "this is parent's construction function ..." << std::endl;
	}
	ParentA( int a_ )
	{
		a = a_;
		std::cout << "this is parent's parameter construction function ..." << a << std::endl;
	}
	~ParentA()
	{
		std::cout << "this is parent's deconstruction function ..." << std::endl;
	}

	void test()
	{
		std::cout << "a = " << a << std::endl;
	}

private:
	int a;
};

// 1. ������Լ̳и����е����г�Ա�ͷ��������˹��캯��
// 2. �����������ʱ��Ϊ�˳�ʼ���Ӹ���̳��������ݳ�Ա��ϵͳ��Ҫ�����丸��Ĺ��캯����
// 3. ���������û�й��췽��������ø�����޲ι��췽��
// 4. ��������ж����˹��췽���������Ǵ��εĻ��ǲ����εģ��ٶ����������ʱ������ִ�и����޲εĹ��췽����Ȼ��ִ���Լ��Ĺ��췽��
// 5. �ڴ����������ʱ���������Ĺ��캯��û����ʽ���ø���Ĺ��췽���������ø���Ĭ�ϵ��޲ι��췽��
// 6. �ڴ����������ʱ���������Ĺ��캯��û����ʽ���ø���Ĺ��췽���Ҹ����Լ��������޲ι��췽���������ø����Լ����޲ι��췽��
// 7. �ڴ����������ʱ���������Ĺ��캯��û����ʾ���ø���Ĺ��췽���Ҹ����Լ�û�ж����޲ι��췽����ֻ������
//�вι��캯������ʱ�����
// 8. ���������ø�����вι��캯������Ҫ�ó�ʼ�������Ա����ķ�ʽ�����£�
class childA :public ParentA
{
public:
	childA():ParentA( 5 ) // ���ֳ�ʼ����ʽ���������������еĳ�����const����Ա���г�ʼ��
	{
		std::cout << "this is child's construction ..." << std::endl;
	}
	/*child() // ������ֻ�д��ι��캯������ʱ�ᱨ��
	{
		std::cout << "this is child's construction ..." << std::endl;
	}*/
	~childA()
	{
		std::cout << "this is child's deconstruction ..." << std::endl;
	}

};

/* �����������캯�� */
class ClassA {
public:
	// 1. new ���ٵ��ڴ�һ���ڶ��ϣ�����ͨ�ı���������ջ��
	// 2. new ��������һ�ε�ַ�ռ���׵�ַ������һ����ָ���������ε�ַ
	// 3. 
	ClassA()
	{
		a = new int[8];
		std::cout << "address of a is: " << a << std::endl;
	}

	ClassA(const ClassA& A_)
	{
		a = new int[8];
		*a = *(A_.a);
		std::cout << "address of  copy of a is: " << a << std::endl;
	}

	~ClassA()
	{
		delete[] a;
	}

private:
	int *a;

};

/* ���� */

int main()
{
	ClassA a;
	ClassA b(a);

#ifdef USE_TAG
	std::cout << "use tag ..." << std::endl;
#endif
	return 0;
}
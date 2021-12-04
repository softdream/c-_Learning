#include <iostream>

void test( int& const a ) // ����дconst�������ã��ȼ��� int& a; ������warning �� qualifiers on reference are ignored
{
	std::cout << "a type = " << typeid(a).name() << std::endl;
	a++;// ���ǿ��Եģ�
	std::cout << "a ++ = " << a << std::endl;
	// ����� 5
}

void test2(const int& a) // ���� const���ε�a�Ǵ������Ĳ�����һ���������ں����ڲ��ܸ�����ֵ
{
	std::cout << "a type = " << typeid(a).name() << std::endl;
	// a ++; // error

}

void test3(int* const a)// ����const���ε���a, ����ָ�벻�ܱ�, ����ָ����ָ�����ݿ��Ա�
{
	std::cout << "a type = " << typeid(a).name() << std::endl;
	(*a) ++;// ָ��ָ�Ķ������Ա�
	// a++; // error: �����޸ĵ���ֵ
	std::cout << "a = " << (*a)++ << std::endl;
}

void test4(const int *a) // ����const���ε���int������ָ����ָ�����ݲ��ܱ䣬 ��*a���ܱ�
{
	std::cout << "a type = " << typeid(a).name() << std::endl;
	// (*a) ++; // error�������޸ĵ���ֵ
	a++;// ���ԣ� ��ַ���Ա�
	std::cout << "a = " << a++ <<std::endl;
}

int main()
{
	int a = 4;
	test(a);

	test2(a);

	test3(&a);

	test4(&a);

	return 0;
}
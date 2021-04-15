#include <iostream>

class Fraction
{
public:
	//---------- Non-explicit-one-argument ctr ---------//
	Fraction(int num, int den = 1):numerator(num), denominator(den)
	{

	}

	// ���������
	Fraction operator+(const Fraction& f)
	{
		return Fraction( numerator + f.numerator, denominator + f.denominator );
	}

	//------------ ת������ -------------//
	/*operator double() const
	{
		std::cout << "Conversion Function ..." << std::endl;
		return (double)(numerator / denominator);
	}*/

	void print() const
	{
		std::cout << "numerator = " << numerator << ", denominator = " << denominator << std::endl;
	}

private:
	int numerator;
	int denominator;
};

int main()
{
	Fraction f(3, 5);

	//double d = 8.0f + f; // ����conversion function�� f ת��Ϊdouble
	//std::cout << "d = " << d << std::endl;
	
	Fraction d2 = f + 4; // ����ʽ���캯��������ת���������棬
						//�����캯������Ϊ��ʾ�Ŀ��Ա����������,�ɱ�����ʽת��
	d2.print();

	return 0;
}
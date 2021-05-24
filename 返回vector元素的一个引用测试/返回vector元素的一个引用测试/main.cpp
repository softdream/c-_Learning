#include <vector>
#include <iostream>

int& getElement(std::vector<int> &vec, int index) {
	return vec[index];
}

void printVec(std::vector<int> &vec)
{
	std::cout << "----------------------" << std::endl;
	for (auto it : vec) {
		std::cout << it << std::endl;
	}
	std::cout << "----------------------" << std::endl;
}

int main()
{
	std::vector<int> vec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int &a = getElement( vec, 3 );
	std::cout << "a = " << a << std::endl;

	a = 300; //����aֻ��vector�ĵ��ĸ�Ԫ�صı������ѣ��ı�aҲ���Ǹı��˵��ĸ�Ԫ�ص�ֵ��
	//getElement(vec, 3) = 300;

	printVec(vec);

	return 0;
}
#include <iostream>
#include<string>


int main()
{	
	int T = 0; // ���ݵ�����
	int EqualCount = 0;

	std::cout << "���������ݵ�������" << std::endl;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		std::cout << "����� " << i << " ����ַ�����" << std::endl;

		std::string f;
		std::cin>>f;
		std::cout << "������ַ���Ϊ�� " << f << "�����ǣ�" << f.length() << std::endl; 

		const char *p = f.data();
		
		/* �ж��Ƿ�Ϊһ���������ڴ� */
		char temp[3]; // �м����ÿ�α��������ַ�
		for (int j = 0; j < f.length(); j += 3) {
			memset(temp, 0, sizeof(temp));
			memcpy( temp, &p[j], 3 );

			std::cout << "temp = " << temp << std::endl;

			for (int k = 0; k < 3; k++) { // ���бȽϣ�ÿ�����ַ�ֻҪ�ͺ�����ַ����бȽϾ��У�
										 // ��Ϊǰ��ıȽϹ���
				if (temp[k] != p[j + 3]) {
					EqualCount++;
				}
			}
			if (EqualCount > 1) { // �������ڴ����ֻ����һ���ַ���һ����
				std::cout << "�ⲻ��һ���������ڴ���" << std::endl;
				continue;
			}
			EqualCount = 0;
		}
		std::cout << "����һ���������ڴ���" << std::endl;
	}

	return 0;
}




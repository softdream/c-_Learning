#ifndef __RUN_LENGTH_CODE_
#define __RUN_LENGTH_CODE_

#include <iostream>

namespace pcs {

/* ���ֽ�Ϊ��λ�����γ̱��� */
class charRLC {
public:
	charRLC()
	{

	}
	~charRLC()
	{
		delete[] data;
	}

	void coding( char *input, int length );

private:
	char *data;
	int length;
};

void charRLC::coding( char *input, int length )
{
	int count = 0, p = 0;
	data = new char[ length * 2 ];
	for (int i = 0; i < length; i++) {
		if (count == 0){
			data[p] = input[i]; //������ĸ
			p++;
		}
		if (input[i - 1] != input[i] && i != 0){
			data[p] = count + '0'; //����תascll��������
			p++;
			count = 1;
			data[p] = input[i]; //������ĸ
			p++;
		}
		else {
			count++;
		}
	}
	data[p] = count + '0';//����תascll��������
	p++;

	std::cout << "data = " << data << std::endl;
}

}

#endif
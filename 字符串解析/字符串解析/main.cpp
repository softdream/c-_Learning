   
#include<string>   
#include<iostream>   
#include<vector>   
#include<sstream> 
#include<fstream>


//��������ת��ģ�庯��   
template <class Type>
Type stringToNum(const std::string &str)
{
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

int main()
{
	char *str1 = "$GPCHC,2066,272455.70,181.26,-0.09,0.70,-0.05,0.05,0.01,-0.0121,-0.0012,1.0015,40.12198055,116.45963268,20.71,-0.004,0.007,0.002,0.008,45,37,42,2,2*7F\r\n";
    char *str2 = "$GPCHC,2066,272455.70,181.26,-0.09,0.70,-0.05,0.05,0.01,-0.0121,-0.0012,1.0015,40.12198055,116.45963268,20.71,-0.004,0.007,0.002,0.008,45,37,42,2,2*7F\r\n";

	std::string s1 = str1;
	std::vector<std::string> arr1;  //����һ���ַ�������   
	int position = 0;
	do{
		std::string tmp_s;
		position = s1.find(","); //�ҵ����ŵ�λ��     
		tmp_s = s1.substr(0, position); //��ȡ��Ҫ���ַ���      
		s1.erase(0, position + 1); //���Ѷ�ȡ������ɾȥ       
		arr1.push_back(tmp_s);   //���ַ���ѹ��������    
	} while (position != -1);

	//std::cout << "s1 = " << s1 << std::endl;
	//std::cout << "length1 = " << s1.length() << std::endl;

	int d0 = stringToNum<int>( arr1[1] );
	printf("d0 = %d\r\n", d0);
	double d1 = stringToNum<double>(arr1[2]);
	printf( "d1 = %f\r\n", d1 );
	double d2 = stringToNum<double>(arr1[3]);
	printf("d2 = %f\r\n", d2);
	return 0;
}
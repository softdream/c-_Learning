#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>

const int question1( const int x )
{
	std::bitset<32> bits = x;

	std::string str = bits.to_string();// ����������ת�ַ�����
	//std::cout << "str = " << str << std::endl;

	std::string str_sub;

	int pose = str.find("1");
	str_sub = str.substr( pose ); // ��ȡ�������ַ�����������λ�� 0 ��
	//std::cout << "str_sub = " << str_sub << std::endl;

	int maxCount0 = 0, count0 = 0;// ������� 0 �ĸ�������ǰ���� 0 �ĸ�����
	int maxCount1 = 0, count1 = 0;// ������� 1 �ĸ�������ǰ���� 1 �ĸ�����

	for (int i = 0; i < str_sub.size(); i++) {
		if (str_sub[i] == '1') { // �����ǰԪ����1����ǰ����1�ĸ�������1
			count1++;
		}
		else { // ����ʹ��֮ǰ������ 1 �ĸ��������������� 1 �ĸ�����������ǰ������ 1 �ĸ������㣻
			maxCount1 = std::max( maxCount1, count1 );
			count1 = 0;
		}

		if (str_sub[i] == '0') { // ����ͬ�ϣ�
			count0++;
		}
		else {
			maxCount0 = std::max(maxCount0, count0);
			count0 = 0;
		}
	}

	maxCount0 = std::max(maxCount0, count0); // ����������� 0 �ĸ�����
	//std::cout << "max count 0 = " << maxCount0 << std::endl;

	maxCount1 = std::max(maxCount1, count1); // ����������� 1 �ĸ�����
	//std::cout << "max count 1 = " << maxCount1 << std::endl;

	return std::max( maxCount0, maxCount1 ); // �������������ģ�
}

const std::vector<int> question2(std::vector<int>& nums)
{
	std::vector<int> nums_cpy = nums; // ����һ��

	std::vector<int> ret; // �������

	std::sort( nums_cpy.begin(), nums_cpy.end() );// �Ա��ݵ��������һ����������

	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == nums_cpy[i]) { // λ�öԵ��ϵ�Ԫ�ؾ�������������Ԫ��
			ret.push_back(nums[i]);
		}
	}

	return ret;
}


class Solution {
public:
	std::vector<int> sortByBits(std::vector<int>& arr) 
	{
		std::sort(arr.begin(), arr.end(),
			[&](int x, int y) { 
			if (bitsSize(x) < bitsSize(y)) {
				return true;
			}
			if (bitsSize(x) > bitsSize(y)) {
				return false;
			}
			return x < y;
			});

		return arr;
	}

private:
	const int bitsSize(const int num)
	{
		std::bitset<32> bits = num;
		return bits.count();
	}

};

int main()
{
	/*int ret = question1(17);
	std::cout << "ret = " << ret << std::endl;

	std::vector<int> nums = { 1, 3, 2, 4, 5 };
	std::vector<int> ans = question2( nums );

	for (auto it : ans) {
		std::cout << it << " ";
	}
	std::cout << std::endl;*/


	std::vector<int> arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> ret2 = Solution().sortByBits( arr );

	for (auto it : ret2) {
		std::cout << it << " ";
	}
	std::cout << std::endl; 
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<string> findWords(vector<string>& words) {
		std::vector<char> table1 = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' };
		std::vector<char> table2 = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
		std::vector<char> table3 = { 'z', 'x','c', 'v', 'b', 'n', 'm','Z','X','C','V','B','N','M' };

		std::vector<std::string> ans;

		for (auto it : words) {
			int count = 0;
			// �����ڵ�һ����
			for (int i = 0; i < it.size(); i++) {
				auto ret1 = std::find(table1.begin(), table1.end(), it[i]);
				if (ret1 == table1.end()) {

				}
				else { // �ҵ���
					count++;
				}
			}
			if (count == it.size()) { // �ڵ�һ��
				ans.push_back(it);
			}

			count = 0;
			// �ڵڶ�����
			for (int i = 0; i < it.size(); i++) {
				auto ret2 = std::find(table2.begin(), table2.end(), it[i]);
				if (ret2 == table2.end()) {

				}
				else { // �ҵ���
					count++;
				}
			}
			if (count == it.size()) { // �ڵ�2��
				ans.push_back(it);
			}

			count = 0;
			// �ڵ�3����
			for (int i = 0; i < it.size(); i++) {
				auto ret3 = std::find(table3.begin(), table3.end(), it[i]);
				if (ret3 == table3.end()) {

				}
				else { // �ҵ���
					count++;
				}
			}
			if (count == it.size()) { // �ڵ�3��
				ans.push_back(it);
			}
		}

		return ans;
	}
};

int main()
{
	std::vector<std::string> t = { "Hello","Alaska","Dad","Peace" };

	std::vector<std::string> ret = Solution().findWords( t );

	for (auto it : ret) {
		std::cout << it.c_str() << std::endl;
	}

	return 0;
}
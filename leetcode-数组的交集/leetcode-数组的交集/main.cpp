#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		std::vector<int> ret;
		for (auto it : nums1) {
			// ������2��Ѱ�Ҹ�����1����ȵ���
			auto item = std::find(nums2.begin(), nums2.end(), it);
			if (item != nums2.end()) {// ����ҵ���
				auto item2 = std::find(ret.begin(), ret.end(), *item);
				// �ȿ��½������ret���Ƿ��Ѿ���������ˣ�û�вż��룬��������ظ�����
				if (item2 == ret.end()) {
					ret.push_back( *item );
				}
			}
		}

		return ret;
	}

	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		std::vector<int> ret;
		if (nums1.size() < nums2.size()) {
			for (auto it : nums1) {
				auto item = std::find(nums2.begin(), nums2.end(), it);
				if (item != nums2.end()) {// ����ҵ���
					ret.push_back(*item);
				}
			}
		}
		else {
			for (auto it : nums2) {
				auto item = std::find(nums1.begin(), nums2.begin(), it);
				if (item != nums1.end()) {
					ret.push_back( *item );
				}
			}
		}

		return ret;
	}
};

int main()
{
	std::vector<int> nums1 = { 4,9,5 }, nums2 = { 9,4,9,8,4 };

	std::vector<int> ret = Solution().intersection( nums1, nums2 );

	for (auto it : ret) {
		std::cout << it << std::endl;
	}

	return 0;
}

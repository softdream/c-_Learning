#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}

};

class Solution {
public:
	//˫ָ�뷨������ָ�룬��ָ�����ָ�����k������ָ�뵽ͷ��ʱ����ָ��ָ��Ԫ�ؾ��ǵ�����k��
	ListNode* getKthFromEnd(ListNode* head, int k)
	{
		ListNode *fast = head->next, *slow = head->next;
		int count = 0;
		while (fast != nullptr) {
			count++;
			if (count > k) {
				slow = slow->next;
			}
			fast = fast->next;
		}
		return slow;
	}

	bool insert(ListNode *head, int value)
	{
		ListNode *node = new ListNode(value);
		if (node == nullptr) {
			return false;
		}

		node->next = head->next;
		head->next = node;
		return true;
	}


	void printList(ListNode *head) {
		ListNode *p = head->next;
		int count = 0;
		while (p != nullptr) {
			std::cout << "node " << count << ": " << p->val << std::endl;
			count++;
			p = p->next;
		}
	}

	void createAList(ListNode *head, std::initializer_list<int> init)
	{
		for (auto it : init) {
			insert(head, it);
		}
	}

	// �����ӡ����
	vector<int> reversePrint(ListNode* head)
	{
		std::stack<ListNode*> stack;
		std::vector<int> vec;

		ListNode *p = head;
		while (p != nullptr) {
			stack.push(p);
			p = p->next;
		}

		while (!stack.empty()) {
			ListNode *n = stack.top();
			vec.push_back(n->val);
			stack.pop();
		}
		return vec;
	}

	// ɾ���������ظ���Ԫ��
	ListNode* deleteDuplicates(ListNode* head)
	{
		ListNode *p = head->next;
		ListNode *ret = p;

		while (p != nullptr && p->next != nullptr ) {
			if (p->val == p->next->val) {
				p->next = p->next->next; // ɾ��
			}
			p = p->next;
		}
		return ret;
	}
};

int main()
{
	Solution s;

	ListNode list(0);

	s.createAList(&list, { 3, 3, 2, 1, 1 });

	s.printList(&list);
	std::cout << "-----------------------" << std::endl;

	ListNode *ret = s.deleteDuplicates( &list );
	s.printList(ret);

	return 0;
}
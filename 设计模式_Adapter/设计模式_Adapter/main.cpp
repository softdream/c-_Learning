#include <iostream>
#include <deque>

/*
	���ģʽ--������
*/

//queue�����й��ܶ�����deque��ɵģ�ֻ�Ƕ�deque��һ�����·�װ�������µĲ���
template<class T, class Sequence = deque<T>>
class queue
{
protected:
	Sequence c; // �ײ�����

public:
	bool empty() const
	{
		return c.empty();
	}

	size_t size() const
	{
		return c.size();
	}

	T& front()
	{
		return c.front();
	}

	T& back()
	{
		return c.back();
	}

	void push(const T& x)
	{
		c.push_back(x);
	}

	void pop()
	{
		c.pop_front();
	}
};

int main()
{
	return 0;
}
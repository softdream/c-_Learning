#include <iostream>
#include <functional>
#include <map>

// ģ�庯��ָ��Ķ��� Type<T>::Action(T)
// ���԰��������ָ��ŵ�����߽ṹ����.
template <class T>
struct Type
{
	typedef void(*Action)(T);
};
// Ҳ���԰��������ָ��ŵ�һ��ģ�巽����.
template <class T> void Func(void(*Action)(T), T val) {
	Action(val);
}


template<typename T>
struct Event{
	Type<T> callback;
 	T arg;
};

void callback( int a )
{
	std::cout << "a = " <<a<< std::endl;
}

void trigger()
{

}

template<typename T>
void setCb(Type<T>::Action cb )
{

}

int main()
{
	//setCb<int>(callback);


	return 0;
}

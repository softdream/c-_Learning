#include <iostream>

/*
	Handle/Body
	Pointer To Implementation
*/

class StringRep;

class String
{
public:
	String()
	{

	}
	String(const char *s)
	{

	}
	String(const String& s)
	{

	}
	String& operator=(const String& s)
	{

	}

private:
	StringRep* rep;// pimpl , ������֮���ϵ��ͨ��ָ�븴�ϵ�
};

class StringRep
{
	friend class String;
	StringRep(const char *s)
	{

	}

	int count;
	char* rep;
};


int main()
{

}

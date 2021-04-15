#include <iostream>
#include <stdlib.h>

#include <forward_list>

std::forward_list<int> list{10, 20, 30};

/* �����һ���ڵ� */
typedef struct TNode {
	int data; // ������
	struct TNode *next;// ָ����
}TNode, *TNodePtr;

bool initLinkList(TNode **linkList)
{
	*linkList = (TNode*)malloc(sizeof(TNode));
	if (!linkList) {
		std::cout << "�����ڴ�ʧ�ܣ�" << std::endl;
		return false;
	}
	(*linkList)->next = NULL;
	std::cout << "link = " << *linkList << std::endl;
	return true;
}

/* ����һ���µ����ݵ���������, ʹ��ͷ�巨 */
//������node�������ڵ��ָ��
//������data�����������
bool insert( TNode **linkList, int data)
{
	//std::cout << "link = " << *linkList << std::endl;
	TNodePtr node = NULL;
	node = ( TNode* )malloc( sizeof( TNode ) );
	if (!node) {
		//std::cout << "�����ڴ�ʧ�ܣ�" << std::endl;
		printf( "�����ڴ�ʧ�ܣ�\n" );
		return false;
	}
	node->data = data;
	node->next = (*linkList)->next;
	(*linkList)->next = node;
	return true;
}

/* ɾ���ڵ� */
//�βΣ�data��Ҫɾ����Ԫ��
//�βΣ�linkList��������ͷָ��
bool deleNode(TNode **linkList, int data)
{
	//std::cout << "link4 = " << *linkList << std::endl;
	if (!(*linkList)) {
		return false;
	}
	TNode *ptr = *linkList;
	while (ptr->next != NULL) {
		if (ptr->next->data == data) {
			TNode *node = NULL;
			node = ptr->next;
			ptr->next = ptr->next->next;
			free( node );
		}
		else {
			ptr = ptr->next;
		}
	}
	return true;
}

/* ��ӡ���� */
void printLinkList(TNode **linkList)
{
	int nodeCount = 0;
	if (*linkList == NULL) {
		exit( -1 );
	}
	TNode *ptr = *linkList;
	while (ptr->next != NULL) {
		ptr = ptr->next;
		nodeCount++;
		printf("�� %d �������ǣ�%d\n", nodeCount, ptr->data);
		//std::cout << "�� " << nodeCount << "�������ǣ�" << linkList->next << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
}

int main()
{
	/*TNode *link = NULL ;// ����һ��������
	if (initLinkList(&link)) printf( "��ʼ���ɹ���" );
	else printf( "��ʼ��ʧ�ܣ�" );

	//std::cout << "link = " << link << std::endl;

	if (insert(&link, 10)) 
		std::cout << "������һ���ڵ� ..." << std::endl;
	else 
		std::cout << "����ڵ�ʧ�� ..." << std::endl;
	if (insert(&link, 20))
		std::cout << "������һ���ڵ� ..." << std::endl;
	else
		std::cout << "����ڵ�ʧ�� ..." << std::endl;
	if (insert(&link, 30)) 
		std::cout << "������һ���ڵ� ..." << std::endl;
	else
		std::cout << "����ڵ�ʧ�� ..." << std::endl;
	if (insert(&link, 40))
		std::cout << "������һ���ڵ� ..." << std::endl;
	else
		std::cout << "����ڵ�ʧ�� ..." << std::endl;

	printLinkList( &link );

	if (deleNode(&link, 20))
		std::cout << "ɾ��һ���ڵ� ..." << std::endl;
	else
		std::cout << "ɾ���ڵ�ʧ�� ..." << std::endl;
	if (deleNode(&link, 10))
		std::cout << "ɾ��һ���ڵ� ..." << std::endl;
	else
		std::cout << "ɾ���ڵ�ʧ�� ..." << std::endl;
	printLinkList(&link);*/

	int i = 0;
	for (auto it = list.begin(); it != list.end(); it++) {
		i++;
		std::cout << "�� " << i << " ��Ԫ���ǣ�" << *it << std::endl;
	}
	return 0;
}
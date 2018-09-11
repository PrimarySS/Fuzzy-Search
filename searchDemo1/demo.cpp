
/*
***���ݽṹʵ���ֵ���ǰ׺��Ϣͳ��***
*/

#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

#define  Max  26		//����a-z

//�����ֵ����Ľṹ��
typedef struct Trie
{
	Trie *Next[Max];	//����ָ�����飬���������������

	int v;	//��Ա����

}root;

//�����±�
Trie * creatRoot()
{
	Trie *root = (Trie *)malloc(sizeof(Trie));

	root -> v = 1;	//�Ը��ַ�Ϊǰ׺����Ϣ����

	memset(root -> Next,NULL,sizeof(root -> Next));		//��ʼ���ߣ�Ϊ�µı߿��ٿռ�

	return root;
}


/*�������
��ǰ׺��Ϣ�����ڱ���
*/
void InSert(char *str,Trie *root){

	Trie *p = root;	//����һ����

	int len = strlen(str);	//��ø�ǰ׺�ĳ���

	for (int i = 0; i < len; i++)	//��ÿ���ַ���ӵ��ֵ����ı���
	{
		int id = str[i] - 'a';	//��ô����ߵı��

		if (p -> Next[id] == NULL)	//���û�бߣ�����һ���ߴ�����ַ�
		{
			p -> Next[id] = creatRoot();	//�ҵ������ı�

			p = p -> Next[id];
		}
		//������ڱߣ������ű���
		else
		{
			p = p -> Next[id];

			p -> v+=1;
		}
	}
}


/*��ѯ����
������Ϣ��ǰ׺���ֵ�����Ӧλ�õ���Ϣһһƥ��
*/
int Query(char *str,Trie *root)
{
	Trie *p = root;

	int len = strlen(str);

	for (int i = 0; i < len; i++)	// ��������ֵ�����ÿһ���ַ�
	{
		int id = str[i] - 'a';	// ��ô����ߵı��

		p = p -> Next[id];		// �����һ�ڵ����Ϣ

		if (p == NULL)	// ��Ϊ�ռ����򲻴����Ը��ַ�Ϊǰ׺����Ϣ
		{
			return 0;
		}
		if (i == len - 1)	// ����	
		{
			return p -> v;
		}
	}
}


// �ͷ��ֵ���
void releseTrie(Trie *T)
{
	if (T == NULL)return;	// �ֵ���Ϊ��ֱ�ӷ���

	// �ͷ�ÿһ���ڵ�ռ���ֵ������ڴ�
	for (int i = 0; i < Max; i++)
	{
		if (T -> Next[i])
		{
			free(T -> Next[i]);
		}
	}
	delete(T);
}


int main()
{
	Trie *root = new Trie();	//�������ڵ�

	char str[20];

	bool flag = false;

	while(gets_s(str))
	{
		if (flag)
		{
			cout << Query(str,root) << endl;
		}
		else
		{
			if (strlen(str) != 0)
			{
				InSert(str,root);
			}
			else
			{
				flag = true;
			}
		}
	}

	releseTrie(root);	//�ͷ�����Դ

	return 0;
}
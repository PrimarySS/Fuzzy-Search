
/*
***Ӣ���ֵ��������ģ������***
*/

#include<iostream>
#include<cstring>
#include<cstdlib>

#define Max 26
int a[Max];

// �ֵ����ṹ��
typedef struct Trie
{
	struct Trie *Next[Max];

	int isStr;	//�жϵ����Ƿ����

}root;

// Ϊ�ֵ������ٿռ�
Trie * Init()
{
	Trie *root = (Trie*)malloc(sizeof(Trie));

	root -> isStr = NULL;

	memset(root->Next,NULL,sizeof(root->Next));

	return root;
}

// �����ֵ���
int Insert(char *str,Trie *root)
{
	Trie *p = root;

	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		int id = str[i] - 'a';	// ��ĸ��Ӧ���±��Ǹ���ĸ���ַ�ֵ��ȥ��ĸa���ַ�ֵ

		if (p -> Next[id] == NULL)
		{
			p -> Next[id] = Init();

			p = p -> Next[id];
		}
		else
		{
			p = p -> Next[id];
		}
	}
	// �������Ǹ��ڵ�ı����Ϊ1,��ʾ����ַ����Ѿ��洢������.
	// 0˵����������Ѿ�������,��Ҫ���,1˵����ӳɹ�.
	if (p->isStr == 1)return 0;
	p->isStr = 1;
	return 1;
}


// ��ѯ���
int visit(char *str,Trie *root,int max,int count)
{
	if (root -> isStr == 1)		// �����ǰ׺������ַ��н����ڵ�
	{
		printf("%s",str);

		for (int i = 0; i < count; i++)
			printf("%c",a[i] + 'a');	

		printf("\n");
	}

	for (int i = 0; i < max; i++)
	{
		if (root -> Next[i] != NULL)
		{
			a[count] = i;	// �������±����ĸ�����һһ��Ӧ

			visit(str,root->Next[i],max,count+1);
		}
	}
	return 0;
}


// ��ȷ��ѯĿ���ַ���,�õ��ýڵ�
int Query(char *str,Trie *root)
{
	Trie *p = root;

	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		int id = str[i] - 'a';

		if (p -> Next[id])p = p -> Next[id];

		else return 0;
	}
	Trie *newStr = p;	// �õ�ǰ׺������ַ�

	int count = 0;

	visit(str,newStr,Max,count);	// �ݹ������������

	return 0;
}


// �ͷ��ڴ�
void releseTrie(Trie *root)
{
	if (root == NULL)return;

	for (int i = 0; i < Max; i++)
	{
		if (root->Next[i] != NULL)
		{
			free(root->Next[i]);
		}
	}
	delete(root);
}


int main()
{
	Trie *root = new Trie();

	char str[15];

	bool flag = false;

	while(gets_s(str))
	{
		if (flag)
		{
			Query(str,root);
		}
		else
		{
			if (strlen(str) != 0)
			{
				Insert(str,root);
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
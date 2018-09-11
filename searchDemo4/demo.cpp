
/*
***英文字典树先序版模糊搜索***
*/

#include<iostream>
#include<cstring>
#include<cstdlib>

#define Max 26
int a[Max];

// 字典树结构体
typedef struct Trie
{
	struct Trie *Next[Max];

	int isStr;	//判断单词是否存在

}root;

// 为字典树开辟空间
Trie * Init()
{
	Trie *root = (Trie*)malloc(sizeof(Trie));

	root -> isStr = NULL;

	memset(root->Next,NULL,sizeof(root->Next));

	return root;
}

// 创建字典树
int Insert(char *str,Trie *root)
{
	Trie *p = root;

	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		int id = str[i] - 'a';	// 字母对应的下标是该字母的字符值减去字母a的字符值

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
	// 将最后的那个节点的标记置为1,表示这个字符串已经存储在树里.
	// 0说明这个单词已经在树中,需要添加,1说明添加成功.
	if (p->isStr == 1)return 0;
	p->isStr = 1;
	return 1;
}


// 查询输出
int visit(char *str,Trie *root,int max,int count)
{
	if (root -> isStr == 1)		// 输入的前缀的最后字符有结束节点
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
			a[count] = i;	// 将数组下标和字母组成了一一对应

			visit(str,root->Next[i],max,count+1);
		}
	}
	return 0;
}


// 精确查询目标字符串,得到该节点
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
	Trie *newStr = p;	// 拿到前缀的最后字符

	int count = 0;

	visit(str,newStr,Max,count);	// 递归遍历它的子树

	return 0;
}


// 释放内存
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
	releseTrie(root);	//释放树资源

	return 0;
}
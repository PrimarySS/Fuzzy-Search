
/*
***数据结构实现字典树前缀信息统计***
*/

#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

#define  Max  26		//测试a-z

//定义字典树的结构体
typedef struct Trie
{
	Trie *Next[Max];	//创建指针数组，定义树的最大容量

	int v;	//成员变量

}root;

//创建新边
Trie * creatRoot()
{
	Trie *root = (Trie *)malloc(sizeof(Trie));

	root -> v = 1;	//以该字符为前缀的信息个数

	memset(root -> Next,NULL,sizeof(root -> Next));		//初始化边，为新的边开辟空间

	return root;
}


/*插入操作
把前缀信息保存在边上
*/
void InSert(char *str,Trie *root){

	Trie *p = root;	//创建一条边

	int len = strlen(str);	//获得该前缀的长度

	for (int i = 0; i < len; i++)	//将每个字符添加到字典树的边上
	{
		int id = str[i] - 'a';	//获得创建边的编号

		if (p -> Next[id] == NULL)	//如果没有边，创建一条边代表该字符
		{
			p -> Next[id] = creatRoot();	//找到创建的边

			p = p -> Next[id];
		}
		//如果存在边，则沿着边走
		else
		{
			p = p -> Next[id];

			p -> v+=1;
		}
	}
}


/*查询操作
将该信息的前缀与字典树对应位置的信息一一匹配
*/
int Query(char *str,Trie *root)
{
	Trie *p = root;

	int len = strlen(str);

	for (int i = 0; i < len; i++)	// 先序遍历字典树上每一个字符
	{
		int id = str[i] - 'a';	// 获得创建边的编号

		p = p -> Next[id];		// 获得下一节点的信息

		if (p == NULL)	// 若为空集，则不存在以该字符为前缀的信息
		{
			return 0;
		}
		if (i == len - 1)	// 存在	
		{
			return p -> v;
		}
	}
}


// 释放字典树
void releseTrie(Trie *T)
{
	if (T == NULL)return;	// 字典树为空直接返回

	// 释放每一个节点占用字典树的内存
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
	Trie *root = new Trie();	//创建树节点

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

	releseTrie(root);	//释放树资源

	return 0;
}
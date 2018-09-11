#include <string>  
#include <map>  
#include <vector>  
#include <iostream>
using namespace std;

#define CH_SIZE 1	// 设置汉字大小

struct trie_node  
{  
	trie_node()  
	{  
		count = 0;  
	}  

	int count;	// 表示以该汉字结束的字符串个数

	map<string, trie_node *> child;		// key为当前汉字，value为后面汉字节点的指针  
};  


class trie  
{
public:  
	trie();  

	void insert_str(string str);	// 插入字符串  

	trie_node *search_str_pre(string str_pre);	// 查询字符串前缀 

	vector<string> get_str_pre(string str);	// 返回所有前缀为str的字符串  

private:  
	void add_str(trie_node *root, string pre_str, vector<string> &ret);    // 递归添加以pre_str为前缀的字符串到ret集合  

private:  
	struct trie_node *root;  
};  
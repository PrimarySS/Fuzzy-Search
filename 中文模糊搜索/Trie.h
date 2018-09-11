#include <string>  
#include <map>  
#include <vector>  
#include <iostream>
using namespace std;

#define CH_SIZE 1	// ���ú��ִ�С

struct trie_node  
{  
	trie_node()  
	{  
		count = 0;  
	}  

	int count;	// ��ʾ�Ըú��ֽ������ַ�������

	map<string, trie_node *> child;		// keyΪ��ǰ���֣�valueΪ���溺�ֽڵ��ָ��  
};  


class trie  
{
public:  
	trie();  

	void insert_str(string str);	// �����ַ���  

	trie_node *search_str_pre(string str_pre);	// ��ѯ�ַ���ǰ׺ 

	vector<string> get_str_pre(string str);	// ��������ǰ׺Ϊstr���ַ���  

private:  
	void add_str(trie_node *root, string pre_str, vector<string> &ret);    // �ݹ������pre_strΪǰ׺���ַ�����ret����  

private:  
	struct trie_node *root;  
};  
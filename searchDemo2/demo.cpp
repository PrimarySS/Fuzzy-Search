
/*
***�����ֵ���***
*/


#include <string>  
#include <map>  
#include <vector>  
#include <iostream>
using namespace std;

#define CH_SIZE 2	// ���ú��ִ�С

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

	trie_node *search_str(string str);	// ��ѯ�ַ���  

	trie_node *search_str_pre(string str_pre);	// ��ѯ�ַ���ǰ׺ 

	void delete_str(string str);	// ɾ���ַ���  

	vector<string> get_str_pre(string str);	// ��������ǰ׺Ϊstr���ַ���  
	
	void clear();	// ���

private:  
	void add_str(trie_node *root, string pre_str, vector<string> &ret);    // �ݹ������pre_strΪǰ׺���ַ�����ret����  

private:  
	struct trie_node *root;  
};  


trie::trie()  
{  
	root = new trie_node();  
}  


// �����ַ���  
void trie::insert_str(string str)  
{  
	if (root == NULL || str == "")return ;  

	trie_node *cur_node = root;  

	for (unsigned int i = 0; i < str.size();)  
	{  
		string sub_str = str.substr(i, CH_SIZE);  // ����һ���½��ĳ�ʼ��Ϊstring������Ӵ�

		map<string, trie_node *>::iterator iter = cur_node -> child.find(sub_str);	// �ҵ�string�����е�sub_str  

		if (iter == cur_node -> child.end())	// �����map��û���ҵ�������½ڵ�  
		{  
			trie_node *tmp_node = new trie_node(); 

			cur_node -> child.insert(pair<string, trie_node *>(sub_str, tmp_node));

			cur_node = tmp_node;  
		}  
		else//����ҵ���value��Ϊָ����һ���ڵ��ָ��  
		{  
			cur_node = iter -> second;  // the second stored value
		}  
		i = i + CH_SIZE ;  
	}  

	cur_node->count++;  
}  


// ��ѯ�ַ���ǰ׺  
trie_node * trie::search_str_pre(string str)  
{  
	if (str == "")return root;  

	if (NULL == root )return NULL;  

	trie_node *cur_node = root;  

	unsigned int i;  
	for ( i = 0; i < str.size(); )  
	{  
		string sub_str = str.substr(i, CH_SIZE);  

		map<string, trie_node *>::iterator iter = cur_node -> child.find(sub_str);  

		if (iter == cur_node -> child.end())  
		{  
			return NULL;  
		}  
		else  
		{  
			cur_node = iter -> second;  
		}  
		i = i + CH_SIZE;  
	}  

	if (i == str.size())return cur_node;  

	else  return NULL;  
}  


// ��ѯ�ַ���  
trie_node * trie::search_str(string str)  
{  
	trie_node * find_pre_node = search_str_pre(str);  // �鿴ǰ׺�Ƿ����

	if (find_pre_node != NULL)  
	{  
		if (find_pre_node -> count == 0)  
		{  
			return NULL;  
		}  
		else  
		{  
			return find_pre_node;  
		}  
	}  
}  


// �ݹ������pre_strΪǰ׺���ַ�����ret����  
void trie::add_str(trie_node *root, string pre_str, vector<string> &ret)  
{  

	for (map<string, trie_node *>::iterator iter = root -> child.begin(); iter != root -> child.end(); iter++)  
	{  
		add_str(iter -> second, pre_str + iter -> first, ret);  
	}  

	if (root->count != 0)  
	{  
		ret.push_back(pre_str);  // push_back()���ֵΪval��Ԫ�ص���ǰvectorĩβ
	}  
}  


// ��������ǰ׺Ϊstr���ַ���  
vector<string> trie::get_str_pre(string str)  
{  
	vector<string> ret;  

	trie_node *find_node = search_str_pre(str);  

	if (find_node != NULL)  
	{  
		add_str(find_node, str, ret);  
	}  

	return ret;  
} 


// ɾ���ַ���  
void trie::delete_str(string str)  
{  
	trie_node *find_node = search_str(str);  

	if (find_node)  
	{  
		find_node -> count--;  
	}  
}  


 // ���  
void trie::clear()  
{  
	vector<trie_node *> que;  
	que.push_back(root);  

	while (!que.empty())  
	{  
		for (map<string, trie_node *>::iterator iter = root -> child.begin(); iter != root->child.end(); iter++)  
		{  
			que.push_back(iter->second);  
		}  

		trie_node *del_node = que.front();  // front()�������ص�ǰvector��ʼԪ�ص�����

		que.pop_back();

		delete del_node;  
	}  
}  



int main()
{
        trie t;
        int n;
        string str;
        vector<string> ret;

        cout << "�����ֵ�����";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
                cin >> str;
                t.insert_str(str);
        }

        cout << "\n����ؼ��֣�" << endl;
        cin >> str;

        ret = t.get_str_pre(str);

		// ������������
        for (vector<string>::iterator iter = ret.begin(); iter != ret.end(); iter++)
        {
                cout << *iter << endl;
        }

        return 0;
}

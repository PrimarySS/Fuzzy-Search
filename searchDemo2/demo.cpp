
/*
***中文字典树***
*/


#include <string>  
#include <map>  
#include <vector>  
#include <iostream>
using namespace std;

#define CH_SIZE 2	// 设置汉字大小

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

	trie_node *search_str(string str);	// 查询字符串  

	trie_node *search_str_pre(string str_pre);	// 查询字符串前缀 

	void delete_str(string str);	// 删除字符串  

	vector<string> get_str_pre(string str);	// 返回所有前缀为str的字符串  
	
	void clear();	// 清空

private:  
	void add_str(trie_node *root, string pre_str, vector<string> &ret);    // 递归添加以pre_str为前缀的字符串到ret集合  

private:  
	struct trie_node *root;  
};  


trie::trie()  
{  
	root = new trie_node();  
}  


// 插入字符串  
void trie::insert_str(string str)  
{  
	if (root == NULL || str == "")return ;  

	trie_node *cur_node = root;  

	for (unsigned int i = 0; i < str.size();)  
	{  
		string sub_str = str.substr(i, CH_SIZE);  // 返回一个新建的初始化为string对象的子串

		map<string, trie_node *>::iterator iter = cur_node -> child.find(sub_str);	// 找到string对象中的sub_str  

		if (iter == cur_node -> child.end())	// 如果在map中没有找到则插入新节点  
		{  
			trie_node *tmp_node = new trie_node(); 

			cur_node -> child.insert(pair<string, trie_node *>(sub_str, tmp_node));

			cur_node = tmp_node;  
		}  
		else//如果找到了value即为指向下一个节点的指针  
		{  
			cur_node = iter -> second;  // the second stored value
		}  
		i = i + CH_SIZE ;  
	}  

	cur_node->count++;  
}  


// 查询字符串前缀  
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


// 查询字符串  
trie_node * trie::search_str(string str)  
{  
	trie_node * find_pre_node = search_str_pre(str);  // 查看前缀是否存在

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


// 递归添加以pre_str为前缀的字符串到ret集合  
void trie::add_str(trie_node *root, string pre_str, vector<string> &ret)  
{  

	for (map<string, trie_node *>::iterator iter = root -> child.begin(); iter != root -> child.end(); iter++)  
	{  
		add_str(iter -> second, pre_str + iter -> first, ret);  
	}  

	if (root->count != 0)  
	{  
		ret.push_back(pre_str);  // push_back()添加值为val的元素到当前vector末尾
	}  
}  


// 返回所有前缀为str的字符串  
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


// 删除字符串  
void trie::delete_str(string str)  
{  
	trie_node *find_node = search_str(str);  

	if (find_node)  
	{  
		find_node -> count--;  
	}  
}  


 // 清空  
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

		trie_node *del_node = que.front();  // front()函数返回当前vector起始元素的引用

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

        cout << "输入字典树：";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
                cin >> str;
                t.insert_str(str);
        }

        cout << "\n输入关键字：" << endl;
        cin >> str;

        ret = t.get_str_pre(str);

		// 迭代遍历集合
        for (vector<string>::iterator iter = ret.begin(); iter != ret.end(); iter++)
        {
                cout << *iter << endl;
        }

        return 0;
}

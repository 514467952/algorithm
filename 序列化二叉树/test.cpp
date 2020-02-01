#include<iostream>
#include<string>
using namespace std;
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
class Solution {
public:
	void Serialize2(TreeNode* root, string& res)
	{
		if (root == NULL)
		{
			res += '#';
			return;
		}
		string s = to_string(root->val);
		res += s;
		res += '!';
		Serialize2(root->left, res);
		Serialize2(root->right, res);
	}
	char* Serialize(TreeNode *root) {
		if (root == NULL)
			return NULL;
		string res;
		Serialize2(root, res);
		char *str = new char[res.length() + 1];
		int i = 0;
		for (; i<res.size(); ++i)
		{
			str[i] = res[i];
		}
		str[i] = '\0';
		return str;
	}
	TreeNode* Deserialize2(char** str)
	{
		if (**str == '#')
		{
			(*str)++;
			return NULL;
		}

		int num = 0;
		while ((**str) != '\0' && (**str) != '!')
		{
			num = num * 10 + ((**str) - '0');
			++(*str);
		}
		TreeNode* root = new TreeNode(num);
		if ((**str) == '\0')
			return root;
		else
			(*str)++;
		root->left = Deserialize2(str);
		root->right = Deserialize2(str);
		return root;
	}

	TreeNode* Deserialize(char *str) {
		if (str == nullptr)
			return nullptr;

		TreeNode* res = Deserialize2(&str);
		return res;
	}
};
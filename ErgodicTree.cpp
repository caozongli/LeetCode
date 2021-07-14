#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
void preOrderTree(TreeNode *root)
{
	if(!root) return;
	stack<int> s;
	TreeNode *p;
	s.push(root);
	while(!s.empty())
	{
		p = s.top();
		if(p)
		{
			s.pop();
			if(p->right) s.push(p->right);
			if(p->left) s.push(p->left);
			s.push(p);
			s.push(nullptr);
		}
		else
		{
			s.pop();
			cout << s.top()->val << endl;
			s.pop();
		}
	}

}

void inOrderTree(TreeNode *root)
{
	if(!root) return;
	stack<int> s;
	TreeNode *p;
	s.push(root);
	while(!s.empty())
	{
		p = s.top();
		if(p)
		{
			s.pop();
			if(p->right) s.push(p->right);
			s.push(p);
			s.push(nullptr);
			if(p->left) s.push(p->left);	
		}
		else
		{
			s.pop();
			cout << s.top()->val << endl;
			s.pop();
		}
	}

}



void postOrderTree(TreeNode *root)
{
	if(!root) return;
	stack<int> s;
	TreeNode *p;
	s.push(root);
	while(!s.empty())
	{
		p = s.top();
		if(p)
		{
			s.pop();
			s.push(p);
			s.push(nullptr);
			if(p->right) s.push(p->right);
			if(p->left) s.push(p->left);	
		}
		else
		{
			s.pop();
			cout << s.top()->val << endl;
			s.pop();
		}
	}

}







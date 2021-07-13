#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


ListNode *sort(ListNode *one, ListNode *two)
{
	ListNode *p1 = one;
	ListNode *p2 = two;
	ListNode *res;
	ListNode *p3;
	if(p1->val > p2->val)
	{
		res = p2;
		p2 = p2->next;
	}
	else
	{
		res = p1;
		p1 = p1->next;
	}
	p3 = res;
	while(p1 && p2)
	{
		if(p1->val > p2->val)
		{
		p3->next = p2;
		p2 = p2->next;
		}
		else
		{
		p3->next = p1;
		p1 = p1->next;
		}
		p3 = p3->next;
	}
	if(p1)p3->next = p1;
	if(p2) p3->next = p2;
	return res;
}


ListNode* merge(ListNode *head, ListNode *end)
{
        if(head==end) return head;
        ListNode *mid = head;
        ListNode *fast = head;
        while(fast && fast->next)
        {
            if(fast->next==end)
            {
                fast = fast->next;
                break;
            }
	    mid = mid->next;
            fast = fast->next->next;
        }
	ListNode *q = mid->next;
	mid->next = nullptr;
        ListNode *h = merge(head, mid);
        end->next = nullptr;
        ListNode *e = merge(q, end);
        ListNode *res = sort(h, e);
        return res;
}


ListNode* sortList(ListNode* head) {
        ListNode *mid = head;
        ListNode *end = head;
        while(end && end->next)
        {
            if(!end->next->next)
            {
                end = end->next;
                break;
            }
	    mid = mid->next;
            end = end->next->next;
        }
        ListNode *q = mid->next;
	mid->next = nullptr;
        ListNode *h = merge(head, mid);
        end->next = nullptr;
        ListNode *e = merge(q, end);
        ListNode *res = sort(h, e);
        return res;
}

TreeNode *create(vector<int> a)
{
	int n = a.size();
	vector<TreeNode *> s;
	for(int i=0; i<n; i++)
	{
		if(a[i]!=INT32_MAX)
		{
			s.push_back(new TreeNode(a[i]));
		}
		else
		{
			s.push_back(nullptr);
		}
	}
	for(int i=0; i<n; i++)
	{
		if(!s[i]) continue;
		if(i*2+1<n)
		{
			if(s[i*2+1])
				s[i]->left = s[i*2+1];
			else s[i]->left = nullptr;
		}
		if(i*2+2<n)
		{
			if(s[i*2+2])
				s[i]->right = s[i*2+2];
			else s[i]->right = nullptr;
		}
	}
	return s[0];

}

int show(TreeNode *root, int sum)
{
	if(!root) return 0;
	int count = root->val==sum? 1: 0;
	count += show(root->left, sum-root->val);
	count += show(root->right, sum-root->val);
	return count;
}

int pathSum(TreeNode* root, int targetSum) {
	return root? show(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum):0;
}



static vector<TreeNode *> res;
static unordered_set<int> hashMy;

void delNode(TreeNode *root)
{
	if(!root) return;
	if(hashMy.count(root->val)) 
	{
		if(root->left)
		{ 
			if(!hashMy.count(root->left->val)) 
			{
				res.push_back(root->left);delNode(root->left);
			}
			else 
			{
				delNode(root->left);
				root->left = nullptr;
			} 
		}
		if(root->right)
		{
			
			if(hashMy.count(root->left->val))
			{
				res.push_back(root->right);delNode(root->right);
			} 
			else 
			{
				delNode(root->right);
				root->right = nullptr;
			}
		}
	}
	else
	{
		if(root->left)
		{
			delNode(root->left);
			if(hashMy.count(root->left->val)) root->left = nullptr;
		}
		if(root->right)
		{
			delNode(root->right);
			if(hashMy.count(root->right->val)) root->right = nullptr;
		}
	}
}


vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
	if(!root) return {};
	for(int i=0; i<to_delete.size(); i++)
		hashMy.emplace(to_delete[i]);
	if(hashMy.count(root->val)) 
	{
		if(root->left)
		{ 
			if(!hashMy.count(root->left->val)) 
			{
				res.push_back(root->left);delNode(root->left);
			}
			else 
			{
				delNode(root->left);
				root->left = nullptr;
			} 
		}
		if(root->right)
		{
			
			if(hashMy.count(root->left->val))
			{
				res.push_back(root->right);delNode(root->right);
			} 
			else 
			{
				delNode(root->right);
				root->right = nullptr;
			}
		}
	}
	else
	{
		res.push_back(root);
		if(root->left)
		{
			delNode(root->left);
			if(hashMy.count(root->left->val)) root->left = nullptr;
		}
		if(root->right)
		{
			delNode(root->right);
			if(hashMy.count(root->right->val)) root->right = nullptr;
		}
	}
	return res;
}
    

TreeNode* createTree(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int ol, int rr)
{
	if(pl>pr) return nullptr;
	if(pl==pr)
	{
		TreeNode *root = new TreeNode(preorder[pl]);
		return root;
	}
	int mid;
	for(int i=ol; i<=rr; i++)
	{
		if(preorder[pl]==inorder[i])
		{
			mid = i;
			break;
		}
	}
	TreeNode *root = new TreeNode(preorder[pl]);
	root->left = createTree(preorder, pl+1, mid, inorder, ol, mid-1);
	root->right = createTree(preorder, mid+1, pr, inorder, mid+1, rr);
	return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	int n = inorder.size();
	int mid;
	for(int i=0; i<n; i++)
	{
		if(inorder[i]==preorder[0]) 
		{
			mid = i;
			break;
		}
	}
	TreeNode *root = new TreeNode(inorder[mid]);
	root->left = createTree(preorder, 1, mid, inorder, 0, mid-1);
	root->right = createTree(preorder, mid+1, n-1, inorder, mid+1, n-1); 
	return root;
}

int main()
{
	// ListNode *p = new ListNode(-1);
	// p->next = new ListNode(5);
	// p->next->next = new ListNode(3);
	// p->next->next->next = new ListNode(4);
	// p->next->next->next->next = new ListNode(0);

	// sortList(p);

	unordered_map<int, int> hash;
	hash.emplace(2, 0);
	int a = 0;
	if(hash.count(2))  a = 1;

	system("pause");
	return 0;
}
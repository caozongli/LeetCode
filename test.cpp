#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
#include <numeric>
#include <stack>

#include <set>
#include <string.h>

template<typename T>
T c(T& a)
{
    cout << a << endl;
    return a;
}

vector<int> partitionLabels(string S) {
    vector<vector<int>> position;
    position.resize(26);
    for(int i=0; i<position.size(); i++)
    {
        position[i].resize(3);
        position[i][0] = -1;
        position[i][1] = -1;
        position[i][2] = 0;
    }
    for(int i=0; i<S.size(); i++)
    {
        position[int(S[i])-97][2] += 1;
        if(position[int(S[i])-97][0]==-1)
        {
            position[int(S[i])-97][0] = i;
            position[int(S[i])-97][1] = i;
        }
        else if(i>position[int(S[i]-97)][1])
        {
            position[int(S[i])-97][1] = i;
        }
    }
    for(int i=0; i<26; i++)
    {
        if(position[25-i][0]==-1) position.erase(position.begin()+25-i);
    }
    std::sort(position.begin(), position.end(), [](vector<int> a, vector<int>b){ return a[0] < b[0];});
    vector<int> result;
    for(int i=0; i<position.size(); i++)
    {
        int p = 0;
        int min = position[i][0];
        int max = position[i][1];
        for(int j=i+1; j<position.size(); j++)
        {
            if(position[j][0]<max)
            {
                i++;
                max = position[j][1] > max? position[j][1]:max;
            }
            else
            {
                result.push_back(max-min+1);
                break;
            }
        }
    }
    return result;

}

int maxProfit(vector<int>& prices) {
    int money = 0;
    int in_ = 0;
    int out = 0;
    if(prices.empty()) return 0;
    for(int i=0; i<prices.size(); i++)
    {
        if(i==prices.size()-1)
        {
            money += prices[i]-in_;
        }
        else
        {
            if(prices[i+1]<prices[i] && prices[i]>in_)
            {
                money += prices[i];
                in_ = prices[i+1];
            }
        }
    }
    return money;
}
    

string largestNumber(vector<int>& nums)
{
    vector<vector<string>> v(10);
    cout << v.size() << endl;
    
    for(auto iter=nums.begin(); iter!=nums.end(); ++iter)
    {
        string s = to_string(*iter);
        v[int(s[0]-'0')].push_back(s);

    }
    string result = "";
    for(int i=0; i<v.size(); i++)
    {
        sort(v[9-i].begin(), v[9-i].end(), [](string a, string b){return a>b;});
        for(int it=0; it<v[9-i].size(); ++it)
        {
            result = result + v[9-i][it];
        }
    }
    
    return result;
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int min(TreeNode*root, int val)
{
    if(!root) return INT_MAX;
    TreeNode *child = root;
    while(root->left)
    {
        child = root;
        root = root->left;
    }
    if(root->val == val) root = child;
    return root->val;
}

int max(TreeNode* root, int val)
{
    if(!root) return INT_MIN;
    TreeNode* child = root;
    while(root->right)
    {
        child = root;
        root = root->right;
    }
    if(root->val == val) root = child;
    return root->val;
}


int minDiffInBST(TreeNode* root) {
    if(!root) return INT_MAX;
    int val = root->val;
    if(!root->right&&!root->left) return INT_MAX; 
    int inm = min(root->right, val);
    int axm = max(root->left, val);
    int m = (val-axm)>(inm-val) ? inm-val:val-axm;
    int m2 = minDiffInBST(root->left);
    int m3 = minDiffInBST(root->right);

    int mn = (m < m2) ? m : m2;
    mn = (mn < m3) ? mn : m3;

    return mn;
}

void insert(TreeNode *root, int val)
{
    TreeNode *p = new TreeNode(val, NULL, NULL);
    while(root)
    {
        if(val>root->val)
        {
            if(root->right)
                root = root->right;
            else
            {
                root->right = p;
                break;
            }
        }
        else
        {
            if(root->left)
                root = root->left;
            else
            {
                root->left = p;
                break;
            }
        }
        
    }
}

class Trie {
public:
    struct Node{
        bool isword;
        Node* childs[26] = {nullptr};
        Node():isword(false){}
        ~Node()
        {
            for(auto& c: childs)
                delete c;
        }
    }* root;


    /** Initialize your data structure here. */
    Trie() {
        root = new Node();
    }
    ~Trie()
    {
        delete root;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = root;
        for(auto& c:word)
        {
            int i = c - 'a';
            if(!p->childs[i])
            {
                p->childs[i] = new Node();
            }
            p = p->childs[i];
        }
        p->isword = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node *p = root;
        for(auto& c: word)
        {
            int i = c - 'a';
            if(!p->childs[i]) return false;
            p = p->childs[i];
        }
        return p->isword;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node *p = root;
        for(auto& c: prefix)
        {
            int i = c - 'a';
            if(!p->childs[i]) return false;
            p = p->childs[i];
        }
        return true;
    }
    
};


bool isScramble(string s1, string s2)
{
    static unordered_map<string, bool> m;
    if(s1.length()!=s2.length()) return false;
    string s = s1 + ":" + s2;
    if(m.find(s)!=m.end()) return m.find(s)->second;
    if(s1==s2)
    {
        m.emplace(s, true);
        return true;
    }

    int n = s1.length();
    for(int i=1; i<n; i++)
    {
        string s3 = s1.substr(0, i), s4 = s1.substr(i, n);
        string s5 = s2.substr(0, i), s6 = s2.substr(i, n);
        string s7 = s2.substr(0, n-i), s8 = s2.substr(n-i, n);
        bool res1 = isScramble(s3, s5) && isScramble(s4, s6);
        bool res2 = isScramble(s3, s8) && isScramble(s4, s7);
        if(res1||res2)
        {
            m.emplace(s, true);
            return true;
        }
    }
    m.emplace(s, false);
    return false;

}

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    multiset<long long> m;
    int n = nums.size();
    // int k = k+1;
    int min = k>n? n:k;
    for(int i=0; i<min; i++)
    {
        auto iter1 = m.lower_bound(long(nums[i]) - long(t));
        auto iter2 = m.upper_bound(long(nums[i]) - long(t));
        for(auto p=iter1; p!=iter2; p++)
        {
            if(long(nums[i])+long(t)>=*p) return true;
        }
        auto iter3 = m.lower_bound(long(nums[i]));
        
        
        m.insert(long(nums[i]));
    }
    for(int i=min; i<n; i++)
    {
        auto iter1 = m.lower_bound(long(nums[i]) - long(t));
        auto iter2 = m.upper_bound(long(nums[i]) - long(t));
        for(auto p=iter1; p!=iter2; p++)
        {
            if(long(nums[i])+long(t)>=*p) return true;
        }
        m.erase(long(nums[i-k]));
        m.insert(long(nums[i]));
    }

    return false;
}

bool checkPossibility(vector<int>& nums) {
    int n = nums.size();
    if(n<3) return true;
    int flag = 0;
    for(int i=0; i<n-1; i++)
    {
        if(nums[i]>nums[i+1])
        {
            flag++;
            if(flag>1) return false;
            if(i==0)
            {
                nums[0] = nums[0] > nums[1]? nums[1]:nums[0];
                nums[1] = nums[0];
            }
            else
                nums[i+1] = nums[i];
        }  
    }
    return true;
}
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m-1;
    int j = n-1;
    int p = m + n - 1;
    while(i!=-1 || j!=-1)
    {
        if(i!=-1&&j!=-1)
        {
            if(nums1[i] > nums2[j]) 
            {
                nums1[p--] = nums1[i];
                i--;
            }
            else 
            {
                nums1[p--] = nums2[j];
                j--;
            }
        }
        else
        {
            if(i==-1)
            {
                nums1[p--] = nums2[j--];
            }
            else
            {
                nums1[p--] = nums1[i--];
            }
        }

    }
}

string minWindow(string s, string t) {
    vector<int> chars(128, 0);
    vector<int> flag(128, false);
    for(int i=0; i<t.size(); i++)
    {
        flag[t[i]] = true;
        ++chars[t[i]];
    }
    int cnt=0, l=0, min_l=0, min_size=s.size()+1;
    for(int i=0; i<s.size(); i++)
    {
        if(flag[s[i]])
        {
            if(--chars[s[i]]>=0)
            {
                cnt++;
            }
            while(cnt==t.size())
            {
                if(i-l+1<min_size)
                {
                    min_l = l;
                    min_size = i - l + 1;
                }
                if(flag[s[l]] && ++chars[s[l]]>0)
                {
                    --cnt;
                }
                ++l;
            }
        }
    }
    return min_size > s.size() ? "": s.substr(min_l, min_size);
}

bool pipei(string s1, string s2)
{
    int n = s2.size();
    int i = 0;
    string s = s1;
    while(i<n)
    {
        int index = s.find(s2[i]);
        if(-1 == index) return false;
        if(index==s.size()-1)
        {
            if(i==n-1) return true;
            return false;
        }
        s = s.substr(index+1, s.size()-index);
        i++;
    }
    return true;
}

int searchRangeIndexL(vector<int> nums, int target, int a, int b)
{
    if(a>b) return INT_MAX;
    int l = a;
    int r = b;
    int mid = (l+r)/2;
    int mid2 = INT_MAX;
    int flag = 0;
    while(l<=r)
    {
        mid = (l+r)/2;
        if(nums[mid]==target)
        {
            flag = 1;
            break;
        }
        else if(nums[mid]<target) l = mid + 1;
        else r = mid - 1;
    }
    if(flag==0) return INT_MAX;

    mid2 = searchRangeIndexL(nums, target, l, mid-1);
    if(mid2!=INT_MAX) return mid2;
    return mid;
}

int searchRangeIndexR(vector<int> nums, int target, int a, int b)
{
    if(a>b) return INT_MIN;
    int l = a;
    int r = b;
    int mid = (l+r)/2;
    int mid2 = INT_MIN;
    int flag = 0;
    while(l<=r)
    {
        mid = (l+r) / 2;
        if(nums[mid]==target)
        {
            flag = 1;
            break;
        }
        else if(nums[mid]<target) l = mid + 1;
        else r = mid - 1;
    }
    if(flag==0) return INT_MIN;

    mid2 = searchRangeIndexR(nums, target, mid+1, r);
    if(mid2!=INT_MIN) return mid2;
    return mid;
}


vector<int> searchRange(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size()-1;
    int mid = (l+r)/2;
    vector<int> result = {-1, -1};
    int flag = 0;
    while(l<r)
    {
        mid = (l+r)/2;
        if(nums[mid]==target)  
        {
            int a = searchRangeIndexL(nums, target, l, mid-1);
            result[0] = a<mid? a: mid;
            int b = searchRangeIndexR(nums, target, mid+1, r);
            result[1] = b>mid? b: mid;
            break;
        }
        else if(nums[mid]<target) l = mid + 1;
        else r = mid - 1;
    }
    return result;
}

bool search_br(int l, int r, vector<int> nums, int target)
{
    int a = l;
    int b = r;
    while(a<=b)
    {
        int mid=(a+b)/2;
        if(nums[mid]==target) return true;
        else if(nums[mid]<target) a = mid+1;
        else b = mid-1;
    }
    return false;
}

bool search(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size()-1;
    int mid = (l+r)/2;

    while(!(nums[mid]<nums[mid-1]&&nums[mid]<=nums[mid+1]))
    {
        if(nums[mid]==nums[r]) break;
        else if(nums[mid]<nums[r]) r = mid-1;
        else l = mid+1;
        mid = (l+r)/2;
    }
    if(target==nums[mid]) return true;
    else if(target>nums[nums.size()-1]) return search_br(0, mid-1, nums, target);
    else return search_br(mid+1, nums.size()-1, nums, target);
}
 int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size()-1;
        int n = r;
        int mid = (l+r)/2;
        if(n==0) return nums[0];
        while(l<=r)
        {
            mid = (l+r)/2;
            if(mid==n)
            {
                if(nums[mid]<nums[mid-1]) return nums[mid];
                else r = mid - 1;
            }
            else if(mid==0)
            {
                if(nums[mid]<nums[n]) return nums[mid];
                else l = mid + 1;
            }
            else
            {
                if(nums[mid]<nums[mid-1])
                {
                    break;
                }
                if(nums[mid]==nums[n])
                {
                    if(nums[mid]<=nums[l])
                    {
                        l++;
                    }
                    else
                    {
                        r--;
                    }
                }
                else if(nums[mid]>nums[n])
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }

            }
        }
        return nums[mid];
    }

     int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return nums[0];
        int l = 0;
        int r = n - 1;
        int mid = (l+r)/2;
        while(l<=r)
        {
            mid = (l+r)/2;
            if(0==mid&&nums[mid]!=nums[mid+1]) return nums[mid];
            if(n-1==mid&&nums[mid]!=nums[mid-1]) return nums[mid];
            if(nums[mid]!=nums[mid+1]&&nums[mid]!=nums[mid-1]) return nums[mid];
            else
            {
                if(nums[mid]==nums[mid+1])
                {
                    if(!(mid%2)) l = mid + 2;
                    else r = mid - 1;
                }
                else if(nums[mid]==nums[mid-1])
                {
                    if(!(mid%2)) r = mid-2;
                    else l = mid + 1;
                }
            }
        }
        return nums[mid];
    }

 int getkeyValue(vector<int>& nums1, vector<int>& nums2, int k)
    {
        int len1 = nums1.size();
        int len2 = nums2.size();
    
        int index1 = 0, index2 = 0;
        while(true)
        {
            int p = k/2;
            if(index1==len1) return nums2[index2+k-1];
            if(index2==len2) return nums1[index1+k-1];
            if(k==1) return min(nums1[index1], nums2[index2]);
            
            int a = min(len1, index1+p);
            int b = min(len2, index2+p);
            if(nums1[a-1]<=nums2[b-1]) 
            {
                k -= (a-index1);
                index1 = a;
            }
            else
            {
                k -= (b-index2);
                index2 = b;
            }
        }
    }


    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        int k = (len1+len2)/2;
        if((len1+len2)%2) return getkeyValue(nums1, nums2, k);
        else return (getkeyValue(nums1, nums2, k) + getkeyValue(nums1, nums2, k+1))/2.0;
    }

void quick_sort(vector<int> &nums, int l, int r)
{
    if(l>=r-1) return;
    int key = nums[l];
    int first = l;
    int right = r-1;

    while(first<right)
    {
        while(first<right&&nums[right]>=key)
        {
            right--;
        }
        nums[first]=nums[right];
        while(first<right&&nums[first]<=key)
        {
            first++;
        }
        nums[right] = nums[first];
    }
    nums[first] == key;
    quick_sort(nums, l, first);
    quick_sort(nums, first+1, r);

}

string frequencySort(string s) {
    int max_count = 0;
    unordered_map<char, int> counts;

    for(int i=0; i<s.size(); i++)
    {
        max_count = max(max_count, ++counts[s[i]]);
    }



    vector<vector<char>> results(max_count+1);
    for(int i=0; i<26; i++)
    {
        results[counts[i]].push_back(char(int('a')+i));
    }

    string s1="";
    for(int i=results.size()-1; i>0; i--)
    {
        if(0==results[i].size()) continue;
        for(int j=0; j<results[i].size(); j++)
        {
            for(int m=0; m<i; m++)
            {
                s1.push_back(results[i][j]);
            }
        }
    }
    return s1;
}

vector<int> direction{-1, 0, 1, 0, -1};
vector<int> bool_of_sea(vector<vector<int>> &heights,int r, int c)
{
    vector<int> flag{0, 0};
    for(int i=0; i<4; i++)
    {
        int x = r + direction[i];
        int y = c + direction[i+1];
        if(x>=0 && y>=0 && x<heights.size() && y<heights[0].size())
        {
            if(heights[x][y]>heights[r][c]) continue;
            if( 0==x || y==0) flag[0] = 1;
            if( heights.size()-1==x || heights[0].size()-1==y ) flag[1] = 1;
            vector<int> flag2 = bool_of_sea(heights, x, y);
            for(int j=0; j<2; j++)
            {
                flag[j] = flag2[j]>flag[j] ? flag2[j] : flag[j];
            }

        }
    }
    return flag;
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    vector<vector<int>> result;
    vector<int> p{0, 0};
    for(int i=0; i<heights.size(); i++)
    {
        for(int j=0; j<heights[0].size(); j++)
        {
            
            p = bool_of_sea(heights, i, j);
            if(1==p[0]&&1==p[1])
            {
                result.push_back(vector<int>{i, j});
            } 
        }
    }
    return result;
}

void con(vector<int>& nums, int depth, int k, vector<bool> used, vector<vector<int>> &ans, vector<int> path)
{
    if(depth==k)
    {
        ans.push_back(path);
        return;  
    }

    for(int i=0; i<nums.size(); i++)
    {
        if(!used[i])
        {
            vector<bool> newused = used;
            newused[i] = true;
            vector<int> newpath = path;
            newpath.push_back(nums[i]);
            con(nums, depth+1, k, newused, ans, newpath);
            used[i] = false;
        }
    }

}

vector<vector<int>> combine(int n, int k) {
    vector<int> nums;
    for(int i=0; i<n; i++)
    {
        nums.push_back(i+1);
    }
    vector<vector<int>> ans;
    vector<bool> used(n, false);
    vector<int> path;
    con(nums, 0, k, used, ans, path);
    return ans;
}


//  vector<int> direction{-1, 0, 1, 0, -1};
bool serch_word(vector<vector<char>> & board, string word, vector<vector<bool>> used, int level, int r, int c)
{
    if(level==word.size())
    {
        return true;
    }
    for(int i=0; i<4; i++)
    {
        int x = r + direction[i];
        int y = c + direction[i+1];
        if(x>=0 && y>=0 && x<board.size() && y<board[0].size())
        {
            vector<vector<bool>> newused = used;
            if(board[x][y]==word[level])
            {
                if(!newused[x][y])
                {
                    newused[x][y] = true;
                    if(serch_word(board, word, newused, level+1, x, y))
                        return true;
                }
            }
        }
    }
    return false;
}




bool exist(vector<vector<char>>& board, string word) {
    if(board.size()<1 || board[0].size()<1) return false;
    vector<vector<bool>> used(board.size(), vector<bool>(board[0].size(), false));

    for(int i=0; i<board.size(); i++)
    {
        for(int j=0; j<board[i].size(); j++)
        {
            if(board[i][j]==word[0])
            {
                vector<vector<bool>> newused = used;
                newused[i][j] = true;
                if(serch_word(board, word, newused, 1, i, j))
                    return true;
            }
            
        }
    }
    return false;
}

void dfs(int n, int level, vector<string> ans, vector<vector<bool>> used, vector<vector<string>> &res)
{
    if(level==n)
    {
        res.push_back(ans);
        return;
    }

    for(int j=0; j<n; j++)
    {
        if(!used[level][j])
        {
            int i = level;
            vector<vector<bool>> newused = used;
            for(int m=0; m<n; m++)
            {
                for(int k=0; k<n; k++)
                {
                    if(m==i || k==j || (m-i)==(k-j) || (m-i)==(j-k))
                    {
                        newused[m][k] = true;
                    }
                }
            } 
            string r = "";
            for(int p=0; p<n; p++)
            {
                if(p==j) r += 'Q';
                    else r += '.';
            }
            vector<string> newans=ans;
            newans.push_back(r);

            dfs(n, level+1, newans, newused, res);

        }
        
    }

}

vector<vector<string>> solveNQueens(int n) {

    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<string> ans;
    vector<vector<string>> res;
    for(int j=0; j<n; j++)
    {
        if(!used[0][j])
        {
            int i = 0;
            vector<vector<bool>> newused = used;
            newused[i][j] = true;
            for(int m=0; m<n; m++)
            {
                for(int k=0; k<n; k++)
                {
                    if(m==i || k==j || (m-i)==(k-j) || (m-i)==(j-k))
                    {
                        newused[m][k] = true;
                    }
                }
            } 
            string r = "";
            for(int p=0; p<n; p++)
            {
                if(p==j) r += 'Q';
                    else r += '.';
            }
            vector<string> newans;
            newans.push_back(r);

            dfs(n, 1, newans, newused, res);
        }
    
        
    }
    return res;
}

void clear(queue<vector<int>> & q)
{
    q = queue<vector<int>>();
}

int shortestBridge(vector<vector<int>>& A) {
    int m = A.size();
    int n = A[0].size();
    vector<vector<bool>> used(m, vector<bool>(n, false));

    queue<vector<int>> q;

    for(int i=0; i<m; i++)
    {
        int flag = 0;
        for(int j=0; j<n; j++)
        {
            if(A[i][j]==1)
            {
                if(!used[i][j])
                {
                    used[i][j] = true;
                    q.push(vector<int>{i, j});
                    flag = 1;
                    break;
                }
            }
            
        }
        if(flag) break;
    }
    queue<vector<int>> res;
    while(!q.empty())
    {
        auto fr = q.front();
        q.pop();
        res.push(fr);
        for(int i=0; i<4; i++)
        {
            int x = fr[0] + direction[i];
            int y = fr[1] + direction[i+1];
            if(x>=0 && y>=0 && x<m && y<n && A[x][y]==1)
            {
                if(!used[x][y])
                {
                    used[x][y] = true;
                    q.push(vector<int>{x, y});
                }
            }
        }
        
    }
    int num = 0;
    queue<vector<int>> ans;
    while(1)
    {   
        while(!res.empty())
        {
            auto fr = res.front();
            res.pop();
            for(int i=0; i<4; i++)
            {
                int x = fr[0] + direction[i];
                int y = fr[1] + direction[i+1];
                if(x>=0 && y>=0 && x<m && y<n)
                {
                    if(!used[x][y])
                    {
                        used[x][y] = true;
                        if(A[x][y]==0)
                        {
                            ans.push(vector<int>{x, y});
                        }
                        else
                        {
                            return num;
                        }
                    }
                }
            }
        }
        res = ans;
        clear(ans);
        num += 1;
    }
    

    return 0;
}

void dfs(vector<vector<char>>& board, vector<vector<bool>> &used, int r, int c)
{
    for(int i=0; i<4; i++)
    {
        int x = r + direction[i];
        int y = c + direction[i+1];
        if(x>=0 && y>=0 && x<board.size() && y<board[0].size())
        {
            if(board[x][y]=='O')
            {
                if(!used[x][y])
                {
                    used[x][y] = true;
                    dfs(board, used, x, y);
                }
                
            }
        }
    }

}

void solve(vector<vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();
    queue<vector<int>> q;
    vector<vector<bool>> used(m, vector<bool>(n, false));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==0 || j==0 || i==m-1 || j==n-1 )
            {
                if(board[i][j]=='O') 
                {
                    q.push(vector<int>{i, j});
                    used[i][j] = true;
                }
            }
        }
    }

    while(!q.empty())
    {
        auto p = q.front();
        q.pop();
        dfs(board, used, p[0], p[1]);
    }
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(!used[i][j]) board[i][j] = 'X';
        }
    }

}

void dfs(vector<int> &nums, vector<int> res, int level, vector<vector<int>> &ans, vector<bool> used)
{
    if(level==nums.size())
    {
        // vector<vector<int>>::iterator it = find(ans.begin(), ans.end(), res);
        // if(it==ans.end())
        ans.push_back(res);
        return;
    }
    unordered_set<int> lis;

    for(int i=0; i<nums.size(); i++)
    {
        if(!used[i])
        {
            if(lis.find(nums[i])!=lis.end()) continue;
            lis.insert(nums[i]);
            vector<bool> newused = used;
            newused[i] = true;
            vector<int> newres = res;
            newres.push_back(nums[i]);
            dfs(nums, newres, level+1, ans, newused);
        }
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    int n = nums.size();
    vector<bool> used(n, false);
    vector<vector<int>> ans;
    vector<int> res;
    unordered_set<int> lis;
    for(int i=0; i<n; i++)
    {
        if(!used[i])
        {
            if(lis.find(nums[i])!=lis.end()) continue;
            lis.insert(nums[i]);
            vector<bool> newused = used;
            newused[i] = true;
            vector<int> newres = res;
            newres.push_back(nums[i]);
            dfs(nums, newres, 1, ans, newused);
        }
    }
    return ans;
}

void dfs(vector<int> &nums, vector<int> res, vector<vector<int>> &ans, int target)
{  
    if(target == accumulate(res.begin(),res.end(),0))
    {
        ans.push_back(res);
        return;
    }
    else if(target < accumulate(res.begin(),res.end(),0))
    {
        return;
    }

    unordered_set<int> lis;

    for(int i=0; i<nums.size(); i++)
    {
        vector<int> newres = res;
        newres.push_back(nums[i]);
        dfs(nums, newres, ans, target);
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<int> nums = candidates;
    int n = nums.size();
    vector<vector<int>> ans;
    vector<int> res;
    for(int i=0; i<n; i++)
    {
        vector<int> newres = res;
        newres.push_back(nums[i]);
        dfs(nums, newres, ans, target);
    }
    return ans;
}

bool dfs(vector<vector<char>> &board, int r, int c)
{
    if(r==board.size())
    {
        return true;
    }
    if(board[r][c]!='.')
    {
        if(c==board[0].size()-1)
        {
            if(dfs(board, r+1, 0))
                return true;
        }
        else
            if(dfs(board, r, c+1))
                return true;
    }
    else
        for(int i=1; i<10; i++)
        {
            int flag = 0;
            int x = (r/3)*3;
            int y = (c/3)*3;
            for(int j=0; j<3; j++)
            {
                if(1==flag) break;
                for(int k=0; k<3; k++)
                {
                    if(board[x+j][y+k]==char(i+'0'))
                    {
                        flag = 1;
                    }
                }
            }
            if(1==flag) continue;
            for(int j=0; j<board.size(); j++)
            {
                if(board[j][c] == char(i+'0'))
                {
                    flag = 1;
                    break;
                }
            }
            if(1==flag) continue;
            for(int j=0; j<board[0].size(); j++)
            {
                if(board[r][j]==char(i+'0'))
                {
                    flag=1;
                    break;
                }
            }
            if(1==flag) continue;
            board[r][c] = i + '0';
            if(c==board[0].size()-1)
            {
                if(dfs(board, r+1, 0))
                    return true;
            }
            else
                if(dfs(board, r, c+1))
                    return true;
            board[r][c] = '.';
        }
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    dfs(board, 0, 0);
}

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if(n==1)
        return {0};
    vector<int> counts(n, 0);
    vector<vector<int>> maxite(n, vector<int>(n, 0));
    for(int i=0; i<edges.size(); i++)
    {
        counts[edges[i][0]]++;
        counts[edges[i][1]]++;
        maxite[edges[i][0]][edges[i][1]] = 1;
        maxite[edges[i][1]][edges[i][0]] = 1;
    }
    
    queue<int> q;
    vector<bool> used(n, false);
    for(int i=0; i<n; i++)
    {
        if(counts[i]==1)
        {
            q.push(i);
            used[i] = true;
        }
    }
    vector<int> res;
    while(!q.empty())
    {
        res.clear();
        int qs = q.size();
        
        for(int i=0; i<qs; i++)
        {
            int p = q.front();
            q.pop();
            used[p] = true;
            for(int m=0; m<n; m++)
            {
                if(1==maxite[m][p])
                {
                    if(!used[m])
                    {
                        if(1==(--counts[m]))
                        {
                            used[m] = true;
                            q.push(m);
                            res.push_back(m);
                        }
                    }
                }
            }
        }
    }
    return res; 
}

int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int mi = min(m, n);
    int mmax = 0;
    for(int i=1; i<=mi; i++)
    {
        int flag = 0;
        for(int j=0; j<m-i; j++)
        {
            for(int k=0; k<n-i; k++)
            {
                flag = 0;
                for(int a=j; a<j+i&&a<m; a++)
                {
                    for(int b=k; b<k+i&&b<n; b++)
                    {
                        if(matrix[a][b]=='0') 
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag) break;
                }
                if(!flag) 
                {
                    mmax = i;
                    break;
                }   
            }
            if(!flag) break;
        }
    }
    return mmax*mmax;
}

bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.size();
    unordered_set<string> dict;
    for(int i=0; i<wordDict.size(); i++)
    {
        dict.insert(wordDict[i]);
    }

    int flag = false;
    set<int> q;
    for(int i=1; i<=n; i++)
    {
        string s1 = s.substr(0, i);
        if(dict.find(s1)!=dict.end()) q.insert(i);
    }


    while(!q.empty())
    {
        int m = *q.rbegin();
        q.erase(m);
        if(m==n) return true;
        for(int i=1; i<=n-m; i++)
        {
            string s1 = s.substr(m, i);
            if(dict.find(s1)!=dict.end()) q.insert(m+i);
        }
    }

    return flag;
}

int knapsack(vector<int> weights, vector<int> values, int N, int W)
{
    vector<vector<int>> dp(N+1, vector<int>(W+1, 0));
    for(int i=1; i<=N; i++)
    {
        int w = weights[i-1], v = values[i-1];
        for(int j=1; j<=W; j++)
        {
            if(j>=w)
            {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-w]+v);
            }
            else
            {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[N][W];
}

int knapsackSaveRoom(vector<int> weights, vector<int> values, int N, int W)
{
    vector<int> dp(W+1, 0);
    for(int i=0; i<N; i++)
    {
        int w = weights[i], v = values[i];
        for(int j=W; j>=w; j--)
        {
            dp[j] = max(dp[j-1], dp[j-w]+v);
        }
    }
    return dp[W];
}

bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum%2) return false;
    sum /= 2;
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int>(sum+1, 0));
    for(int i=0; i<=n; i++)
    {
        dp[i][0] = true;
    }

    for(int i=1; i<=n; i++)
    {
        int w = nums[i-1];
        for(int j=1; j<=sum; j++)
        {
            if(j>=w) dp[i][j] = dp[i-1][j] || dp[i-1][j-w];
        }
    }
    return dp[n][sum];
}

bool isMatch(string s, string p) {
    int length1 = s.length();
    int length2 = p.length();
    if((!length1) || (!length2)) return true;
    if(!length2) return false;
    vector<vector<int>> dp(length1+1, vector<int>(length2+1, 0));
    dp[0][0] = 1;
    for(int i=0; i<=length1; i++)
    {
        for(int j=1; j<=length2; j++)
        {
            if(i!=0)
            {
                if(p[j-1]=='.' || p[j-1]==s[i-1])
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else if(p[j-1]=='*')
                {
                    if(p[j-2]!=s[i-1])
                    {
                        if(p[j-2]=='.')
                        {
                            dp[i][j] = dp[i-1][j-2];
                        }                     
                    }
                    else
                    {
                        dp[i][j] = dp[i][j-1] || dp[i][j-2] || dp[i-1][j];
                    }
                }
            }
            else
            {
                if(p[j-1]=='*'||p[j-1]=='.') dp[i][j] = 1;
            }
            
        }   
    }
    return dp[length1][length2];
}

int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    if(n<1) return 0;
    int pre = 0;
    int m = nums[0];
    for(auto &p: nums)
    {
        pre = max(pre+p, p);
        m = max(m, pre);
    }

    return m;
}

int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n+1, 1);
    vector<int> db(n+1, 0); //0代表减，1代表加, 2代表即可加又可减
    db[1] = 2;
    for(int i=2; i<=n; i++)
    {
        int t = 1;
        int f = 1;
        for(int j=i-1; j>=1; j--)
        {
            if(t==1)
            {
                if(nums[i-1]>nums[j-1])
                {
                    if(db[j]==1 || db[j]==2)
                    {
                        t = dp[j] + 1;
                    }
                }
            }
            
            if(f==1)
            {
                if(nums[i-1]<nums[j-1])
                {
                    if(db[j]==0 || db[j]==2)
                    {
                        f = dp[j] + 1;
                    }
                }
            }
            if( f>1 && t>1 ) break;
        }
        if(t>f)
        {
            dp[i] = t;
            db[i] = 0;
        }
        else if(t<f)
        {
            dp[i] = f;
            db[i] = 1;
        }
        else
        {
            dp[i] = t;
            db[i] = 2;
        }
    }
    return dp[n];
}


int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    if(n<2) return 0;
    vector<int> sell(n+1, 0);
    vector<int> buy(n+1, 0);
    buy[0] = 0;
    buy[1] = -prices[0];
    for(int i=2; i<=n; i++)
    {
        for(int j=2; j<=i; j++)
        {
            buy[j] = max(buy[j-1], sell[j-1] - prices[i-1]);
            sell[j] = max(sell[j-1], buy[j-1] + prices[i-1]-2);
        }
    }
    return sell[n];
}

int maxCoins(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    if(nums.size() == 1)
    {
        return nums[0];
    }

    vector<int> val = nums;
    val.push_back(1);
    val.insert(val.begin(), 1);
    int n = val.size();

    vector<int> result(n-2, 0);
    for(int i=1; i<n-1; i++)
    {
        vector<int> rr;
        vector<int>::const_iterator first1 = nums.begin();
        vector<int>::const_iterator last1 = nums.begin()+i-1;
        vector<int>::const_iterator first2 = nums.begin()+i;
        vector<int>::const_iterator last2 = nums.end();
        vector<int> f1(first1, last1);
        vector<int> f2(first2, last2);
        result[i-1] = val[i]*val[i-1]*val[i+1] + maxCoins(f1) + maxCoins(f2);
    }
    

    return *max_element(result.begin(), result.end());
}

string convertToTitle(int columnNumber) {
    if(columnNumber<1) return "";
    int left = columnNumber%26;
    int p = columnNumber;
    string res = "";
    int ii = 0;
    while((p/26) >0)
    {
        char c;
        if (left-ii==0) c = 'Z';
        else 
            c = left + 'A' - 1 - ii;
        res.insert(0, 1, c);
        if(left-ii == 0) ii = 1;
        else ii = 0;
        p /= 26;
        left = p%26;
    }
    char c = left + 'A' - 1 - ii;
    if(c >= 'A') res.insert(0, 1, c);

    return res;
}

string addBinary(string a, string b) {
    int plus = 0;
    int n1 = a.length()-1;
    int n2 = b.length()-1;
    string res = "";
    while(n1>-1||n2>-1)
    {
        int s;
        if(n1>-1 && n2>-1) s = int(a[n1]-'0') + int(b[n2]-'0') + plus;
        else if(n1<0) s = int(b[n2]-'0') + plus;
        else if(n2<0) s = int(a[n1]-'0') + plus;
        n1--;
        n2--; 
        if(s>1) 
        {
            plus = 1;
            s = s-2;
        }
        else
        {
            plus = 0;
        }
        char c = char(s +'0');
        res.insert(0, 1, c);
    }
    if (plus!=0) res.insert(0, 1, '1');
    return res;
}


int minMoves2(vector<int>& nums) {
    int m = 0;
    int n = nums.size();
    if(n<2) return 0;
    std::sort(nums.begin(), nums.end());
    for(int i=1; i<n; i++)
    {
        m += abs(nums[i]-nums[0]);
    }
    cout << m;
    for(int i=1; i<n; i++)
    {
        int s = abs(nums[i] - nums[i-1]);
        int p = m + s*(i-1)-s*(n-i);
        m = min(m, p);
    }
    return m;
}

int maxProduct(vector<string>& words) {
    vector<uint32_t> t_word;
    for(auto &s: words)
    {
        int n = s.size();
        uint32_t p = 0;
        for(int j=0; j<n; j++)
            p += (1<<int(s[j]-'a'));
        t_word.push_back(p);
    }
    int res = 0;
    for(int i=0; i<words.size(); i++)
    {
        uint32_t p = t_word[i];
        for(int j=i+1; j<words.size(); j++)
        {
            uint32_t p1 = t_word[j];
            if(p1&p) continue;
            else
            {
                int m = words[i].size() * words[j].size();
                res = max(res, m);
            }
        }
    }
    return res;
}


int missingNumber(vector<int>& nums) {
    int res = 0;
    for(auto &p: nums)
    {
        res |= (1<<p);
    }
    int n = 0;
    while(res)
    {
        if(!(res&1)) return n;
        res >>= 1;
    }
    return 0;
}
int findComplement(int num) {
    int p = 0;
    while(num>0)
    {
        p <<= 1;
        p |= ((num&1)^1);
        num >>= 1;
    }
    return p;
}


vector<int> findDisappearedNumbers(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int flag = 0;
    vector<int> res;
    for(auto& n: nums)
    {
        if(n==flag || n==++flag) continue;
        else
        {
            flag++;
            while(flag!=n)
            {
                res.push_back(flag++);
            }
        }
    }
    if(res.empty()) res.push_back(flag);
    return res; 
}

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int conta;
    for(int i=0; i<n/2; i++)
    {
        for(int j=i; j<n-i-1; j++)
        {
            conta = matrix[j][n-1-i];
            matrix[j][n-i-1] = matrix[i][j];
            swap(conta, matrix[n-1-i][n-j-1]);
            swap(conta, matrix[n-j-1][i]);
            matrix[i][j] = conta;
        }
        
    }
}


bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.size()<1) return false;
    int m = 0;
    int n = matrix[0].size()-1;
    while(m<matrix.size()&&n>=0)
    {
        if(matrix[m][n]==target) return true;
        else if(matrix[m][n]>target) m++;
        else n--;
    }
    return false;   
}




int maxChunksToSorted(vector<int>& arr) {
    int n = arr.size();
    if(n<1) return 0;
    vector<vector<int>> res(1, vector<int>{1, arr[0], arr[0]});
    for(int i=1; i<n; i++)
    {
        vector<int> signal = res.back();
        if(arr[i]>=signal[2]) 
        {
            res.push_back(vector<int>{signal[0]+1, arr[i], arr[i]});
        }
        else
        {
            int res_len = res.size();
            for(int j=0; j<res_len; j++)
            {
                if(arr[i]>=res[j][2]) continue;
                int m_max = res[res_len-1][2];
                int m_min = (res[j][1], arr[i]);
                res[j][1] = m_min;
                res[j][2] = m_max;
                for(int k=res_len-1; k>j; k--)
                {
                    res.pop_back();
                }
            }
        }
    }
    return res[res.size()-1][0];

}

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    if(n<1) return {};
    vector<int> day;
    day.push_back(0);
    stack<int> res;
    stack<int> days;
    days.push(0);
    res.push(temperatures[n-1]);
    for(int i=n-2; i>=0; i--)
    {
        int num = temperatures[i];
        if(num<res.top()) 
        {
            res.push(num);
            days.push(1);
            day.insert(day.begin(), 1);
        }
        else
        {
            int nn = 1;
            while(!res.empty())
            {
                if(res.top()<num)
                {
                    nn += days.top();
                    res.pop();
                    days.pop();
                }
                else
                {
                    break;
                }
            }
            if(res.empty()) day.insert(day.begin(), 0);
            else day.insert(day.begin(), nn);
            res.push(num);
            days.push(nn);
            
        }
    }
    return day;
}


struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 struct Com{
    bool operator()(ListNode *l1, ListNode *l2)
    {
        return l1->val>l2->val;
    }
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.size()<1) return nullptr;
    priority_queue<ListNode*, vector<ListNode*>, Com> q;
    for(auto &p: lists)
    {
        while(p)
        {
            q.push(p);
            p = p->next;
        }
    }
    if(q.empty()) return nullptr;
    ListNode *head = q.top();
    q.pop();
    ListNode *ptr = head;
    while(!q.empty())
    {
        ptr->next = q.top();
        q.pop();
        ptr = ptr->next;
        ptr->next = nullptr;
    }
    return head;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    if(n<1||n<k) return {};
    vector<int> ans;
    deque<int> dq(nums.begin(), nums.begin()+k);
    int m = *max_element(dq.begin(), dq.end());
    ans.push_back(m);
    int flag;
    for(int i=k; i<n; i++)
    {
        int a = nums[i];
        
        flag = dq.front();
        
        dq.pop_front();
        dq.push_back(a);
        
        if(flag==m)
        {
            m = *max_element(dq.begin(), dq.end());
        }

        ans.push_back(m);
    }
    return ans;
}

int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> hash;
    int m = 0;
    int res = 0;
    for(int i=0; i<nums.size(); i++)
    {
        unordered_map<int, int>::const_iterator it_self = hash.find(nums[i]);
        if(it_self!=hash.end()) continue;
        m = 1;
        unordered_map<int, int>::const_iterator it_left = hash.find(nums[i]-1);        
        if(it_left!=hash.end())
        {
            m += it_left->second;
        }
        unordered_map<int, int>::const_iterator it_right = hash.find(nums[i]+1);
        if(it_right!=hash.end())
        {
            m += it_right->second;
            hash.emplace(nums[i]+1, m);
        }
        if(it_left!=hash.end())
        {
            hash.emplace(nums[i]-1, m);
        }
        res = max(res, m);
        hash.emplace(nums[i], m);
    }
    return res;
}
bool isSon(string s, string p)
{
    int n1 = s.size();
    int n2 = p.size();
    int i = 0;
    int j = 0;
    

    while(i<n1 && j<n2)
    {
        if(s[i]==p[j]) 
        {
            i++;
            j++;
        }
        else
        {
            i++;
        }
    }
    if(i==n1&&j!=n2) return false;
    return true;
}

int maximumRemovals(string s, string p, vector<int>& removable) {
    int n1 = s.size();
    int n2 = p.size();
    int n = removable.size();
    int left = 0;
    int right = n-1;
    
    while(left<=right)
    {
        string ss = s;
        int mid = (left+right)/2;
        for(int i=0; i<=mid; i++)
        {
            ss[removable[i]] = '1';
        }
        bool isson = isSon(ss, p);
        if(!isson) right = mid - 1;
        else left = mid + 1;
    }
    return left;


}

vector<string> findItinerary(vector<vector<string>>& tickets) {
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> plantRoute;
    int n = tickets.size();
    for(int i=0; i<n; i++)
    {
        plantRoute[tickets[i][0]].push(tickets[i][1]);
    }
    vector<string> ans;
    ans.push_back("JFK");
    int i = 0;
    while(!plantRoute.empty())
    {
        ans.push_back(plantRoute[ans[i]].top());
        plantRoute[ans[i]].pop();
        if(plantRoute[ans[i]].empty()) plantRoute.erase(ans[i]);
        i++;
    }

    return ans;
}


struct cmp
{
    bool operator()(vector<int> a1, vector<int> a2)
    {
        return a1[0] > a2[0];
    }   
};
 

vector<int> nextGreaterElements(vector<int>& nums) {
    priority_queue<vector<int>, vector<vector<int>>, cmp> hashmap;
    int n = nums.size();
    vector<int> res(n, 0);
    for(int i=0; i<n; i++)
    {
        int flag = nums[i];
        while((!hashmap.empty())&&(hashmap.top()[0]<flag))
        {
            int j = hashmap.top()[1];
            hashmap.pop();
            res[j] = flag;
        }
        hashmap.emplace(vector<int>{flag, i});
    }
    int a = hashmap.top()[1];
    for(int i=0; i<n; i++)
    {
        if(nums[i]>a) 
        {
            res[n-1] = nums[i];
            break;
        }
    }
    hashmap.pop();
    while(!hashmap.empty())
    {
        res[hashmap.top()[1]] = -1;
        hashmap.pop();
    }
    return res;
}


int findShortestSubArray(vector<int>& nums) {
    unordered_map<int, vector<int>> hashmap;

    int n = nums.size();
    int maxIdx = -1;
    int ii = -1;
    int du = 0;
    for(int i=0; i<n; i++)
    {
        if(hashmap.find(nums[i])==hashmap.end())
        {
            hashmap.emplace(nums[i], vector<int>{1, i});
        }
        else
        {
            hashmap[nums[i]][0]++;
        }
        if(hashmap[nums[i]][0]>=du)
        {
            du = hashmap[nums[i]][0];
            ii = nums[i];
            maxIdx = i;
        }
    }

    return maxIdx-hashmap[ii][1]+1;

}

struct cmpp{
        bool operator()(int a, int b)
        {
            return a > b;
        }    
    };

int nthSuperUglyNumber(int n, vector<int>& primes) {
    priority_queue<int, vector<int>, cmpp> hashmap;
    hashmap.push(1);
    int count = 0;
    int ans = 0;
    int ans2 = 0;
    while(count<n)
    {
        ans = hashmap.top();
        count += 1;
        hashmap.pop();
        while(ans==ans2)
        {
            ans = hashmap.top();
            hashmap.pop();
        }
        for(int i=0; i<primes.size(); i++)
        {
            if(!hashmap.empty())
                if(ans*primes[i] > hashmap.top()) break;
            hashmap.push(ans*primes[i]);
        }
        ans2 = ans;
    }
    return ans;
}


bool isHuiwen(string s)
{
    int i = 0;
    int j = s.length()-1;
    while(i!=j)
    {
        if(s[i]!=s[j]) return false;
        i++;
        j--;
    }
    return true;
}


int countSubstrings(string s) {
    int n = s.length();
    int res=0;
    for(int i=0; i<n; i++)
    {
        res++;
        for(int j=0; j<i; j++)
        {
            if(s[j]==s[i])
            {
                if(isHuiwen(s.substr(j, i-j+1)))
                {
                    res++;
                }
            }
            
        }
    }
    return res;
}

int Priority(char op)
{
    switch(op)
    {
        case '+': return 0;
        case '-': return 0;
        case '*': return 1;
        case '/': return 1;
        default: return -2;
    }
}

int calculate(string s) {
    stack<int> number;
    stack<char> Operat;
    int n = s.length();
    Operat.push('#');
    int i=0;
    while(i<n)
    {
        while(s[i]==' ') i++;
        if(s[i]>='0'&&s[i]<='9')
        {
            int num = 0;
            while(s[i]>='0'&&s[i]<='9')
            {
                num = num*10 + (s[i]-'0');
                i++;
            }
            number.push(num);
        }
        if(s[i]=='+')
        {
            if(Priority(Operat.top())<Priority('+'))
                Operat.push('+');
            else
            {
                while(Priority(Operat.top())>Priority('+'))
                {
                    int op1 = number.top();
                    number.pop();
                    int op2 = number.top();
                    number.pop();
                    if(Operat.top()=='+')
                        number.push(op1+op2);
                    else if(Operat.top()=='-')
                        number.push(op2-op1);
                    else if(Operat.top()=='*')
                        number.push(op2*op1);
                    else 
                        number.push(op2/op1);
                    Operat.pop();
                }  
            }
            i++;
        }
        else if(s[i]=='-')
        {
            if(Priority(Operat.top()) < Priority('-'))
                Operat.push('-');
            else
            {
                while(Priority(Operat.top())>Priority('-'))
                {
                    int op1 = number.top();
                    number.pop();
                    int op2 = number.top();
                    number.pop();
                    if(Operat.top()=='+')
                        number.push(op1+op2);
                    else if(Operat.top()=='-')
                        number.push(op2-op1);
                    else if(Operat.top()=='*')
                        number.push(op2*op1);
                    else 
                        number.push(op2/op1);
                    Operat.pop();
                }  
            }
            i++;
        }
        else if(s[i]=='*')
        {
            if(Priority(Operat.top())<Priority('*'))
                Operat.push('*');
            else
            {
                while(Priority(Operat.top())>Priority('*'))
                {
                    int op1 = number.top();
                    number.pop();
                    int op2 = number.top();
                    number.pop();
                    if(Operat.top()=='+')
                        number.push(op1+op2);
                    else if(Operat.top()=='-')
                        number.push(op2-op1);
                    else if(Operat.top()=='*')
                        number.push(op2*op1);
                    else 
                        number.push(op2/op1);
                    Operat.pop();
                }  
            }
            i++;
        }
        else if(s[i]=='/')
        {
            if(Priority(Operat.top())<Priority('/'))
                Operat.push('/');
            else
            {
                while(Priority(Operat.top())>Priority('/'))
                {
                    int op1 = number.top();
                    number.pop();
                    int op2 = number.top();
                    number.pop();
                    if(Operat.top()=='+')
                        number.push(op1+op2);
                    else if(Operat.top()=='-')
                        number.push(op2-op1);
                    else if(Operat.top()=='*')
                        number.push(op2*op1);
                    else 
                        number.push(op2/op1);
                    Operat.pop();
                }  
            }
            i++;
        }
        else if(s[i]=='(')
        {
            Operat.push('(');
            i++;
        }
        else if(s[i]==')')
        {
            while(Operat.top()!='(')
            {
                int op1 = number.top();
                number.pop();
                int op2 = number.top();
                number.pop();
                if(Operat.top()=='+')
                    number.push(op1+op2);
                else if(Operat.top()=='-')
                    number.push(op2-op1);
                else if(Operat.top()=='*')
                    number.push(op2*op1);
                else 
                    number.push(op2/op1);
                Operat.pop();
            }
            Operat.pop();
            i++;
        }
        
    }
    return number.top();
}
bool myErase(string &s, vector<vector<int>> &dp, int n)
{
    int m = s.length();
    int ind = 0;
    int sta = -1;
    for(int i=0; i<m; i++)
    {
        ind = dp[ind][int(s[i]-'a')];
        if(ind==n) 
        {
            sta = i;
            break;
        }
    }
    
    if(sta==-1) return false;
    s.erase(sta-n+1, n);
    return true;
}

string removeOccurrences(string s, string part) {
    int n = part.length();
    vector<vector<int>> dp(n, vector<int>(26, 0));
    dp[0][int(part[0]-'a')] = 1;
    int x = 0;
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<26; j++)
            dp[i][j] = dp[x][j];
        dp[i][int(part[i]-'a')] = i+1;
        x = dp[x][int(part[i]-'a')];
    }
    
    while(myErase(s, dp, n));
    return s;
    
}

long long maxAlternatingSum(vector<int>& nums) {
    int n = nums.size();
    if(n<1) return 0;
    int ma = nums[0];
    int mi = INT_MAX;
    vector<long long> res; 
    res.push_back(nums[0]);
    int state = 0;
    for(int i=1; i<n; i++)
    {
        if(state==0)
        {
            if(nums[i]>ma)
            {
                ma = nums[i];
                res.back() = ma;
            }
            if(nums[i]<ma)
            {
                ma = mi = nums[i];
                state = 2;
                res.push_back(ma);
            }    
            
        }
        else if(state==1)
        {
            if(nums[i]>ma)
            {
                ma = nums[i];
                res.back() = ma;
            }
            if(nums[i]<ma)
            {
                ma = mi = nums[i];
                state = 2;
                res.push_back(ma);
            }
        }
        else if(state==2)
        {
            if(nums[i]>ma)
            {
                ma = nums[i];
                state = 1;
                res.push_back(ma);
            }
            if(nums[i]<mi)
            {
                res.back() = nums[i];
                mi = ma = nums[i];
            }
        }
        
        
    }
    long long ans = 0;
    for(int i=0; i<res.size(); i++)
    {
        if(i%2)
        {
            if(i!=res.size()-1)
                ans -= res[i];
        } 
        else ans += res[i];
    }
    return ans;

}


vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    int rank = min(m/2, n/2);
    int rowBe;
    int colBe;
    int rowAf;
    int colAf;
    int jAf;    
    vector<vector<int>> res = grid;
    for(int i=0; i<rank; i++)
    {
        int numBlock = (m-2*i)*2 + (n-2*i)*2 - 4;
        int removeStride = k%numBlock;
        for(int j=0; j<numBlock; j++)
        {
            
            if(j<(n-2*i))
            {
                rowBe = i;
                colBe = i + j;
            }
            else if(j>=n-2*i && j<n-2*i+m-2*i-2)
            {
                rowBe = j+1 - (n-2*i) + i;
                colBe = n-i-1;    
            }
            else if(j>=n-2*i+m-2*i-2 && j<(n-2*i)*2+m-2*i-2)
            {
                rowBe = m - i - 1;
                colBe = n - i - 1 - (j+1-(n-2*i)-(m-2*i) + 2)+1; 
            }
            else
            {
                rowBe = m - i - 1 - (j+1 - ((n-2*i)*2 + m-2*i - 2));
                colBe = i;    
            }
            jAf = (j - removeStride + numBlock)%numBlock;
            
            if(jAf<(n-2*i))
            {
                rowAf = i;
                colAf = i + jAf;
            }
            else if(jAf>=n-2*i && jAf<n-2*i+m-2*i-2)
            {
                rowAf = jAf+1 - (n-2*i) + i;
                colAf = n-i-1;    
            }
            else if(jAf>=n-2*i+m-2*i-2 && jAf<(n-2*i)*2+m-2*i-2)
            {
                rowAf = m - i - 1;
                colAf = n - i - 1 - (jAf+1-(n-2*i)-(m-2*i) + 2) + 1; 
            }
            else
            {
                rowAf = m - i - 1 - (jAf+1 - ((n-2*i)*2 + m-2*i - 2));
                colAf = i;    
            }
            res[rowAf][colAf] = grid[rowBe][colBe];
        }
    }
    return res;
}


bool isPalindrome(ListNode* head) {
    if(head==nullptr || head->next==nullptr) return true;
    ListNode *low = head;
    ListNode *fast = head;
    ListNode *head2 = nullptr;
    ListNode *head3 = nullptr;
    while(fast!=nullptr && fast->next!=nullptr)
    {
        ListNode *p = low->next;
        low->next = head2;
        head2 = low;
        low = p;
        fast = fast->next->next;
    }
    head3 = low;
    if(head3->val!=head2->val) head2 = head2->next;
    while(head2&&head3)
    {
        if(head2->val!=head3->val) return false;
        head3 = head3->next;
        head2 = head2->next;
    }

    return  true;
}


int main()
{
    
    // vector<int> a(2, 0);
    // vector<int> b = a;
    // a[0] = 1;
    // combine(4, 2);

    // string word = "AAAAAAAAAAAAAAB";
    // vector<vector<char>> board = {{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'}};

    // bool res = exist(board, word);
    // cout << res << endl;
    // vector<vector<char>> v{{'X','O','X','O','X','O'},{'O','X','O','X','O','X'},{'X','O','X','O','X','O'},{'O','X','O','X','O','X'}};
    // solve(v);
    // string s = "";
    // s+=char(5+'0');
    // s+="->";
    // cout << s << endl;

    // vector<vector<char>> p{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    // maximalSquare(p);
    // string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    
    // vector<string> dict{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};

    // wordBreak(s, dict);
    // set<int> q{0, 3, 5, 4, 9};
    // int m = *q.rbegin();
    // q.erase(m);
    // vector<int> p{1,4,3,6,0,7,8,2,5};
    // vector<ListNode*> lists(2, new ListNode());
    // ListNode* p = new ListNode(-1);
    // lists[0] = p;
    // lists[0]->next = new ListNode(-1);
    // lists[0]->next->next = new ListNode(-1);
    // lists[0]->next->next->next = nullptr;
    // p = new ListNode(-2);
    // lists[1] = p;
    // lists[1]->next = new ListNode(-2);
    // lists[1]->next->next = new ListNode(-1);
    // lists[1]->next->next->next = nullptr;
    // p = new ListNode(2);
    // lists[2] = p;
    // lists[2]->next = new ListNode(6);
    // lists[2]->next->next = nullptr;
    string s = "axxxxyyyyb";

    string s2 = "xy";
    
    // maxCoins(p);
    system("pause");
    return 0;
}

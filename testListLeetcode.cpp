#include <iostream>

using namespace std;
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
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





int main()
{
	ListNode *p = new ListNode(-1);
	p->next = new ListNode(5);
	p->next->next = new ListNode(3);
	p->next->next->next = new ListNode(4);
	p->next->next->next->next = new ListNode(0);

	sortList(p);

	return 0;
}
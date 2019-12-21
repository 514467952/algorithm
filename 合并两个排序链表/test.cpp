#include<iostream>

using namespace std;

struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		if (pHead1 == NULL)
			return pHead2;
		else if (pHead2 == NULL)
			return pHead1;

		ListNode* p1 = pHead1;
		ListNode* p2 = pHead2;
		ListNode* result = NULL;
		ListNode* p3 = result;
		while (p1 != NULL && p2 != NULL)
		{
			if (p1->val <= p2->val)
			{
				if (result == NULL)
					p3 = result = pHead1;
				else
				{
					p3->next = p1;
					p3 = p3->next;
				}
				p1 = p1->next;
			}
			else if (p1->val > p2->val)
			{
				if (result == NULL)
					p3 = result = pHead2;
				else{
					p3->next = p2;
					p3 = p3->next;
				}
				p2 = p2->next;
			}
		}
		if (p1 == NULL)
			p3->next = p2;
		if (p2 == NULL)
			p3->next = p1;
		return result;
	}
};
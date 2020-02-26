
struct ListNode {
    int val;    
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* newHead = new ListNode(-1); //新链表
		ListNode* Cur = newHead;
		int sum = 0; //每一位上面的和
		bool carry = false; //进位标志
		while (l1 != NULL || l2 != NULL)
		{
			sum = 0;
			if (l1 != NULL)
			{
				sum += l1->val;
				l1 = l1->next;
			}
			if (l2 != NULL)
			{
				sum += l2->val;
				l2 = l2->next;
			}
			if (carry)
			{
				sum += 1;
			}
			Cur->next = new ListNode(sum % 10);
			carry = sum >= 10 ? true : false;
			Cur = Cur->next;

		}
		if (carry)
		{
			Cur->next = new ListNode(1);
		}
		//没有头节点，返回头结点的下一个结点
		return newHead->next;
	}
};
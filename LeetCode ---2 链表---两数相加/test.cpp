
struct ListNode {
    int val;    
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* newHead = new ListNode(-1); //������
		ListNode* Cur = newHead;
		int sum = 0; //ÿһλ����ĺ�
		bool carry = false; //��λ��־
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
		//û��ͷ�ڵ㣬����ͷ������һ�����
		return newHead->next;
	}
};
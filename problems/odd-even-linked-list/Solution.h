#include "../../common/common.h"
using namespace linkedList;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) {
            return head;
        }
        int count = 1;
        ListNode* oddHead = head;
        ListNode* oddEnd = head;
        ListNode* evenHead = head->next;
        ListNode* evenEnd = head->next;
        while(head->next) {
            cout << head->val << count << endl;
            if(count % 2 == 1) {
                oddEnd->next = head->next;
                oddEnd = oddEnd->next;
            } else {
                evenEnd->next = head->next;
                evenEnd = evenEnd->next;
            }
            ++count;
            head = head->next;
        }
        oddEnd->next = evenHead;
        return oddHead;
    }
};

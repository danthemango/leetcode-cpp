#include "../../common/common.h"
using namespace linkedList;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* newHead = nullptr;
        ListNode* curr = head;
        while(curr != nullptr) {
            ListNode* tmp = curr->next;
            curr->next = newHead;
            newHead = curr;
            curr = tmp;
        }
        return newHead;
    }
};
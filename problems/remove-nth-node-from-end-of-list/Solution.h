#include "../../common/common.h"
using namespace linkedList;

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head || !head->next) {
            return nullptr;
        }
        ListNode* target = head;
        ListNode* curr = head;
        while(n >= 0) {
            if(!curr) {
                head = head->next;
                return head;
            } else {
                curr = curr->next;
            }
            n--;
        }
        while(curr != nullptr) {
            curr = curr->next;
            target = target->next;
        }
        target->next = target->next->next;
        return head;
    }
};
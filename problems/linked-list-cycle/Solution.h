#include "../../common/common.h"

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head || !head->next) {
            return false;
        }
        ListNode* c1 = head;
        ListNode* c2 = head->next;
        while(true) {
            if(!c1 || !c2 || !c1->next || !c2->next) {
                return false;
            } else if(c1 && c2 && c1 == c2) {
                return true;
            } else {
                c1 = c1->next;
                c2 = c2->next->next;
            }
        }
    }

    bool run(ListNode *head, int pos) {
        ListNode* cycleNode = nullptr;
        ListNode* curr = head;
        while(curr->next != nullptr) {
            if(pos > 0) {
                pos--;
            } else if(pos == 0) {
                cycleNode = curr;
            }
            curr = curr->next;
        }
        ListNode* endPtr = curr;
        endPtr->next = cycleNode;

        return hasCycle(head);
    }
};

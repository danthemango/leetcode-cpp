#include "../../common/common.h"

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

    void appendToEnd(ListNode*& end, ListNode* val) {
        if(end == nullptr) {
            end = val;
        } else {
            end->next = val;
            end = val;
        }
    }

    void applyOverflow(bool& didOverflow, ListNode* node) {
        assert(node != nullptr);
        node->val += (didOverflow ? 1 : 0);
        didOverflow = node->val >= 10;
        node->val %= 10;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        bool didOverflow = false;
        ListNode* head = nullptr;
        ListNode* end = nullptr;

        while(l1 || l2) {
            if(!l1) {
                applyOverflow(didOverflow, l2);
                appendToEnd(end, l2);
                l2 = l2->next;
            } else if(!l2) {
                applyOverflow(didOverflow, l1);
                appendToEnd(end, l1);
                l1 = l1->next;
            } else {
                int result = l1->val + l2->val + (didOverflow ? 1 : 0);
                didOverflow = result >= 10;
                result %= 10;
                appendToEnd(end, new ListNode(result));
                l2 = l2->next;
                l1 = l1->next;
            }
            if(!head) {
                head = end;
            }
        }
        if(didOverflow) {
            appendToEnd(end, new ListNode(1));
        }

        return reverseList(head);
    }
};
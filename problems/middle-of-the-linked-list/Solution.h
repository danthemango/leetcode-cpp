#include "../../common/common.h"
#include "../../common/ListNode.h"

using namespace linkedList;

// https://leetcode.com/problems/middle-of-the-linked-list
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int count = 0;
        if(!head) {
            return head;
        }

        ListNode* tmp = head;
        while(head->next) {
            head = head->next;
            tmp = tmp->next;
            if(head->next) {
                head = head->next;
            }
        }
        return tmp;
    }
};

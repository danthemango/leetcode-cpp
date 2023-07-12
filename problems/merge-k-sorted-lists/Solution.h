#include "../../common/common.h"
using namespace linkedList;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = nullptr;
        ListNode* curr = nullptr;

        while(list1 != nullptr || list2 != nullptr) {
            ListNode* nextVal;
            if(list1 == nullptr) {
                nextVal = list2;
                list2 = list2->next;
            } else if(list2 == nullptr) {
                nextVal = list1;
                list1 = list1->next;
            } else if(list1->val > list2->val) {
                nextVal = list2;
                list2 = list2->next;
            } else {
                nextVal = list1;
                list1 = list1->next;
            }
            if(head == nullptr) {
                head = nextVal;
                curr = head;
            } else {
                curr->next = nextVal;
                curr = curr->next;
            }
        }
        return head;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head = nullptr;
        for(const auto& list : lists) {
            head = mergeTwoLists(head, list);
        }
        return head;
    }
};
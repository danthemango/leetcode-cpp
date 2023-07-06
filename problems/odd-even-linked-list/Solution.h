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
    void addTo(ListNode*& head, ListNode*& other) {
        other->next = head;
        head = head->next;
    }

    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) {
            return head;
        }

        int isOdd = true;
        ListNode* oddHead = head;
        ListNode* oddEnd = head;
        ListNode* evenHead = head->next;
        ListNode* evenEnd = head->next;
        head = head->next->next;
        while(head) {
            if(isOdd) {
                oddEnd->next = head;
                oddEnd = head;
            } else {
                evenEnd->next = head;
                evenEnd = head;
            }
            head = head->next;
            isOdd = !isOdd;
        }

        oddEnd->next = evenHead;
        evenEnd->next = nullptr;

        return oddHead;
    }
};

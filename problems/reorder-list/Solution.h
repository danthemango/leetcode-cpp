#include "../../common/common.h"
#include <stack>

class Solution {
public:
    void reorderList(ListNode* head) {
        /* 
            set size = 0
            create a stack of elements, and a queue of elements
            iterate through the list
            - push onto stack
            - push onto queue
            - increment size
            create newHeadPtr
            create endPtr = newHeadPtr
            set newSize = 0
            while(newSize < size)
            - pop a node from the queue
                - put at end of new list, update endPtr
            - if newSize < size, pop a node from the stack
                - put at end of new list, update endPtr
            return newHeadPtr
        */
        std::stack<ListNode *> nodeStack;
        std::queue<ListNode *> nodeQueue;
        unsigned int oldSize = 0;
        while (head != nullptr) {
            nodeStack.push(head);
            nodeQueue.push(head);
            head = head->next;
            ++oldSize;
        }
        ListNode* newHead = nullptr;
        ListNode* newEnd = nullptr;
        ListNode* cur = nullptr;
        unsigned int newSize = 0;
        while(newSize < oldSize) {
            cur = nodeQueue.front();
            nodeQueue.pop();
            if(newHead == nullptr) {
                newHead = cur;
            } else {
                newEnd->next = cur;
            }
            newEnd = cur;
            ++newSize;
            if(newSize < oldSize) {
                cur = nodeStack.top();
                nodeStack.pop();
                newEnd->next = cur;
                newEnd = cur;
                ++newSize;
            }
        }
        newEnd->next = nullptr;
    }

    ListNode* run(ListNode* head) {
        reorderList(head);
        return head;
    }
};
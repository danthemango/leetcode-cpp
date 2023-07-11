#ifndef TLISTNODE_H
#define TLISTNODE_H
#include "listNode.h"
#include <iostream>

/* testtype tree type handler */
class TListNode {
    public:
    linkedList::ListNode* val;

    TListNode();

    TListNode(linkedList::ListNode* _val);

    linkedList::ListNode*& get();

    bool operator==(linkedList::ListNode*& other);

    bool operator==(TListNode& other);

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TListNode& t);
};

#endif // TLISTNODE_H

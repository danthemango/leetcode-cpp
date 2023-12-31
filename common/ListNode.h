#pragma once
#ifndef LISTNODE_H
#define LISTNODE_H

#include <string>
#include <sstream>

#include "textParse.h"

namespace linkedList {
    using namespace textParse;
    class ListNode
    {
        public:
        int val;
        ListNode *next;
        ListNode();
        ListNode(int x);
        ListNode(int x, ListNode *next);
        // extra
        friend std::ostream& operator<<(std::ostream& os, ListNode& l);
        bool operator==(ListNode& other) const;
        bool operator!=(ListNode& other) const;
    };

    // returns true if a listnode could be created
    // this will assume a list is specified with an array of integers of the format, like: [5,1,5,6,8]
    bool tryParse(const std::string& input, unsigned int& i, ListNode*& out_listNode);

    // deletes the linked listnodes
    void deleteList(ListNode* head);

    // returns a stringified version of this list
    std::string toString(ListNode* head);

    // returns true if the two lists have equal values
    bool isEqual(ListNode* a, ListNode* b);
}

#endif // LISTNODE_H
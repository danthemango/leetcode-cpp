/* vector<ListNode*> */
#ifndef TVECTORLISTNODE_H
#define TVECTORLISTNODE_H
#include <iostream>
#include <vector>
#include "ListNode.h"

/* testcase vector type */
class TVectorListNode {
    public:
    std::vector<linkedList::ListNode*> val;

    TVectorListNode();

    TVectorListNode(std::vector<linkedList::ListNode*> _val);

    std::vector<linkedList::ListNode*>& get();

    bool operator==(const std::vector<linkedList::ListNode*>& other);

    bool operator==(const TVectorListNode& other);

    bool tryParse(const std::string& input);

    friend std::ostream& operator<<(std::ostream& os, TVectorListNode& t);
};

#endif // TVECTORLISTNODE_H

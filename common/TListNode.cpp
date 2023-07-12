#include "TListNode.h"
#include "textParse.h"

/* testtype tree type handler */
TListNode::TListNode() { }

TListNode::TListNode(linkedList::ListNode* _val) : val(_val) { }

linkedList::ListNode*& TListNode::get() {
    return val;
}

bool TListNode::operator==(linkedList::ListNode*& other) {
    return linkedList::isEqual(this->val, other);
}

bool TListNode::operator==(TListNode& other) {
    return linkedList::isEqual(this->val, other.val);
}

bool TListNode::tryParse(const std::string& input) {
    unsigned int i = 0;
    return linkedList::tryParse(input, i, this->val);
}

std::ostream & operator<<(std::ostream& os, TListNode& t) {
    os << linkedList::toString(t.val) << std::endl;
    return os;
}

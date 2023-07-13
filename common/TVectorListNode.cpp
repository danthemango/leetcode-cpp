/* vector<ListNode*> */
#include "TVectorListNode.h"
#include "ListNode.h"
using linkedList::ListNode;

/* testcase vector type */
TVectorListNode::TVectorListNode() { }

TVectorListNode::TVectorListNode(std::vector<linkedList::ListNode*> _val) : val(_val) {}

std::vector<linkedList::ListNode*>& TVectorListNode::get() {
    return val;
}

bool TVectorListNode::operator==(const std::vector<linkedList::ListNode*>& otherLists) {
    for(unsigned int i = 0; i < otherLists.size(); i++) {
        if(i >= this->val.size()) {
            return false;
        }
        auto& thisList = this->val[i];
        auto& otherList = otherLists[i];
        if(*thisList != *otherList) {
            return false;
        }
    }
    return true;
}

bool TVectorListNode::operator==(const TVectorListNode& other) {
    return *this == other.val;
}

bool TVectorListNode::tryParse(const std::string& input) {
    unsigned int i = 0;

    if(!textParse::tryParseNextChar(input, i, '[')) {
        return false;
    }

    bool first = true;
    this->val.clear();
    while(i < input.size()) {
        if(textParse::tryParseNextChar(input, i, ']')) {
            return true;
        }
        if(first) {
            first = false;
        } else if(!textParse::tryParseNextChar(input, i, ',')){
            return false;
        }

        ListNode* head;
        if(!linkedList::tryParse(input, i, head)) {
            return false;
        }
        this->val.push_back(head);
    }
    return false;
}

std::string vectorList2String(std::vector<ListNode*>& array) {
    std::string result;
    result.push_back('[');
    bool first = true;
    for(const auto& list : array) {
        if(!first) {
            result.push_back(',');
        } else {
            first = false;
        }
        result.append(linkedList::toString(list));
    }
    result.push_back(']');
    return result;


}

std::ostream& operator<<(std::ostream& os, TVectorListNode& t) {
    os << vectorList2String(t.val);
    return os;
}
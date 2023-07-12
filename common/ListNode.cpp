#include "ListNode.h"

namespace linkedList {
    ListNode::ListNode(int x, ListNode *next) : val(x), next(next) { }
    ListNode::ListNode() : val(0), next(nullptr) {}
    ListNode::ListNode(int x) : val(x), next(nullptr) {}
    std::ostream& operator<<(std::ostream& os, ListNode& l) {
        ListNode* head = &l;
        os << "[";
        bool first = true;
        while(head != nullptr) {
            if(first) {
                first = false;
            } else {
                os << ",";
            }
            os << head->val;
            head = head->next;
        }
        os << "]";
        return os;
    }

    // returns true if a listnode could be created
    // this will assume a list is specified with an array of integers of the format, like: [5,1,5,6,8]
    bool tryParse(const std::string& input, unsigned int& i, ListNode*& out_listNode) {
        unsigned int resetI = i;
        if(!tryParseNextChar(input, i, '[')) {
            return false;
        }

        out_listNode = nullptr;
        ListNode* curr = nullptr;

        bool first = true;
        while(i < input.size()) {
            if(tryParseNextChar(input, i, ']')) {
                return true;
            }

            if(!first) {
                if(!tryParseNextChar(input, i, ',')) {
                    i = resetI;
                    return false;
                }
            } else {
                first = false;
            }

            int out_val;
            if(!tryParseNextInt(input, i, out_val)) {
                i = resetI;
                return false;
            }
            if(out_listNode == nullptr) {
                out_listNode = new ListNode(out_val);
                curr = out_listNode;
            } else {
                curr->next = new ListNode(out_val);
                curr = curr->next;
            }
        }

        i = resetI;
        return false;
    }

    // deletes the linked listnodes
    void deleteList(ListNode* head) {
        while(head != nullptr) {
            ListNode* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    // returns a stringified version of this list
    std::string toString(ListNode* head) {
        std::string result;
        result.push_back('[');
        bool first = true;
        while(head != nullptr) {
            if(!first) {
                result.push_back(',');
            } else {
                first = false;
            }
            result.append(std::to_string(head->val));
            head = head->next;
        }
        result.push_back(']');
        return result;
    }

    // returns true if the two lists have equal values
    bool isEqual(ListNode* a, ListNode* b) {
        while(a != nullptr && b != nullptr) {
            if (a->val != b->val) {
                return false;
            }
            a = a->next;
            b = b->next;
        }

        return a == b;
    }
}
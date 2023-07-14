#include "TTreeNode.h"

/* testtype tree type handler */
TTreeNode::TTreeNode() { }

TTreeNode::TTreeNode(TreeNode* _val) : val(_val) { }

TreeNode*& TTreeNode::get() {
    return val;
}

bool TTreeNode::operator==(TreeNode*& other) {
    if(this->val == nullptr || other == nullptr) {
        return this->val == other;
    } else {
        return *this->val == *other;
    }
}

bool TTreeNode::operator==(TTreeNode& other) {
    if(this->val == nullptr || other.val == nullptr) {
        return this->val == other.val;
    } else {
        return *this->val == *other.val;
    }
}

bool TTreeNode::tryParse(const std::string& input) {
    unsigned int i = 0;
    return TreeNode::tryParse(input, i, this->val);
}

std::ostream& operator<<(std::ostream& os, TTreeNode& t) {
    if(t.val == nullptr) {
        os << "[]";
        return os;
    } else {
        os << t.val;
        return os;
    }
}

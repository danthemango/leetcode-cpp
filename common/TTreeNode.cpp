#include "TTreeNode.h"

/* testtype tree type handler */
TTreeNode::TTreeNode() { }

TTreeNode::TTreeNode(tree::TreeNode* _val) : val(_val) { }

tree::TreeNode*& TTreeNode::get() {
    return val;
}

bool TTreeNode::operator==(tree::TreeNode*& other) {
    return tree::isEqual(this->val, other);
}

bool TTreeNode::operator==(TTreeNode& other) {
    return tree::isEqual(this->val, other.val);
}

bool TTreeNode::tryParse(const std::string& input) {
    unsigned int i = 0;
    return tree::tryParse(input, i, this->val);
}

std::ostream& operator<<(std::ostream& os, TTreeNode& t) {
    os << tree::tree2string(t.val) << std::endl;
    return os;
}

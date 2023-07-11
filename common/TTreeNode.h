#ifndef TTREENODE_H
#define TTREENODE_H

#include <iostream>
#include "TreeNode.h"

/* testtype tree type handler */
class TTreeNode {
    public:
    tree::TreeNode* val;

    TTreeNode();

    TTreeNode(tree::TreeNode* _val);

    tree::TreeNode*& get();

    bool operator==(tree::TreeNode*& other);

    bool operator==(TTreeNode& other);

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TTreeNode& t);
};

#endif // TTREENODE_H

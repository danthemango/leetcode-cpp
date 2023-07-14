#ifndef TTREENODE_H
#define TTREENODE_H

#include <iostream>
#include "TreeNode.h"

/* testtype tree type handler */
class TTreeNode {
    public:
    TreeNode* val;

    TTreeNode();

    TTreeNode(TreeNode* _val);

    TreeNode*& get();

    bool operator==(TreeNode*& other);

    bool operator==(TTreeNode& other);

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TTreeNode& t);
};

#endif // TTREENODE_H

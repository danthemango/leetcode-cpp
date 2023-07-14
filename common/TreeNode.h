#ifndef TREE_H
#define TREE_H

#include <string>
#include <sstream>
#include <queue>

#include "textParse.h"

// Definition for a binary tree node.
class TreeNode {
    public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode();
    TreeNode(int x);
    TreeNode(int x, TreeNode *left, TreeNode *right);

    friend std::ostream& operator<<(std::ostream& os, TreeNode* tn);
    friend std::ostream& operator<<(std::ostream& os, TreeNode& tn);
    bool operator==(TreeNode& other) const;
    static void deleteTree(TreeNode* root);
    static bool tryParse(const std::string& input, unsigned int& i, TreeNode*& out_root);
};

#endif // TREE_H

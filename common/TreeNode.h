#ifndef TREE_H
#define TREE_H

#include <string>
#include <sstream>
#include <queue>

#include "textParse.h"

namespace tree {
    using namespace textParse;
    /**
     * Definition for a binary tree node.
     */
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode();
        TreeNode(int x);
        TreeNode(int x, TreeNode *left, TreeNode *right);
    };

    // stores a tree value for parsing
    struct TreeVal {
        int val;
        bool isNull;
    };

    std::string val2string(const TreeVal& treeVal);

    // parses tree node value, either int or null
    // returns true if successful
    // updating i to the next char after a successful match
    bool tryParseVal(std::string input, unsigned int& i, TreeVal& out_val);

    // attempts to parse a node list from input string at i
    // with a format similar to: [54,3,null,4]
    // returns true if successful
    // and updating i to the position after a successful match
    bool tryParseValList(std::string input, unsigned int& i, std::vector<TreeVal>& out_list);

    // returns the subtree at index i of the tree node values list
    TreeNode* getNodeAtI(const std::vector<TreeVal>& treeValues, int i);

    bool tryParse(std::string input, unsigned int& i, TreeNode*& out_node);

    // returns true if successfully parsed a tree, updating out_node with the head
    bool tryParse(const std::string input, TreeNode*& out_node);

    // delete all nodes in a tree
    void deleteTree(TreeNode* head);

    TreeNode* string2tree(std::string input);

    int getTreeSize(TreeNode* head);

    std::string tree2string(TreeNode* head);

    // returns true if a equals b
    bool isEqual(TreeNode*& a, TreeNode*& b);
}

#endif // TREE_H

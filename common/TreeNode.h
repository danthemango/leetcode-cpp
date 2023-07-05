#ifndef TREE_H
#define TREE_H

#include <string>
#include <sstream>
#include <queue>

#include "./textParse.h"

namespace tree {
    using namespace textParse;
    /**
     * Definition for a binary tree node.
     */
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    // stores a tree value for parsing
    struct TreeVal {
        int val;
        bool isNull;
    };

    std::string val2string(const TreeVal& treeVal) {
        if(treeVal.isNull) {
            return "null";
        } else {
            return std::to_string(treeVal.val);
        }
    }

    // parses tree node value, either int or null
    // returns true if successful
    // updating i to the next char after a successful match
    bool tryParseVal(std::string input, int& i, TreeVal& out_val) {
        int resetI = i;
        skipSpace(input, i);
        if(tryParseInt(input, i, out_val.val)) {
            out_val.isNull = false;
            return true;
        } else if(tryParseString(input, i, "null")) {
            out_val.isNull = true;
            return true;
        } else {
            i = resetI;
            return false;
        }
    }

    // attempts to parse a node list from input string at i
    // with a format similar to: [54,3,null,4]
    // returns true if successful
    // and updating i to the position after a successful match
    bool tryParseValList(std::string input, int& i, std::vector<TreeVal>& out_list) {
        int resetI = i;
        if(!tryParseNextChar(input, i, '[')) {
            i = resetI;
            return false;
        }

        TreeVal treeVal;
        // if true, expect a comma before any next value
        // assuming we aren't at the end of the list
        bool expectComma = false;

        while(i < input.size()) {
            // closing brace
            if(tryParseNextChar(input, i, ']')) {
                // end of list
                return true;
            // parse a comma if expected
            } else if(expectComma) {
                if(!tryParseNextChar(input, i, ',')) {
                    // improperly formatted list
                    i = resetI;
                    return false;
                } else {
                    expectComma = false;
                }
            } else if(tryParseVal(input, i, treeVal)) {
                out_list.push_back(treeVal);
                expectComma = true;
            } else {
                i = resetI;
                return false;
            }
        }

        // fail, the closing brace should have been found in the loop
        i = resetI;
        return false;
    }

    // returns the subtree at index i of the tree node values list
    TreeNode* getNodeAtI(const std::vector<TreeVal>& treeValues, int i) {
        if(treeValues.size() <= i) {
            return NULL;
        }

        if(treeValues[i].isNull) {
            return NULL;
        }

        TreeNode* node = new TreeNode(treeValues[i].val);
        node->left = getNodeAtI(treeValues, 2*i+1);
        node->right = getNodeAtI(treeValues, 2*i+2);
        return node;
    }

    bool tryParse(std::string input, int& i, TreeNode*& out_node) {
        std::vector<TreeVal> treeValList;
        if(!tryParseValList(input, i, treeValList)) {
            out_node = NULL;
            return false;
        }

        /*
            iterate over the tree values, creating new pointers if
            they are not specified to be null
            note: use a recursive algorithm which
            parses the left subtree at 2*i+1 for the left value
            and 2*i+1 for the right subtree, for a given index i
            of the vector
        */

        out_node = getNodeAtI(treeValList, 0);
        return true;
    }

    // returns true if successfully parsed a tree, updating out_node with the head
    bool tryParse(const std::string input, TreeNode*& out_node) {
        int i = 0; 
        return tryParse(input, i, out_node);
    }


    // delete all nodes in a tree
    void deleteTree(TreeNode* head) {
        if(!head) {
            return;
        }
        deleteTree(head->left);
        head->left = NULL;
        deleteTree(head->right);
        head->right = NULL;
        delete head;
    }

    TreeNode* string2tree(std::string input) {
        TreeNode* result;
        int i = 0;
        if(tryParse(input, i, result)) {
            return result;
        } else {
            return NULL;
        }
    }

    int getTreeSize(TreeNode* head) {
        if(!head) {
            return 0;
        }
        int tl = getTreeSize(head->left);
        int tr = getTreeSize(head->right);
        return 1 + tl + tr;
    }

    std::string tree2string(TreeNode* head) {
        std::stringstream ss;

        ss << '[';

        std::queue<TreeNode*> nodeQueue;
        if(head) {
            nodeQueue.push(head);
        }

        bool first = true;

        while(!nodeQueue.empty()) {
            TreeNode* node = nodeQueue.front();
            nodeQueue.pop();
            
            if(!first) {
                ss << ",";
            } else {
                first = false;
            }

            if(!node) {
                ss << "null";
            } else {
                ss << node->val;
                nodeQueue.push(node->left);
                nodeQueue.push(node->right);
            }
        }

        ss << ']';

        std::string result;
        ss >> result;
        return result;
    }

    // returns true if a equals b
    bool isEqual(TreeNode*& a, TreeNode*& b) {
        if(!a || !b) {
            return a == b;
        } else if(a->val != b->val) {
            return false;
        } else {
            return isEqual(a->left, b->left) && isEqual(a->right, b->right);
        }
    }
}

#endif // TREE_H

#include "../../common/common.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // returns true if all nodes are less than n
    bool isLessThan(TreeNode* root, int n) {
        if(root == nullptr) {
            return true;
        } else if(root->val >= n) {
            return false;
        }
        return isLessThan(root->left, n) && isLessThan(root->right, n);
    }

    // returns true if all nodes are greater than n
    bool isGreaterThan(TreeNode* root, int n) {
        if(root == nullptr) {
            return true;
        } else if(root->val <= n) {
            return false;
        }
        return isGreaterThan(root->left, n) && isGreaterThan(root->right, n);
    }

    bool isValidBST(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        return isLessThan(root->left, root->val) && isGreaterThan(root->right, root->val) && isValidBST(root->left) && isValidBST(root->right);
    }
};
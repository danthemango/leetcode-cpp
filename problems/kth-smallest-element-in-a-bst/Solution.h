#include "../../common/common.h"
#include "../../common/TreeNode.h"

using namespace std;
using namespace tree;

/* 
    Problem: 
    Given the root of a binary search tree, and an integer k,
    return the kth smallest value (1-indexed) of all the values
    of the nodes in the tree.
*/

/*
    Solution:
    let sizeLeft be the size of the left subtree
    let sizeRight be the size of the right subtree

    if sizeLeft >= k, return the kth-smallest element of the left subtree,
    else if sizeLeft+1 == k, return the current node,
    else let kr = k - sizeLeft - 1, and return the kr-th smallest element
    of the right subtree
*/

class Solution {
public:
    // returns the number of nodes in the current tree
    int getSize(TreeNode* root) {
        if(!root) {
            return 0;
        }
        return 1 + getSize(root->left) + getSize(root->right);
    }

    int kthSmallest(TreeNode* root, int k) {

        int sizeLeft = getSize(root->left);

        if(sizeLeft >= k) {
            return kthSmallest(root->left, k);
        } else if(sizeLeft+1 == k) {
            return root->val;
        } else {
            int sizeRight = getSize(root->right);
            int remainder = k - sizeLeft - 1;
            return kthSmallest(root->right, remainder);
        }
    }
};

#include "../../common/common.h"
using namespace tree;

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) {
            return 0;
        }
        if(!root->left) {
            return 1 + maxDepth(root->right);
        }
        if(!root->right) {
            return 1 + maxDepth(root->left);
        }
        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        if(l > r) {
            return 1 + l;
        } else {
            return 1 + r;
        }
    }
};
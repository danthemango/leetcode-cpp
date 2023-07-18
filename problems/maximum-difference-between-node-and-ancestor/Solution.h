#include "../../common/common.h"

class Solution {
public:
    int getMinValue(TreeNode* root) {
        int minDesc = root->val;
        if(root->left) {
            minDesc = min(minDesc, getMinValue(root->left));
        }
        if(root->right) {
            minDesc = min(minDesc, getMinValue(root->right));
        }
        return minDesc;
    }

    int getMaxValue(TreeNode* root) {
        int maxDesc = root->val;
        if(root->left) {
            maxDesc = max(maxDesc, getMaxValue(root->left));
        }
        if(root->right) {
            maxDesc = max(maxDesc, getMaxValue(root->right));
        }
        return maxDesc;
    }

    // returns the largest value of descendant - ancestor in tree
    int largestDescDiff(TreeNode* root) {
        // if there is no tree or no subtrees, the diff is going to be 0
        if(!root) {
            return 0;
        } else if(!root->left && !root->right) {
            return 0;
        }

        int maxVal;
        if (root->left && !root->right) {
            maxVal = getMaxValue(root->left);
        } else if(!root->left && root->right) {
            maxVal = getMaxValue(root->right);
        } else {
            maxVal = getMaxValue(root->left);
            maxVal = max(maxVal, getMaxValue(root->right));
        }
        int maxDiff = maxVal - root->val;
        if(root->left) {
            maxDiff = max(maxDiff, maxAncestorDiff(root->left));
        }
        if(root->right) {
            maxDiff = max(maxDiff, maxAncestorDiff(root->right));
        }
        return maxDiff;

    }

    // returns the largest value of ancestor - descendant in tree
    int largestAncDiff(TreeNode* root) {
        // if there is no tree or no subtrees, the diff is going to be 0
        if(!root) {
            return 0;
        } else if(!root->left && !root->right) {
            return 0;
        }

        int minVal;
        if (root->left && !root->right) {
            minVal = getMinValue(root->left);
        } else if(!root->left && root->right) {
            minVal = getMinValue(root->right);
        } else {
            minVal = getMinValue(root->left);
            minVal = min(minVal, getMinValue(root->right));
        }
        int maxDiff = root->val - minVal;
        if(root->left) {
            maxDiff = max(maxDiff, maxAncestorDiff(root->left));
        }
        if(root->right) {
            maxDiff = max(maxDiff, maxAncestorDiff(root->right));
        }
        return maxDiff;
    }

    int maxAncestorDiff(TreeNode* root) {
        return max(largestDescDiff(root), largestAncDiff(root));
    }
};

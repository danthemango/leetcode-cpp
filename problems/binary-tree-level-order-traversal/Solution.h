#include "../../common/common.h"

class Solution {
public:
    /*
        create an array of arrays result
        start with level 0
        run levelOrder with the result and level 0
        if result.size() < level, add a new vector<int>
        get result[level], and add this value to it
        run levelOrder with the left and right subtree
    */
    void levelOrder(TreeNode* root, vector<vector<int>>& result, int level) {
        if(!root) {
            return;
        }
        if(level >= result.size()) {
            vector<int> newRow;
            result.push_back(newRow);
        }
        vector<int>& row = result[level];
        row.push_back(root->val);
        levelOrder(root->left, result, level+1);
        levelOrder(root->right, result, level+1);
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        int level = 0;
        levelOrder(root, result, level);
        return result;
    }
};
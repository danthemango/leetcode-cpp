#include "../../common/common.h"

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0) {
            return nullptr;
        }
        // preorder index
        unsigned int pi = 0;
        // inorder index
        unsigned int ii = 0;
        int rootVal = preorder[pi];
        TreeNode* root = new TreeNode(rootVal);

        ++pi;
        {
            vector<int> leftPreorder;
            vector<int> leftInorder;
            while(inorder[ii] != rootVal) {
                leftPreorder.push_back(preorder[pi]);
                leftInorder.push_back(inorder[ii]);
                ++ii;
                ++pi;
            }
            root->left = buildTree(leftPreorder, leftInorder);
        }

        ++ii;
        {
            vector<int> rightPreorder;
            vector<int> rightInorder;
            while(ii < inorder.size()) {
                rightPreorder.push_back(preorder[pi]);
                rightInorder.push_back(inorder[ii]);
                ++ii;
                ++pi;
            }
            root->right = buildTree(rightPreorder, rightInorder);
        }
        return root;
    }
};
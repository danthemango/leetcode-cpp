#include "../../common/common.h"
using namespace tree;

class Solution
{
public:
    // updates a list of leaf values of this tree
    void getLeaves(TreeNode *root, std::vector<int> &leaves)
    {
        if (!root)
        {
            return;
        }

        if (!root->left && !root->right)
        {
            leaves.push_back(root->val);
        }
        if (root->left)
        {
            getLeaves(root->left, leaves);
        }
        if (root->right)
        {
            getLeaves(root->right, leaves);
        }
    }

    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {
        std::vector<int> leaves1;
        std::vector<int> leaves2;
        getLeaves(root1, leaves1);
        getLeaves(root2, leaves2);

        if (leaves1.size() != leaves2.size())
        {
            return false;
        }
        for (int i = 0; i < leaves1.size(); i++)
        {
            if (leaves1[i] != leaves2[i])
            {
                return false;
            }
        }
        return true;
    }
};

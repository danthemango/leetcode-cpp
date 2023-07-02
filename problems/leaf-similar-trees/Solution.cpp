#include "../../common/common.h"
using namespace tree;

class Solution {
public:
bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    std::vector<int> leaves1;
    std::vector<int> leaves2;
    getLeaves(root1, leaves1);
    getLeaves(root2, leaves2);
    if(leaves1.size() != leaves2.size()) {
        return false;
    }
    for(int i = 0; i < leaves1.size(); i++) {
        if(leaves1[i] != leaves2[i]){
            return false;
        }
    }
    return true;
}

// updates a list of leaf values of this tree
void getLeaves(TreeNode* root, std::vector<int>& leaves) {
    if(!root) {
        return;
    }

    if(!root->left && !root->right) {
        leaves.push_back(root->val);
    }
    if(root->left) {
        getLeaves(root->left, leaves);
    } 
    if(root->right) {
        getLeaves(root->right, leaves);
    }
}
};

class SolutionRunner {
    public:
    SolutionRunner(const std::string& treeString1, const std::string& treeString2, bool expected) {
        Solution solution;
        TreeNode* root1;
        TreeNode* root2;
        std::cout << "tree 1: " << treeString1 << std::endl;
        if(!tree::tryParse(treeString1, root1)) {
            std::cout << "could not parse treeString1: " << treeString1 << std::endl;
        }

        std::cout << "tree 2: " << treeString2 << std::endl;
        if(!tree::tryParse(treeString2, root2)) {
            std::cout << "could not parse treeString2: " << treeString2 << std::endl;
        }

        bool result = solution.leafSimilar(root1, root2);
        std::cout << "expected = " << expected << " result = " << result << std::endl;
        if(result != expected) {
            std::cout << "Fail." << std::endl;
        } else {
            std::cout << "Success." << std::endl;
        }
    }
};

int main() {
    std::vector<SolutionRunner> solutionRunners {
        {"[3,5,1,6,2,9,8,null,null,7,4]", "[3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]", true},
        {"[1,2,3]", "[1,3,2]", false}
    };
}

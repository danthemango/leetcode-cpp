#include <string>
#include <vector>
#include <iostream>
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

// an example input and expected values
struct SolutionInput {
    // the tree, as specified by an array in a string
    std::string treeString;
    int k;
    // expected result
    int exp;
};

void runSolution(SolutionInput& si) {
    Solution solution;
    TreeNode* head = tree::string2tree(si.treeString);
    int result = solution.kthSmallest(head, si.k);
    cout << "- input: " << endl;
    cout << "  - root: " << si.treeString << endl;
    cout << "  - k: " << si.k << endl;
    cout << "- expected: " << si.exp << endl;
    cout << "- result: " << result << endl;
    cout << (result == si.exp ? "Success." : "Fail.") << endl;
    cout << endl;
    tree::deleteTree(head);
}

int main() {
    std::vector<SolutionInput> sInputs {
        /* tree string, k, expected */
        {"[3,1,4,null,2]", 1, 1},
        {"[5,3,6,2,4,null,null,1]",3,3}
    };

    for(SolutionInput si : sInputs) {
        runSolution(si);
    }
}
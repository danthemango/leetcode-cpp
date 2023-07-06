#include "Solution.h"

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
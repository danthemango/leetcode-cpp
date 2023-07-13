#include "../../common/common.h"

class Counts {
    public:
    // val -> count
    std::map<int, int> counts;

    void increment(int val) {
        if(counts.find(val) == counts.end()) {
            counts[val] = 1;
        } else {
            ++counts[val];
        }
    }

    int get(int val) {
        if(counts.find(val) != counts.end()) {
            return counts[val];
        } else {
            return 0;
        }
    }
};

class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        // simple implementation by counting all values and putting a map of val -> count
        std::queue<TreeNode*> q;
        std::vector<int> result;
        if(root == nullptr) {
            return result;
        }

        int max = 0;
        Counts counts;
        q.push(root);
        while(!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();
            int val = cur->val;
            counts.increment(val);
            int count = counts.get(val);
            if(count == max) {
                result.push_back(val);
            } else if(count > max) {
                max = count;
                result.clear();
                result.push_back(val);
            }
            
            if(cur->left != nullptr) {
                q.push(cur->left);
            }
            if(cur->right != nullptr) {
                q.push(cur->right);
            }
        }
        return result;
    }
};
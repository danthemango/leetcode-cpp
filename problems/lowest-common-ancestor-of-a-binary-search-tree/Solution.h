#include "../../common/common.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct NodeParent {
    NodeParent(TreeNode* _node, NodeParent* _parent) : node(_node), parent(_parent), left(nullptr), right(nullptr) {}
    TreeNode* node;
    NodeParent* parent;
    NodeParent* left;
    NodeParent* right;
};


class Solution {
public:
    NodeParent* getNodeParent(TreeNode* node, NodeParent* parent, TreeNode* p, TreeNode* q, NodeParent*& np, NodeParent*& nq) {
        if(node == nullptr) {
            return nullptr;
        }
        NodeParent* nodeParent = new NodeParent(node, parent);
        if(node == p) {
            np = nodeParent;
        }
        if(node == q) {
            nq = nodeParent;
        }
        nodeParent->left = getNodeParent(node->left, nodeParent, p, q, np, nq);
        nodeParent->right = getNodeParent(node->right, nodeParent, p, q, np, nq);
        return nodeParent;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        NodeParent* np;
        NodeParent* nq;
        getNodeParent(root, nullptr, p, q, np, nq);
        std::map<NodeParent*, bool> nodeParentMap;
        NodeParent* cur = np;
        while(cur != nullptr) {
            nodeParentMap[cur] = true;
            cur = cur->parent;
        }
        cur = nq;
        while(nodeParentMap.find(cur) == nodeParentMap.end()) {
            cur = cur->parent;
        }
        return cur->node;
    }
};
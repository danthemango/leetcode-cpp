
#include <string>
#include <sstream>
#include <queue>

#include "TreeNode.h"
#include "textParse.h"

TreeNode::TreeNode() : val(0), left(nullptr), right(nullptr) {}
TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
TreeNode::TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

std::string node2string(TreeNode* node) {
    if(node == nullptr) {
        return "null";
    } else {
        return std::to_string(node->val);
    }
}

bool isSame(TreeNode* a, TreeNode* b) {
    if(!a || !b) {
        return a == b;
    } else {
        return a->val == b->val && isSame(a->left, b->left) && isSame(a->right, b->right);
    }
}

bool TreeNode::operator==(TreeNode& other) const {
    return isSame((TreeNode*) this, &other);
}

void TreeNode::deleteTree(TreeNode* root) {
    if(root == nullptr) {
        return;
    }    
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    delete root;
    deleteTree(left);
    deleteTree(right);
}

unsigned int CountNodes(TreeNode* root) {
    if(root == nullptr) {
        return 0;
    } else {
        return 1 + CountNodes(root->left) + CountNodes(root->right);
    }
}

std::vector<std::string> tree2vector(TreeNode* root) {
    std::vector<std::string> result;
    std::queue<TreeNode*> nodeQueue;
    if(root != nullptr) {
        nodeQueue.push(root);
    }
    while(!nodeQueue.empty()) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();
        result.push_back(node2string(node));
        if(node != nullptr) {
            nodeQueue.push(node->left);
            nodeQueue.push(node->right);
        }
    }
    return result;
}

std::string tree2string(TreeNode* root) {
    std::vector<std::string> nodeStrings = tree2vector(root);

    std::string result;
    result.push_back('[');
    bool first = true;
    for(std::string& nodeString : nodeStrings) {
        if(!first) {
            result.push_back(',');
        }
        first = false;
        result.append(nodeString);
    }
    result.push_back(']');
    return result;
}

std::ostream& operator<<(std::ostream& os, TreeNode* tn) {
    os << tree2string(tn);
    return os;
}

std::ostream& operator<<(std::ostream& os, TreeNode& tn) {
    os << &tn;
    return os;
}

bool tryParseNextTreeNode(const std::string& input, unsigned int& i, TreeNode*& out_node) { 
    using namespace textParse;
    int intVal;
    skipSpace(input, i);
    if(tryParseNextString(input, i, "null")) {
        out_node = nullptr;
        return true;
    } else if(tryParseNextInt(input, i, intVal)) {
        out_node = new TreeNode(intVal);
        return true;
    } else {
        return false;
    }
}

// deletes all node pointers that have been set
void deleteNodeVector(std::vector<TreeNode*> arr) {
    for(TreeNode*& node : arr) {
        if(node != nullptr) {
            delete node;
            node = nullptr;
        }
    }
}

class TreeVector {
    public:
    std::vector<TreeNode*> vals;
    // delete entries if never fetched
    bool fetched = false;

    ~TreeVector() {
        if(fetched) {
            return;
        }

        for(TreeNode*& val : vals) {
            if(val != nullptr) {
                delete val;
            }
        }
    }

    void push_back(TreeNode* val) {
        this->vals.push_back(val);
    }

    std::vector<TreeNode*> get() {
        fetched = true;
        return this->vals;
    }
};

// tries to parse an array of treenodes
bool tryParseTreeNodeVector(const std::string& input, unsigned int& i, std::vector<TreeNode*>& out_arr) {
    TreeVector treeVector;
    unsigned int resetI = i;
    using namespace textParse;
    if(!tryParseNextChar(input, i, '[')) {
        i = resetI;
        return false;
    }
    bool first = true;
    while(i < input.size()) {
        if(tryParseNextChar(input, i, ']')) {
            out_arr = treeVector.get();
            return true;
        }
        if(first) {
            first = false;
        } else if(!tryParseNextChar(input, i, ',')) {
            i = resetI;
            return false;
        }

        TreeNode* node;
        if(!tryParseNextTreeNode(input, i, node)) {
            i = resetI;
            return false;
        } else {
            treeVector.push_back(node);
        }
    }
    i = resetI;
    return false;
}

// depending on the node state, the new node will be put on 
// the left of the current node, the right of the current node,
// or we need to request a new node for the next value
enum class NodeState { left, right, needNew };

std::ostream& operator<<(std::ostream& os, std::vector<TreeNode*> arr) {
    os << '[';
    bool first = true;
    for(TreeNode*& node : arr) {
        if(first) {
            first = false;
        } else {
            os << ',';
        }
        if(node == nullptr) {
            os << "null";
        } else {
            os << node->val;
        }
    }
    os << ']';
    return os;
}

TreeNode* TreeNodeVector2Tree(std::vector<TreeNode*>& nodeArr, unsigned int i) {
    if(i >= nodeArr.size()) {
        return nullptr;
    }
    TreeNode* root = nodeArr[i];
    if(!root) {
        return nullptr;
    }
    root->left = TreeNodeVector2Tree(nodeArr, i*2+1);
    root->right = TreeNodeVector2Tree(nodeArr, i*2+2);
    return root;
}

bool TreeNode::tryParse(const std::string& input, unsigned int& i, TreeNode*& out_root) {
    int resetI = i;

    std::vector<TreeNode*> arr;
    if(!tryParseTreeNodeVector(input, i, arr)) {
        i = resetI;
        return false;
    }

    if(arr.size() == 0 || arr[0] == nullptr) {
        out_root = nullptr;
        return true;
    }

    out_root = TreeNodeVector2Tree(arr, 0);
    return true;
}

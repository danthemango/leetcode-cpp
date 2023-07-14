
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

bool TreeNode::operator==(TreeNode& other) const {
    if(this->val != other.val) {
        return false;
    }
    if(this->left == nullptr || other.left == nullptr) {
        return this->left == other.left;
    }
    if(this->right == nullptr || other.right == nullptr) {
        return this->right == other.right;
    }
    return *this->left == *other.left && *this->right == *other.right;
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

std::string tree2string(TreeNode* root) {
    std::queue<TreeNode*> valQueue;
    if(root != nullptr) {
        valQueue.push(root);
    }
    std::string result;
    result.push_back('[');
    bool first = true;
    while(!valQueue.empty()) {
        if(!first) {
            result.push_back(',');
        }
        first = false;

        TreeNode* node = valQueue.front();
        valQueue.pop();
        std::string stringVal = node2string(node);
        result.append(stringVal);
        if(node != nullptr) {
            valQueue.push(node->left);
            valQueue.push(node->right);
        }
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

bool TreeNode::tryParse(const std::string& input, unsigned int& i, TreeNode*& out_root) {
    int resetI = i;
    out_root = nullptr;

    std::vector<TreeNode*> arr;
    if(!tryParseTreeNodeVector(input, i, arr)) {
        i = resetI;
        return false;
    }

    if(arr.size() == 0 || arr[0] == nullptr) {
        return true;
    }

    std::queue<TreeNode*> nodeQueue;
    unsigned int arrI = 0;
    out_root = arr[arrI];
    if(out_root != nullptr) {
        nodeQueue.push(out_root);
    } else {
        return true;
    }
    TreeNode* cur = nullptr;
    NodeState nodeState = NodeState::needNew;
    ++arrI;
    while(arrI < arr.size()) {
        TreeNode* newNode = arr[arrI];
        ++arrI;
        if(nodeState == NodeState::left) {
            cur->left = newNode;
            nodeState = NodeState::right;
        } else if(nodeState == NodeState::right) {
            cur->right = newNode;
            nodeState = NodeState::needNew;
        } else if(nodeState == NodeState::needNew) {
            cur = nodeQueue.front();
            nodeQueue.pop();
            cur->left = newNode;
            nodeState = NodeState::right;
        } else {
            throw "should never happen";
        }

        if(newNode != nullptr) {
            nodeQueue.push(newNode);
        }
    }

    return true;
}

#include "../../common/common.h"

class Codec {
    public:
    // returns a stringified version of node
    std::string node2string(TreeNode* node) {
        if(node == nullptr) {
            return "null";
        } else {
            return std::to_string(node->val);
        }
    }

    std::string serialize(TreeNode* root) {
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

            TreeNode* nodeVal = valQueue.front();
            valQueue.pop();
            std::string stringVal = node2string(nodeVal);
            result.append(stringVal);
            if(nodeVal != nullptr) {
                valQueue.push(nodeVal->left);
                valQueue.push(nodeVal->right);
            }
        }
        result.push_back(']');
        return result;
    }

    TreeNode* string2node(std::string stringVal) {
        if(stringVal == "null") {
            return nullptr;
        } else {
            return new TreeNode(atoi(stringVal.c_str()));
        }
    }

    std::vector<std::string> string2arr(std::string str) {
        unsigned int i = 0;
        bool first = true;
        std::vector<std::string> result;
        if(str[i] != '[') {
            throw "error string2arr: need opening brace";
        }
        ++i;
        while(i < str.size()) {
            if(str[i] == ']') {
                return result;
            }

            if(!first) {
                if(str[i] != ',') {
                    throw "string2arr: missing comma separated value";
                }
                ++i;
            }
            first = false;
            std::string val;
            while(str[i] != ']' && str[i] != ',') {
                val += str[i];
                ++i;
            }
            result.push_back(val);
        }
        throw "string2arr: missing closing brace";
    }

    // depending on the node state, the new node will be put on 
    // the left of the current node, the right of the current node,
    // or we need to request a new node for the next value
    enum NodeState { left, right, needNew };

    TreeNode* deserialize(std::string str) {
        std::vector<std::string> arr = string2arr(str);
        if(arr.size() == 0) {
            return nullptr;
        }
        TreeNode* root = string2node(arr[0]);
        if(root == nullptr) {
            return nullptr;
        }

        unsigned int i = 1;
        TreeNode* cur = nullptr;
        NodeState nodeState = needNew;
        std::queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        while(i < arr.size()) {
            TreeNode* newNode = string2node(arr[i]);
            ++i;
            if(nodeState == left) {
                cur->left = newNode;
                nodeState = right;
            } else if(nodeState == right) {
                cur->right = newNode;
                nodeState = needNew;
            } else if(nodeState == needNew) {
                cur = nodeQueue.front();
                nodeQueue.pop();
                cur->left = newNode;
                nodeState = right;
            } else {
                throw "should never happen";
            }

            if(newNode != nullptr) {
                nodeQueue.push(newNode);
            }
        }
        return root;
    }
};

class Solution {
    public:
    TreeNode* run(TreeNode* root) {
        Codec ser, deser;
        std::string serialized = ser.serialize(root);
        std::cout << "serialized: " << serialized << std::endl;
        TreeNode* result = deser.deserialize(serialized);
        // std::cout << "result: " << tree::tree2string(result) << std::endl;
        return result;
    }
};
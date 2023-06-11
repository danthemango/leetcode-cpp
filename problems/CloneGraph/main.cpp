#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <exception>
#include <map>
#include <queue>
#include <sstream>
using namespace std;

// max number of nodes based on constraints, to be used for error checking
#define MAXNODES 100

namespace graphNode {

    class Node {
    public:
        int val;
        vector<Node*> neighbors;
        Node() {
            val = 0;
            neighbors = vector<Node*>();
        }
        Node(int _val) {
            val = _val;
            neighbors = vector<Node*>();
        }
        Node(int _val, vector<Node*> _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    };
}

// TODO move to other file
using namespace graphNode;

class Solution {
    public:
    Node* cloneGraph(Node* node) {
        return NULL;
    }
};

// returns true if the solution returns proper expected string value for a given in string
bool runSolution(string inStr, string expStr);

// returns true if the value is a digit
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int getDigit(char c) {
    return c - '0';
}

// TODO parse all whitespace
bool isSpace(char c) {
    return c == ' ';
}

// returns true if c is the char in input at i
// incrementing i if found
bool isChar(std::string input, int& i, char c) {
    if(i < input.size() && input[i] == c) {
        i++;
        return true;
    } else {
        return false;
    }
}

// increments i until a non-whitespace is found
void skipSpace(std::string input, int& i) {
    while(i < input.size() && isSpace(input[i])) {
        i++;
    }
}

// returns true if the next non-space char is c at pos i of input
// incrementing i if found
bool isNextChar(std::string input, int& i, char c) {
    skipSpace(input, i);
    return isChar(input, i, c);
}

// returns true if an int can be found at position i of input string
// and returns the value in out_int
// and increments i to the char after the pattern
bool tryGetInt(std::string input, int& i, int& out_int) {
    skipSpace(input, i);

    if(i >= input.size()) {
        return false;
    }

    if(!isDigit(input[i])) {
        return false;
    }

    out_int = 0;
    while(i < input.size() && isDigit(input[i])) {
        out_int *= 10;
        out_int += getDigit(input[i]);
        i++;
    }

    return true;
}

// returns true if an edge of format "[a,b,c,...]" can be found in string
// at position i
// and increments i to the char after the pattern
bool tryGetEdge(std::string input, int& i, std::vector<int>& edge) {
    int resetI = i;
    if(!isNextChar(input, i, '[')) {
        i = resetI;
        return false;
    }
    int out_int;
    bool foundInt = tryGetInt(input, i, out_int);
    while(foundInt) {
        edge.push_back(out_int);
        if(!isNextChar(input, i, ',')) {
            break;
        }
        foundInt = tryGetInt(input, i, out_int);
    }
    if(!isNextChar(input, i, ']')) {
        i = resetI;
        return false;
    }
    return true;
}

// returns true if an array of edges with format [[a,b],[c,d]] are found
// with 0 or more edges
// and increments i to the char after the pattern
bool tryGetEdges(std::string input, int& i, vector<vector<int>>& out_edges) {
    if(!isNextChar(input, i, '[')) {
        return false;
    }

    vector<int> edge;
    bool foundEdge = tryGetEdge(input, i, edge);
    while(foundEdge) {
        vector<int> newEdge = edge;
        edge.clear();
        out_edges.push_back(newEdge);
        if(!isNextChar(input, i, ',')) {
            break;
        }
        foundEdge = tryGetEdge(input, i, edge);
    }

    if(!isNextChar(input, i, ']')) {
        return false;
    }
    return true;
}

// returns true if an array of edges with format [[a,b],[c,d,...],...] are found
// with 0 or more nodes and 0 or more edges
bool tryGetEdges(std::string input, vector<vector<int>>& out_edges) {
    int i = 0;
    return tryGetEdges(input, i, out_edges);
}

// returns node for given string, null if it cannot be parsed
Node* string2Graph(string input) {
    // get list of edges for each node
    vector<vector<int>> nodeEdgeLists;
    if(!tryGetEdges(input, nodeEdgeLists)) {
        return NULL;
    } else if(nodeEdgeLists.size() == 0) {
        return NULL;
    }

    // create head node ptr
    // create map which corresponds node val (int) to node ptr
    // for each node of the edge-lists:
    // - create new node with val
    // - fill the map 
    // - fill head if it's empty

    Node* head = NULL;
    std::map<int, Node*> nodeMap;
    int val = 1;
    for(const vector<int>& nodeEdges: nodeEdgeLists) {
        Node* node = new Node(val);
        if(head == NULL) {
            head = node;
        }
        nodeMap[val] = node;
        val++;
    }

    // for each val in the edge list:
    //     - look up the node ptr from the map and set it as current
    //     - for each edge:
    //         - look up corresponding ptr from the map
    //         - add the ptr as a neighbor to the current node ptr

    for(int i = 0; i < nodeEdgeLists.size(); i++) {
        int curVal = i+1;
        const vector<int>& nodeEdges = nodeEdgeLists[i];
        for(const int& neighVal: nodeEdges) {
            Node* curNode = nodeMap[curVal];
            Node* neighNode = nodeMap[neighVal];
            curNode->neighbors.push_back(neighNode);
        }
    }

    // return head node ptr
    return head; 
}

// returns a string for a given graph
string graph2String(Node* head) {
    /*
    create a map which corresponds a val to a node ptr
    create a queue of node ptrs
    add the head to the queue
    */

    if(head == NULL) {
        return "[]";
    }

    std::map<int, Node*> nodeMap;
    std::queue<Node*> nodeQueue;
    nodeQueue.push(head);
    nodeMap[head->val] = head;

    /*
    while the queue isn't empty:
    - pop a node from the queue
    - put val and ptr into the node map
    - increment numNodes
    - for each neighbor of node:
        - if neighbor not in map, add it to the queue
    */

   int numNodes = 1;
   while (!nodeQueue.empty()) {
        Node* curNode = nodeQueue.front();
        nodeQueue.pop();
        for(Node* neighPtr : curNode->neighbors) {
            if(nodeMap.find(neighPtr->val) == nodeMap.end()) {
                nodeMap[neighPtr->val] = neighPtr;
                nodeQueue.push(neighPtr);
                numNodes++;
            }
        }
   }

   /*
   for each node in the map:
   - make a string list of the neighbors, in the form of [a,b,c,...]
   */

    std::stringstream ss;
    ss << '[';
    bool firstNode = true;
    for (int i = 1; i <= numNodes; i++)
    {
        if (!firstNode) {
            ss << ',';
        } else {
            firstNode = false;
        }

        Node *node = nodeMap[i];
        ss << '[';
        bool firstEdge = true;
        for (Node *neighNode : node->neighbors)
        {
            if (!firstEdge)
            {
                ss << ',';
            }
            else
            {
                firstEdge = false;
            }
            ss << neighNode->val;
        }
        ss << ']';
    }
    ss << ']';

    std::string result;
    ss >> result;

    return result;
}

// returns true if the two nodes are connected
bool areConnected(Node* a, Node* b) {
    // TODO
    return false;
}

// returns true if all connections are the same
bool areSame(Node* a, Node* b) {
    // TODO
    return false;
}

/*
constraints:
- The number of nodes in the graph is in the range [0, 100].
- 1 <= Node.val <= 100
- Node.val is unique for each node.
- There are no repeated edges and no self-loops in the graph.
- The Graph is connected and all nodes can be visited starting from the given node.
*/

// returns true if the result was the same as expected
bool runSolution(int testNbr, string inStr, string expStr) {
    std::cout << "running test number " << testNbr << std::endl;
    Node* head = string2Graph(inStr);
    std::string result = graph2String(head);
    cout << "result: " << result << endl;

    // Solution mySolution;
    // Node* inNode = string2Graph(inStr);
    // Node* result = mySolution.cloneGraph(inNode);
}

int main() {
    try {
        int i = 1;
        runSolution(i++, "[[2,4],[1,3],[2,4],[1,3]]", "[[2,4],[1,3],[2,4],[1,3]]");
        runSolution(i++, "[[]]","[[]]");
        runSolution(i++, "[]","[]");
        std::cout << "all done" << std::endl;
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    } catch (const char* s) {
        std::cout << "exception: " << s << std::endl;
    }
}
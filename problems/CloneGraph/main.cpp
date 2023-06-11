#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <exception>
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
    while(isSpace(input[i])) {
        i++;
    }

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

// returns node for given string
Node* string2Graph(string input) {
    if(input.size() < 2 || input[0] != '[' || input[input.size()-1] != ']') {
        throw "input must be of the form: '[[(\\d+)+]*]'";
    }
    
    int i = 0;
    int nesting = 0;
    while(i < input.size()-1) {
        int startEdge = -1;
        int endEdge = -1;


    }

    // TODO

    return NULL; 
}

// returns a string for a given graph
string graph2String(Node* input) {
    // TODO
    return "";
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

// returns a list of all nodes in a graph
vector<Node*> getAllNodes(Node* graph) {
    // TODO
}

// returns true if all nodes values in a graph are in a range (inclusive)
bool allNodesInRange(Node* graph, int min, int max) {
    vector<Node*> allNodes = getAllNodes(graph);
    for(Node* node : allNodes) {
        if(node->val < min || node->val > max) {
            return false;
        }
    }
    return true;
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

    int i = 0;
    vector<vector<int>> edges;
    bool foundEdges = tryGetEdges(inStr, i, edges);

    if(!foundEdges) {
        cout << "found no nodes" << endl;
    } else {
        cout << "found " << edges.size() << (edges.size() == 1 ? " node" : " nodes") << endl;
        for(const vector<int>& edge : edges) {
            cout << '[';
            for(const int& part : edge) {
                cout << part << " ";
            }
            cout << ']';
            cout << endl;
        }
    }

    // Solution mySolution;
    // Node* inNode = string2Graph(inStr);
    // Node* result = mySolution.cloneGraph(inNode);
}

int main() {
    try {
        int i = 1;
        runSolution(i++, "[[2,4],[1,3],[2,4],[1,3]]", "[[2,4],[1,3],[2,4],[1,3]]");
        runSolution(i++, "[[]]","[[]]");
        runSolution(i++, "[[1,2,3,4],[5,6,4]]", "[[2,4],[1,3],[2,4],[1,3]]");
        runSolution(i++, "[]","[]");
        std::cout << "all done" << std::endl;
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    } catch (const char* s) {
        std::cout << "exception: " << s << std::endl;
    }
}
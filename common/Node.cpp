#include "Node.h"

Node::Node() {
    val = 0;
    neighbors = std::vector<Node*>();
}
Node::Node(int _val) {
    val = _val;
    neighbors = std::vector<Node*>();
}
Node::Node(int _val, std::vector<Node*> _neighbors) {
    val = _val;
    neighbors = _neighbors;
}

TNodePtr::TNodePtr() {};
TNodePtr::TNodePtr(Node* _val) : val(_val) { }

TNodePtr::~TNodePtr() {
    deleteGraph(val);
}

Node* TNodePtr::get() {
    return val;
}

bool TNodePtr::tryParse(const std::string& input) {
    unsigned int i = 0;
    std::vector<std::vector<int>> nodeEdgeLists;
    if(!tryGetEdges(input, i, nodeEdgeLists)) {
        val = nullptr;
        return false;
    }
    val = vector2graph(nodeEdgeLists);
    return true;
}

std::ostream & operator<<(std::ostream& os, TNodePtr& t) {
    Node* head = t.val;
    os << TNodePtr::graph2String(head);
    return os;
}

// the graphs are identical in content, not necessarily the same object
bool TNodePtr::operator==(const TNodePtr& other) {
    return areSame(this->val, other.val);
}

// returns true if an edge of format "[a,b,c,...]" can be found in string
// at position i
// and increments i to the char after the pattern
bool TNodePtr::tryGetEdge(std::string input, unsigned int& i, std::vector<int>& edge) {
    int resetI = i;
    if(!textParse::tryParseNextChar(input, i, '[')) {
        i = resetI;
        return false;
    }
    int out_int;
    bool foundInt = textParse::tryParseInt(input, i, out_int);
    while(foundInt) {
        edge.push_back(out_int);
        if(!textParse::tryParseNextChar(input, i, ',')) {
            break;
        }
        foundInt = textParse::tryParseInt(input, i, out_int);
    }
    if(!textParse::tryParseNextChar(input, i, ']')) {
        i = resetI;
        return false;
    }
    return true;
}

// returns true if an array of edges with format [[a,b],[c,d]] are found
// with 0 or more edges
// and increments i to the char after the pattern
bool TNodePtr::tryGetEdges(std::string input, unsigned int& i, std::vector<std::vector<int>>& out_edges) {
    if(!textParse::tryParseNextChar(input, i, '[')) {
        return false;
    }

    std::vector<int> edge;
    bool foundEdge = tryGetEdge(input, i, edge);
    while(foundEdge) {
        std::vector<int> newEdge = edge;
        edge.clear();
        out_edges.push_back(newEdge);
        if(!textParse::tryParseNextChar(input, i, ',')) {
            break;
        }
        foundEdge = tryGetEdge(input, i, edge);
    }

    if(!textParse::tryParseNextChar(input, i, ']')) {
        return false;
    }
    return true;
}

// returns true if an array of edges with format [[a,b],[c,d,...],...] are found
// with 0 or more nodes and 0 or more edges
bool TNodePtr::tryGetEdges(std::string input, std::vector<std::vector<int>>& out_edges) {
    unsigned int i = 0;
    return tryGetEdges(input, i, out_edges);
}

// accepts a list of lists and creates a graph from it
Node* TNodePtr::vector2graph(std::vector<std::vector<int>> nodeEdgeLists) {
    // create head node ptr
    // create map which corresponds node val (int) to node ptr
    // for each node of the edge-lists:
    // - create new node with val
    // - fill the map 
    // - fill head if it's empty

    Node* head = nullptr;
    std::map<int, Node*> nodeMap;
    int val = 1;
    for(const std::vector<int>& nodeEdges: nodeEdgeLists) {
        Node* node = new Node(val);
        if(head == nullptr) {
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

    for(unsigned int i = 0; i < nodeEdgeLists.size(); i++) {
        int curVal = i+1;
        const std::vector<int>& nodeEdges = nodeEdgeLists[i];
        for(const int& neighVal: nodeEdges) {
            Node* curNode = nodeMap[curVal];
            Node* neighNode = nodeMap[neighVal];
            curNode->neighbors.push_back(neighNode);
        }
    }

    // return head node ptr
    return head;
}

// returns node for given string, null if it cannot be parsed
Node* TNodePtr::string2Graph(std::string input) {
    // get list of edges for each node
    std::vector<std::vector<int>> nodeEdgeLists;
    if(!tryGetEdges(input, nodeEdgeLists)) {
        return nullptr;
    } else if(nodeEdgeLists.size() == 0) {
        return nullptr;
    }

    return vector2graph(nodeEdgeLists);
}

// returns a map of node values to node pointers by traversing the graph
std::map<int, Node*> TNodePtr::getNodeMap(Node* head) {
    /*
    create a map which corresponds a val to a node ptr
    create a queue of node ptrs
    add the head to the queue
    */

    std::map<int, Node*> nodeMap;
    if(head == nullptr) {
        return nodeMap;
    }

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

while (!nodeQueue.empty()) {
        Node* curNode = nodeQueue.front();
        nodeQueue.pop();
        for(Node* neighPtr : curNode->neighbors) {
            if(nodeMap.find(neighPtr->val) == nodeMap.end()) {
                nodeMap[neighPtr->val] = neighPtr;
                nodeQueue.push(neighPtr);
            }
        }
}

    return nodeMap;
}

// returns a string for a given graph
std::string TNodePtr::graph2String(Node* head) {
    if(head == nullptr) {
        return "[]";
    }

    std::map<int, Node*> nodeMap = getNodeMap(head);
    int numNodes = nodeMap.size();

    /*
        for each node in the map:
        - make a string list of the neighbors, in the form of [a,b,c,...]
    */

    std::string result;
    result.push_back('[');
    bool firstNode = true;
    for (int i = 1; i <= numNodes; i++)
    {
        if (!firstNode) {
            result.push_back(',');
        } else {
            firstNode = false;
        }

        Node *node = nodeMap[i];
        result.push_back('[');
        bool firstEdge = true;
        for (Node *neighNode : node->neighbors)
        {
            if (!firstEdge)
            {
                result.push_back(',');
            }
            else
            {
                firstEdge = false;
            }
            result.push_back(neighNode->val);
        }
        result.push_back(']');
    }
    result.push_back(']');

    return result;
}

// returns true if the two nodes are connected
bool TNodePtr::areConnected(Node* a, Node* b) {
    /*
    get a map of each node value to it's pointer from graph in a
    check if any of them match b
    */
    auto nodeMap = getNodeMap(a);
    for(auto& nodePair : nodeMap) {
        Node* node = nodePair.second;
        if(node == b) {
            return true;
        }
    }

    return false;
}

// returns true if the list of node neighbors are the same
// assuming each neighbor has a unique value and the list doesn't
// need to be sorted
bool TNodePtr::areSameNeighbors(std::vector<Node*> aNeighbors, std::vector<Node*> bNeighbors) {
    /*
        create a map af neighbors in a and b,
        ensure that each entry in a is found in b and vice versa
    */
    std::map<int, Node*> aNeighMap;
    std::map<int, Node*> bNeighMap;
    for(Node*& aNeighbor : aNeighbors) {
        aNeighMap[aNeighbor->val] = aNeighbor;
    }

    for(Node*& bNeighbor : bNeighbors) {
        bNeighMap[bNeighbor->val] = bNeighbor;
    }

    for(const std::pair<int, Node*>& aNeighPair : aNeighMap) {
        int aNeighVal = aNeighPair.first;
        if(bNeighMap.find(aNeighVal) == bNeighMap.end()) {
            return false;
        }
    }
    
    for(const std::pair<int, Node*>& bNeighPair : aNeighMap) {
        int bNeighVal = bNeighPair.first;
        if(aNeighMap.find(bNeighVal) == aNeighMap.end()) {
            return false;
        }
    }

    return true;
}

// returns true if all connections are the same
bool TNodePtr::areSame(Node* a, Node* b) {
    if(a == nullptr) {
        return b == nullptr;
    } else if(b == nullptr) {
        return a == nullptr;
    }

    /*
        get a map of all nodes in graph a and graph b,
        ensure each value in a is also found in b,
        ensure the corresponding node has neighbors also found in b,
        then ensure each value in b is found in a,
        then ensure the corresponding node has neighbors found in a
    */
std::map<int, Node*> aNodeMap = getNodeMap(a);
std::map<int, Node*> bNodeMap = getNodeMap(b);

    for(std::pair<int, Node*> aPair : aNodeMap) {
        int& aVal = aPair.first;
        Node*& aNode = aPair.second;
        if(bNodeMap.find(aVal) == bNodeMap.end()) {
            return false;
        }
        Node*& bNode = bNodeMap[aVal];
        if(!areSameNeighbors(aNode->neighbors, bNode->neighbors)) {
            return false;
        }
    }

    for(std::pair<int, Node*> bPair : bNodeMap) {
        int& bVal = bPair.first;
        Node*& bNode = bPair.second;
        if(aNodeMap.find(bVal) == bNodeMap.end()) {
            return false;
        }
        Node*& aNode = aNodeMap[bVal];
        if(!areSameNeighbors(bNode->neighbors, aNode->neighbors)) {
            return false;
        }
    }
    
    return true;
}

// deletes all nodes in a graph
void TNodePtr::deleteGraph(Node* head) {
    if(!head) {
        return;
    }

    std::map<int, Node*> nodeMap = getNodeMap(head);
    for(const std::pair<int, Node*>& nodePair : nodeMap) {
        delete nodePair.second;
    }
}

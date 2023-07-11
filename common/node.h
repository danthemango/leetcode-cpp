#ifndef NODE_H
#define NODE_H

#include <map>
#include <queue>
#include <vector>
#include <string>
#include "textParse.h"

class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node();
    Node(int _val);
    Node(int _val, std::vector<Node*> _neighbors);
};

class TNodePtr {
    public:
    Node* val;

    TNodePtr();
    TNodePtr(Node* _val);

    ~TNodePtr();

    Node* get();

    bool tryParse(const std::string& input);

    friend std::ostream & operator<<(std::ostream& os, TNodePtr& t);

    // the graphs are identical in content, not necessarily the same object
    bool operator==(const TNodePtr& other);

    // returns true if an edge of format "[a,b,c,...]" can be found in string
    // at position i
    // and increments i to the char after the pattern
    bool tryGetEdge(std::string input, int& i, std::vector<int>& edge);

    // returns true if an array of edges with format [[a,b],[c,d]] are found
    // with 0 or more edges
    // and increments i to the char after the pattern
    bool tryGetEdges(std::string input, int& i, std::vector<std::vector<int>>& out_edges);

    // returns true if an array of edges with format [[a,b],[c,d,...],...] are found
    // with 0 or more nodes and 0 or more edges
    bool tryGetEdges(std::string input, std::vector<std::vector<int>>& out_edges);

    // accepts a list of lists and creates a graph from it
    Node* vector2graph(std::vector<std::vector<int>> nodeEdgeLists);

    // returns node for given string, null if it cannot be parsed
    Node* string2Graph(std::string input);

    // returns a map of node values to node pointers by traversing the graph
    static std::map<int, Node*> getNodeMap(Node* head);

    // returns a string for a given graph
    static std::string graph2String(Node* head);

    // returns true if the two nodes are connected
    bool areConnected(Node* a, Node* b);

    // returns true if the list of node neighbors are the same
    // assuming each neighbor has a unique value and the list doesn't
    // need to be sorted
    bool areSameNeighbors(std::vector<Node*> aNeighbors, std::vector<Node*> bNeighbors);

    // returns true if all connections are the same
    bool areSame(Node* a, Node* b);

    // deletes all nodes in a graph
    void deleteGraph(Node* head);
};

#endif // NODE_H

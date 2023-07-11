#include "../../common/common.h"
#include "../../common/Node.h"

using namespace std;

// max number of nodes based on constraints, to be used for error checking
#define MAXNODES 100

class Solution {
    public:
    Node* cloneGraph(Node* adjList) {
        Node* head = adjList;
        if(head == NULL) {
            return NULL;
        }

        /* 
            create a map of all of the visited nodes in the graph
            which corresponds each of the node values to it's pointer (Node*)
            do this by creating a queue of nodes, pushing the head node to the queue,
            looking at the front node of the queue, 
            looking at all of the neighbours of this node,
            and if the neighbor is unvisited, adding it to the map
            then adding the neighbor to the queue
        */

        std::map<int, Node*> nodeMap;
        std::queue<Node*> nodeQueue;
        nodeMap[head->val] = head;
        nodeQueue.push(head);
        while(!nodeQueue.empty()) {
            Node* node = nodeQueue.front();
            nodeQueue.pop();
            for(Node* neighbor : node->neighbors) {
                if(nodeMap.find(neighbor->val) == nodeMap.end()) {
                    nodeMap[neighbor->val] = neighbor;
                    nodeQueue.push(neighbor);
                }
            }
        }

        /* 
            iterate through the list of nodes, and create a copy of each of them into a clone map
        */
        std::map<int, Node*> cloneMap;
        for(const std::pair<int, Node*>& nodePair : nodeMap) {
            const int& val = nodePair.first;
            cloneMap[val] = new Node(val);
        }

        /*
            iterate through the list of nodes again,
            and add the pointers of the cloned neighbor 
            to the cloned node's neighbor list
        */
        for(const std::pair<int, Node*>& nodePair : nodeMap) {
            const int& val = nodePair.first;
            for(Node*& neighbor : nodePair.second->neighbors) {
                int neighborVal = neighbor->val;
                Node* neighborPtr = cloneMap[neighborVal];
                cloneMap[val]->neighbors.push_back(neighborPtr);
            }
        }

        /*
            return the cloned head
        */
        return cloneMap[head->val];
    }
};

/*
constraints:
- The number of nodes in the graph is in the range [0, 100].
- 1 <= Node.val <= 100
- Node.val is unique for each node.
- There are no repeated edges and no self-loops in the graph.
- The Graph is connected and all nodes can be visited starting from the given node.
*/

// // returns true if the result was the same as expected
// void runSolution(int testNbr, string inStr) {
//     /*
//         create a graph from the input string,
//         use the solution function to create a copy,
//         and ensure the graphs are the same,
//         but not connected,
//         printing the result to the screen
//     */

//     cout << "===========" << endl ;
//     std::cout << "running test number " << testNbr << std::endl;
//     Node* inGraph = string2Graph(inStr);

//     Solution mySolution;
//     Node* clonedGraph = mySolution.cloneGraph(inGraph);
//     std::string cloneString = graph2String(clonedGraph);
//     bool sameGraph = areSame(inGraph, clonedGraph);
//     bool connectedGraph = areConnected(inGraph, clonedGraph);
//     bool fail = false;

//     if(!sameGraph) {
//         fail = true;
//         cout << "Error: not the same graph" << endl;
//     }

//     if(connectedGraph) {
//         fail = true;
//         cout << "Error: the graphs are still connected" << endl;
//     }

//     cout << "input string: " << inStr << endl;
//     cout << "input graph: " << graph2String(inGraph) << endl;
//     cout << "created graph: " << graph2String(clonedGraph) << endl;

//     if(!fail) { 
//         cout << "success" << endl;
//     }

//     cout << "delete graphs" << endl;
//     deleteGraph(inGraph);
//     deleteGraph(clonedGraph);

//     cout << "===========" << endl << endl;
// }

// int main() {
//     try {
//         int i = 1;
//         runSolution(i++, "[[2,4],[1,3],[2,4],[1,3]]");
//         runSolution(i++, "[[2],[1]]");
//         runSolution(i++, "[[2],[1,3],[2]]");
//         runSolution(i++, "[[]]");
//         runSolution(i++, "[]");
//         std::cout << "all done" << std::endl;
//     } catch (std::exception& e) {
//         std::cout << "exception: " << e.what() << std::endl;
//     } catch (const char* s) {
//         std::cout << "exception: " << s << std::endl;
//     }
// }

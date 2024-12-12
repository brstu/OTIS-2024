#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
public:
    string name;
    string content;

    Node(const string& name) : name(name), content("") {}
};

class Edge {
public:
    Node* start;
    Node* end;
    bool directed;

    Edge(Node* start, Node* end, bool directed)
        : start(start), end(end), directed(directed) {}
};

class Graph {
private:
    vector<Node*> nodes;
    vector<Edge*> edges;

public:
    ~Graph() {
        for (Node* node : nodes) {
            delete node;
        }
        for (Edge* edge : edges) {
            delete edge;
        }
    }

    void addNode(const std::string& name) {
        nodes.push_back(new Node(name));
    }

    void removeNode(const std::string& name) {
        auto it = std::remove_if(nodes.begin(), nodes.end(), [&name](Node* node) {
            return node->name == name;
            });
        if (it != nodes.end()) {
            //                 ,                       
            edges.erase(remove_if(edges.begin(), edges.end(), [this, &name](Edge* edge) {
                return edge->start->name == name || edge->end->name == name;
                }), edges.end());
            delete* it; //             
            nodes.erase(it, nodes.end());
        }
    }

    void addEdge(const string& startName, const string& endName, bool directed) {
        Node* startNode = getNode(startName);
        Node* endNode = getNode(endName);
        if (startNode && endNode) {
            edges.push_back(new Edge(startNode, endNode, directed));
        }
    }

    void printInfo() const {
        cout << "Nodes count: " << nodes.size() << "\n";
        for (const auto& node : nodes) {
            cout << "Node: " << node->name << "\n";
        }
        cout << "Edges count: " << edges.size() << "\n";
        for (const auto& edge : edges) {
            cout << "Edge: " << edge->start->name << " -> " << edge->end->name
                << (edge->directed ? " (directed)" : " (undirected)") << "\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << nodes.size() << "\n";
            for (const auto& node : nodes) {
                outFile << node->name << "\n";
            }
            outFile << edges.size() << "\n";
            for (const auto& edge : edges) {
                outFile << edge->start->name << " "
                    << edge->end->name << " "
                    << (edge->directed ? "1" : "0") << "\n";
            }
            outFile.close();
        }
        else {
            cerr << "Unable to open file for writing\n";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            size_t nodeCount, edgeCount;
            inFile >> nodeCount;
            inFile.ignore();
            for (size_t i = 0; i < nodeCount; ++i) {
                string nodeName;
                getline(inFile, nodeName);
                addNode(nodeName);
            }
            inFile >> edgeCount;
            inFile.ignore();
            for (size_t i = 0; i < edgeCount; ++i) {
                string startName, endName;
                int directed;
                inFile >> startName >> endName >> directed;
                addEdge(startName, endName, directed == 1);
            }
            inFile.close();
        }
        else {
            cerr << "Unable to open file for reading\n";
        }
    }

private:
    Node* getNode(const string& name) {
        for (Node* node : nodes) {
            if (node->name == name) {
                return node;
            }
        }
        return nullptr; //               
    }
};

int main() {
    Graph g;

    //                               
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", true);   // A -> B
    g.addEdge("B", "C", false);  // B -- C

    //                         
    g.printInfo();

    //                        
    g.saveToFile("graph.txt");

    //                                          
    Graph g2;
    g2.loadFromFile("graph.txt");

    //                                     
    g2.printInfo();

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class Edge {
public:
    std::string startNode;
    std::string endNode;
    std::string color;
    // Other attributes for edge properties
};

class Node {
public:
    std::string name;
    std::string content;
    std::string color;
    std::string imagePath;
    // Other attributes for node properties
};

class Graph {
private:
    std::string name;
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    // Other attributes for graph properties

public:
    explicit Graph(const std::string& graphName) : name(graphName) {}

    void AddNode(const Node& node) {
        nodes.push_back(node);
    }

    void AddEdge(const Edge& edge) {
        edges.push_back(edge);
    }

    void RemoveNode(const std::string& nodeName) {
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if (it->name == nodeName) {
                nodes.erase(it);
                break;
            }
        }
    }

    void RemoveEdge(const std::string& startNode, const std::string& endNode) {
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if (it->startNode == startNode && it->endNode == endNode) {
                edges.erase(it);
                break;
            }
        }
    }

    void SaveToFile(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file.is_open()) {
            file << "Graph: " << name << std::endl;
            file << "Nodes:" << std::endl;
            for (const auto& node : nodes) {
                file << "Node: " << node.name << ", Content: " << node.content << ", Color: " << node.color << ", Image: " << node.imagePath << std::endl;
            }
            file << "Edges:" << std::endl;
            for (const auto& edge : edges) {
                file << "Edge: " << edge.startNode << " -> " << edge.endNode << ", Color: " << edge.color << std::endl;
            }
            file.close();
        } else {
            std::cout << "Unable to open file" << std::endl;
        }
    }

    void LoadFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                if (line.find("Graph:") == 0) {
                    name = line.substr(7);
                } else if (line.find("Node:") == 0) {
                    Node node;
                    size_t pos = line.find(", Content:");
                    node.name = line.substr(6, pos - 6);
                    node.content = line.substr(pos + 11);
                    pos = line.find(", Color:");
                    node.color = line.substr(pos + 8);
                    pos = line.find(", Image:");
                    node.imagePath = line.substr(pos + 8);
                    nodes.push_back(node);
                } else if (line.find("Edge:") == 0) {
                    Edge edge;
                    size_t pos = line.find(" -> ");
                    edge.startNode = line.substr(6, pos - 6);
                    edge.endNode = line.substr(pos + 4);
                    pos = line.find(", Color:");
                    edge.color = line.substr(pos + 8);
                    edges.push_back(edge);
                }
            }
            file.close();
        } else {
            std::cout << "Unable to open file" << std::endl;
        }
    }

    // Other methods for editing and performing actions on the graph
};

class GraphEditor {
private:
    std::map<std::string, Graph> graphs;

public:
    void CreateGraph(const std::string& graphName) {
        graphs[graphName] = Graph(graphName);
    }

    void DeleteGraph(const std::string& graphName) {
        graphs.erase(graphName);
    }

    void SaveGraph(const std::string& graphName, const std::string& fileName) {
        auto it = graphs.find(graphName);
        if (it != graphs.end()) {
            it->second.SaveToFile(fileName);
        } else {
            std::cout << "Graph not found" << std::endl;
        }
    }

    void LoadGraph(const std::string& graphName, const std::string& fileName) {
        graphs[graphName].LoadFromFile(fileName);
    }

    Graph& GetGraph(const std::string& graphName) {
        return graphs[graphName];
    }

    // Other methods for editing and performing actions on the graphs
};

int main() {
    GraphEditor editor;

    // Example usage
    editor.CreateGraph("MyGraph");
    Node node1 = {"Node1", "Content of Node 1", "Red", "image1.png"};
    Node node2 = {"Node2", "Content of Node 2", "Blue", "image2.png"};
    Edge edge1 = {"Node1", "Node2", "Green"};
    editor.GetGraph("MyGraph").AddNode(node1);
    editor.GetGraph("MyGraph").AddNode(node2);
    editor.GetGraph("MyGraph").AddEdge(edge1);
    editor.SaveGraph("MyGraph", "mygraph.txt");

    return 0;
}
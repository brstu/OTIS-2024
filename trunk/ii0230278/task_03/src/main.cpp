#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

class Node {
public:
    std::string name;
    std::set<std::string> content; // содержание узла, например, текст, ссылки на файл
    Node() : name("") {} // Конструктор по умолчанию
    Node(const std::string &name) : name(name) {}
};

class Edge {
public:
    std::string from;
    std::string to;
    bool directed;

    Edge(const std::string &from, const std::string &to, bool directed) : from(from), to(to), directed(directed) {}
};

class Graph {
private:
    std::string name;
    std::unordered_map<std::string, Node> nodes; // узлы графа
    std::vector<Edge> edges; // ребра графа
    bool directed;

public:
    Graph(const std::string &name, bool directed) : name(name), directed(directed) {}

    void addNode(const std::string &nodeName) {
        nodes[nodeName] = Node(nodeName);
    }

    void addEdge(const std::string &from, const std::string &to) {
        edges.push_back(Edge(from, to, directed));
    }

    void removeNode(const std::string &nodeName) {
        nodes.erase(nodeName);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [nodeName](Edge &edge) {
            return edge.from == nodeName || edge.to == nodeName;
        }), edges.end());
    }

    void removeEdge(const std::string &from, const std::string &to) {
        edges.erase(std::remove_if(edges.begin(), edges.end(), [from, to](Edge &edge) {
            return edge.from == from && edge.to == to;
        }), edges.end());
    }

    void printInfo() const {
        std::cout << "Graph Name: " << name << "\n";
        std::cout << "Nodes: \n";
        for (const auto &node : nodes) {
            std::cout << " - " << node.first << "\n";
        }
        std::cout << "Edges: \n";
        for (const auto &edge : edges) {
            std::cout << " - " << edge.from << (edge.directed ? " -> " : " -- ") << edge.to << "\n";
        }
    }

    int getNodeCount() const {
        return nodes.size();
    }

    int getEdgeCount() const {
        return edges.size();
    }

    const std::string& getName() const {
        return name;
    }
};

// Пример использования
int main() {
    Graph graph("MyGraph", false);  // создание неориентированного графа
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");

    graph.printInfo();

    std::cout << "Node Count: " << graph.getNodeCount() << "\n";
    std::cout << "Edge Count: " << graph.getEdgeCount() << "\n";

    graph.removeEdge("A", "B");
    graph.removeNode("C");

    std::cout << "\nAfter some removals:\n";
    graph.printInfo();

    return 0;
}
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <set>
#include <queue>

class Node {
public:
    std::string name;
    Node(const std::string& name) : name(name) {}
};

class Edge {
public:
    std::shared_ptr<Node> from;
    std::shared_ptr<Node> to;
    bool directed;
    Edge(std::shared_ptr<Node> from, std::shared_ptr<Node> to, bool directed)
            : from(from), to(to), directed(directed) {}
};

class Graph {
private:
    std::string name;
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Edge>> edges;

    std::shared_ptr<Node> findNode(const std::string& name) const {
        for (const auto& node : nodes) {
            if (node->name == name) return node;
        }
        return nullptr;
    }

public:
    Graph(const std::string& name) : name(name) {}

    void addNode(const std::string& nodeName) {
        if (!findNode(nodeName)) {
            nodes.push_back(std::make_shared<Node>(nodeName));
        }
    }

    void addEdge(const std::string& fromName, const std::string& toName, bool directed) {
        auto fromNode = findNode(fromName);
        auto toNode = findNode(toName);
        if (fromNode && toNode) {
            edges.push_back(std::make_shared<Edge>(fromNode, toNode, directed));
        }
    }

    void display() const {
        std::cout << "Graph: " << name << "\nNodes:\n";
        for (const auto& node : nodes) {
            std::cout << " - " << node->name << "\n";
        }
        std::cout << "Edges:\n";
        for (const auto& edge : edges) {
            std::cout << " - " << edge->from->name << (edge->directed ? " -> " : " <-> ") << edge->to->name << "\n";
        }
    }

    bool isConnected() const {
        if (nodes.empty()) return true;

        std::set<std::shared_ptr<Node>> visited;
        std::queue<std::shared_ptr<Node>> q;
        q.push(nodes[0]);

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            if (visited.insert(current).second) { // Insert and check if it was not already present
                for (const auto& edge : edges) {
                    if (edge->from == current && visited.find(edge->to) == visited.end())
                        q.push(edge->to);
                    else if (!edge->directed && edge->to == current && visited.find(edge->from) == visited.end())
                        q.push(edge->from);
                }
            }
        }
        return visited.size() == nodes.size();
    }

    int shortestPath(const std::string& startName, const std::string& endName) {
        if (startName == endName) return 0;

        std::queue<std::pair<std::string, int>> q;
        std::set<std::string> visited;

        q.push({startName, 0});

        while (!q.empty()) {
            auto [current, distance] = q.front();
            q.pop();
            visited.insert(current);

            for (const auto& edge : edges) {
                if (edge->from->name == current && visited.find(edge->to->name) == visited.end()) {
                    if (edge->to->name == endName) return distance + 1;
                    q.push({edge->to->name, distance + 1});
                } else if (!edge->directed && edge->to->name == current && visited.find(edge->from->name) == visited.end()) {
                    if (edge->from->name == endName) return distance + 1;
                    q.push({edge->from->name, distance + 1});
                }
            }
        }
        return -1;
    }
};

int main() {
    Graph graph("MyGraph");

    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addEdge("A", "B", true);
    graph.addEdge("B", "C", true);

    graph.display();


    std::cout << (graph.isConnected() ? "Graph connected.\n" : "Graph isnt connected.\n");


    int distance = graph.shortestPath("A", "C");
    std::cout << (distance != -1 ? "The shortest path between A and C: " + std::to_string(distance) + "\n" : "No way between A and C.\n");

    return 0;
}

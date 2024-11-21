#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

class Node;
class Edge;
class Graph;

class Node {
public:
    Node(std::string name) : name(name) {}
    std::string getName() const { return name; }
    // Функции для редактирования содержимого узла, установки цвета и т. д.

private:
    std::string name;
    // Дополнительные свойства узла
};

class Edge {
public:
    Edge(std::shared_ptr<Node> from, std::shared_ptr<Node> to, bool isDirected = false)
        : from(from), to(to), isDirected(isDirected) {}
    std::shared_ptr<Node> getFrom() const { return from; }
    std::shared_ptr<Node> getTo() const { return to; }
    bool isDirectedEdge() const { return isDirected; }

private:
    std::shared_ptr<Node> from;
    std::shared_ptr<Node> to;
    bool isDirected;
    // Дополнительные свойства рёбер
};

class Graph {
public:
    Graph(std::string name) : name(name) {}
    
    void addNode(const std::string& nodeName) {
        auto node = std::make_shared<Node>(nodeName);
        nodes[nodeName] = node;
        std::cout << "Node " << nodeName << " added.\n";
    }

    void addEdge(const std::string& fromNode, const std::string& toNode, bool isDirected = false) {
        if (nodes.find(fromNode) != nodes.end() && nodes.find(toNode) != nodes.end()) {
            auto edge = std::make_shared<Edge>(nodes[fromNode], nodes[toNode], isDirected);
            edges.push_back(edge);
            std::cout << "Edge from " << fromNode << " to " << toNode << " added.\n";
        } else {
            std::cout << "One or both nodes not found.\n";
        }
    }
    
    void displayGraph() const {
        std::cout << "Graph: " << name << "\nNodes:\n";
        for (typename std::map<std::string, std::shared_ptr<Node>>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
            std::cout << "- " << it->first << "\n";  // it->first — это имя узла
        }

        std::cout << "Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "- " << edge->getFrom()->getName()
                << (edge->isDirectedEdge() ? " -> " : " -- ")
                << edge->getTo()->getName() << "\n";
        }
    }


    // Методы для экспорта, импорта, проверки свойств графа и т. д.

private:
    std::string name;
    std::map<std::string, std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Edge>> edges;
};

void displayMenu() {
    std::cout << "Graph Editor Menu:\n";
    std::cout << "1. Add Node\n";
    std::cout << "2. Add Edge\n";
    std::cout << "3. Display Graph\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    std::unique_ptr<Graph> graph = std::make_unique<Graph>("MyGraph");
    int choice;
    std::string nodeName, fromNode, toNode;
    bool isDirected;

    while (true) {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter node name: ";
                std::cin >> nodeName;
                graph->addNode(nodeName);
                break;
            case 2:
                std::cout << "Enter from node: ";
                std::cin >> fromNode;
                std::cout << "Enter to node: ";
                std::cin >> toNode;
                std::cout << "Is it directed? (1 for Yes, 0 for No): ";
                std::cin >> isDirected;
                graph->addEdge(fromNode, toNode, isDirected);
                break;
            case 3:
                graph->displayGraph();
                break;
            case 4:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

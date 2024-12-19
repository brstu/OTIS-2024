#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

class Vertex {
public:
    std::string id;
    std::set<std::string> content; // Содержание узла, например, текст, ссылки на файл

    Vertex() : id("") {} // Конструктор по умолчанию
    Vertex(const std::string& id) : id(id) {}
};

class Link {
public:
    std::string source;
    std::string destination;
    bool isDirected;

    Link(const std::string& source, const std::string& destination, bool isDirected)
        : source(source), destination(destination), isDirected(isDirected) {}
};

class Network {
private:
    std::string title;
    std::unordered_map<std::string, Vertex> vertices; // Узлы сети
    std::vector<Link> links; // Ребра сети
    bool directed;

public:
    Network(const std::string& title, bool directed) : title(title), directed(directed) {}

    void insertVertex(const std::string& vertexId) {
        vertices[vertexId] = Vertex(vertexId);
    }

    void insertLink(const std::string& source, const std::string& destination) {
        links.push_back(Link(source, destination, directed));
    }

    void deleteVertex(const std::string& vertexId) {
        vertices.erase(vertexId);
        links.erase(std::remove_if(links.begin(), links.end(), [vertexId](Link& link) {
            return link.source == vertexId || link.destination == vertexId;
            }), links.end());
    }

    void deleteLink(const std::string& source, const std::string& destination) {
        links.erase(std::remove_if(links.begin(), links.end(), [source, destination](Link& link) {
            return link.source == source && link.destination == destination;
            }), links.end());
    }

    void displayInfo() const {
        std::cout << "Network Title: " << title << "\n";
        std::cout << "Vertices: \n";
        for (const auto& vertex : vertices) {
            std::cout << " - " << vertex.first << "\n";
        }
        std::cout << "Links: \n";
        for (const auto& link : links) {
            std::cout << " - " << link.source << (link.isDirected ? " -> " : " -- ") << link.destination << "\n";
        }
    }

    int getVertexCount() const {
        return vertices.size();
    }

    int getLinkCount() const {
        return links.size();
    }

    const std::string& getTitle() const {
        return title;
    }
};

// Пример использования
int main() {
    Network network("MyNetwork", false); // Создание неориентированной сети
    network.insertVertex("A");
    network.insertVertex("B");
    network.insertVertex("C");
    network.insertLink("A", "B");
    network.insertLink("B", "C");

    network.displayInfo();

    std::cout << "Vertex Count: " << network.getVertexCount() << "\n";
    std::cout << "Link Count: " << network.getLinkCount() << "\n";

    network.deleteLink("A", "B");
    network.deleteVertex("C");

    std::cout << "\nAfter some removals:\n";
    network.displayInfo();

    return 0;
}

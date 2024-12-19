#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm>

class Vertex {
public:
    std::string label;
    std::string data;  // Текстовое содержимое узла
    std::string link;  // Ссылка на файл

    Vertex() = default;
    Vertex(const std::string& vertexName) : label(vertexName) {}
};

class Connection {
public:
    std::string start;
    std::string end;
    bool isDirected;

    Connection(const std::string& start, const std::string& end, bool isDirected = false)
        : start(start), end(end), isDirected(isDirected) {}
};

class Network {
public:
    std::string graphName;
    bool directed;
    std::unordered_map<std::string, Vertex> vertices;
    std::vector<Connection> connections;

    Network(const std::string& name, bool directed)
        : graphName(name), directed(directed) {}

    void addVertex(const std::string& vertexName) {
        if (vertices.find(vertexName) == vertices.end()) {
            vertices[vertexName] = Vertex(vertexName);
            std::cout << "Vertex " << vertexName << " added.\n";
        }
        else {
            std::cout << "Vertex " << vertexName << " already exists.\n";
        }
    }

    void deleteVertex(const std::string& vertexName) {
        if (vertices.erase(vertexName)) {
            connections.erase(std::remove_if(connections.begin(), connections.end(), [&](Connection& connection) {
                return connection.start == vertexName || connection.end == vertexName;
                }), connections.end());
            std::cout << "Vertex " << vertexName << " removed.\n";
        }
        else {
            std::cout << "Vertex " << vertexName << " does not exist.\n";
        }
    }

    void addConnection(const std::string& from, const std::string& to) {
        if (vertices.find(from) != vertices.end() && vertices.find(to) != vertices.end()) {
            connections.emplace_back(from, to, directed);
            std::cout << "Connection from " << from << " to " << to << " added.\n";
        }
        else {
            std::cout << "One or both vertices do not exist.\n";
        }
    }

    void deleteConnection(const std::string& from, const std::string& to) {
        connections.erase(std::remove_if(connections.begin(), connections.end(), [&](Connection& connection) {
            return connection.start == from && connection.end == to;
            }), connections.end());
        std::cout << "Connection from " << from << " to " << to << " removed.\n";
    }

    void saveNetwork(const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << graphName << " : " << (directed ? "DIRECTED" : "UNDIRECTED") << " ;\n";
            for (const auto& vertexPair : vertices) {
                outFile << vertexPair.first << " ";
            }
            outFile << ";\n";
            for (const auto& connection : connections) {
                outFile << connection.start << " -> " << connection.end << (directed ? " ;" : " ");
            }
            outFile.close();
            std::cout << "Network saved to " << filename << "\n";
        }
        else {
            std::cout << "Error opening file for saving.\n";
        }
    }

    void loadNetwork(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            vertices.clear();
            connections.clear();
            std::string line;
            getline(inFile, line);
            size_t pos = line.find(" : ");
            graphName = line.substr(0, pos);
            directed = line.find("DIRECTED") != std::string::npos;

            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(',')) != std::string::npos) {
                std::string vertexName = line.substr(0, pos);
                addVertex(vertexName);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addVertex(line);

            getline(inFile, line);
            while ((pos = line.find("->")) != std::string::npos) {
                std::string from = line.substr(0, pos);
                line.erase(0, pos + 2);
                pos = line.find(',');
                std::string to = line.substr(0, pos);
                addConnection(from, to);
                if (pos == std::string::npos) break;
                line.erase(0, pos + 1);
            }
            inFile.close();
            std::cout << "Network loaded from " << filename << "\n";
        }
        else {
            std::cout << "Error opening file for loading.\n";
        }
    }

    void showInfo() {
        std::cout << "Graph: " << graphName << "\n";
        std::cout << "Number of vertices: " << vertices.size() << "\n";
        std::cout << "Number of connections: " << connections.size() << "\n";
    }

    void renderGraph() {
        std::cout << "\n--- ASCII Network Representation ---\n";
        for (const auto& connection : connections) {
            std::cout << std::setw(2) << connection.start << " --> " << connection.end << "\n";
            if (!directed) {
                std::cout << std::setw(2) << connection.end << " --> " << connection.start << "\n";
            }
        }
        std::cout << "-------------------------------------\n";
    }
};

void displayMenu() {
    std::cout << "\n--- Network Editor Menu ---\n";
    std::cout << "1. Add Vertex\n";
    std::cout << "2. Remove Vertex\n";
    std::cout << "3. Add Connection\n";
    std::cout << "4. Remove Connection\n";
    std::cout << "5. Show Network Info\n";
    std::cout << "6. Save Network\n";
    std::cout << "7. Load Network\n";
    std::cout << "8. Render Network\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Network network("ExampleNetwork", true);
    int choice;
    std::string vertexName, fromVertex, toVertex, filename;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка буфера ввода

        switch (choice) {
        case 1:
            std::cout << "Enter vertex name: ";
            std::getline(std::cin, vertexName);
            network.addVertex(vertexName);
            break;

        case 2:
            std::cout << "Enter vertex name to remove: ";
            std::getline(std::cin, vertexName);
            network.deleteVertex(vertexName);
            break;

        case 3:
            std::cout << "Enter the 'from' vertex: ";
            std::getline(std::cin, fromVertex);
            std::cout << "Enter the 'to' vertex: ";
            std::getline(std::cin, toVertex);
            network.addConnection(fromVertex, toVertex);
            break;

        case 4:
            std::cout << "Enter the 'from' vertex to remove: ";
            std::getline(std::cin, fromVertex);
            std::cout << "Enter the 'to' vertex to remove: ";
            std::getline(std::cin, toVertex);
            network.deleteConnection(fromVertex, toVertex);
            break;

        case 5:
            network.showInfo();
            break;

        case 6:
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            network.saveNetwork(filename);
            break;

        case 7:
            std::cout << "Enter filename to load: ";
            std::getline(std::cin, filename);
            network.loadNetwork(filename);
            break;

        case 8:
            network.renderGraph();
            break;

        case 9:
            std::cout << "Exiting program.\n";
            return 0;

        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}

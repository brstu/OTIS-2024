<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Применение знаний алгоритмов для графов на практике”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Мохорева Т. Д.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и с помощью запроса на внесение изменений (pull request) разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc (где xx - номер группы, yy - номер студента, например ii02302)..
2. Исходный код разработанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
## Задание ##
Задание. Разработать и реализовать программный продукт, позволяющий редактировать графовые конструкции различных видов и производить над ними различные действия. Язык программирования - **C++**.

<hr>

# Выполнение задания #

Код программы:
```#include <iostream>
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


```     
```

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 1
Enter vertex name: A
Vertex A added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 1
Enter vertex name: B
Vertex B added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 1
Enter vertex name: C
Vertex C added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 3
Enter the 'from' vertex: A
Enter the 'to' vertex: B
Connection from A to B added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 3
Enter the 'from' vertex: A
Enter the 'to' vertex: C
Connection from A to C added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 1
Enter vertex name: D
Vertex D added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 3
Enter the 'from' vertex: C
Enter the 'to' vertex: D
Connection from C to D added.

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 5
Graph: ExampleNetwork
Number of vertices: 4
Number of connections: 3

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 8

--- ASCII Network Representation ---
 A --> B
 A --> C
 C --> D
-------------------------------------

--- Network Editor Menu ---
1. Add Vertex
2. Remove Vertex
3. Add Connection
4. Remove Connection
5. Show Network Info
6. Save Network
7. Load Network
8. Render Network
9. Exit
Choose an option: 9
Exiting program.
```


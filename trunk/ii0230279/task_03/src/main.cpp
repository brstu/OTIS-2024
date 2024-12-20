#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm>

class Node {
public:
    std::string id;       // ������������� ����
    std::string data;     // ������ ��������� ����������
    std::string link;     // ������ �� ��������� ����

    Node() = default; // ����������� �� ���������
    Node(const std::string& nodeId) : id(nodeId) {} // ����������� � ����������
};

class Connection {
public:
    std::string startNode; // ��������� ����
    std::string endNode;   // �������� ����
    bool isDirected;       // ���� �������������� ����������

    Connection(const std::string& start, const std::string& end, bool directed = false)
        : startNode(start), endNode(end), isDirected(directed) {}
};

class NetworkGraph {
public:
    std::string graphName;      // �������� �����
    bool directedGraph;         // �������� �� ���� ������������
    std::unordered_map<std::string, Node> theNodes;  // ������� �����
    std::vector<Connection> theConnections;            // ������ ����������

    // ����������� ��� �������� ������ �����
    NetworkGraph(const std::string& name, bool isDirected)
        : graphName(name), directedGraph(isDirected) {}

    // ����� ��� ���������� ����
    void addNode(const std::string& nodeId) {
        if (theNodes.find(nodeId) == theNodes.end()) { // �������� ������������� ����
            theNodes[nodeId] = Node(nodeId);
            std::cout << "���� " << nodeId << " ������� ������.\n";
        }
        else {
            std::cout << "���� " << nodeId << " ��� ����������.\n";
        }
    }

    // ����� ��� �������� ����
    void removeNode(const std::string& nodeId) {
        if (theNodes.erase(nodeId)) { // ���� ���� ��� ������ � ������
            // �������� ���� ����������, � ������� ��������� ������ ����
            theConnections.erase(std::remove_if(theConnections.begin(), theConnections.end(), [&](Connection& conn) {
                return conn.startNode == nodeId || conn.endNode == nodeId;
                }), theConnections.end());

            std::cout << "���� " << nodeId << " ������� ������.\n";
        }
        else {
            std::cout << "���� " << nodeId << " �� ������.\n";
        }
    }

    // ����� ��� ���������� ���������� ����� ������
    void addConnection(const std::string& start, const std::string& end) {
        if (theNodes.find(start) != theNodes.end() && theNodes.find(end) != theNodes.end()) {
            theConnections.emplace_back(start, end, directedGraph);
            std::cout << "���������� �� " << start << " � " << end << " ������� ���������.\n";
        }
        else {
            std::cout << "���� ��� ��� ���� �����������.\n";
        }
    }

    // ����� ��� �������� ����������
    void removeConnection(const std::string& start, const std::string& end) {
        theConnections.erase(std::remove_if(theConnections.begin(), theConnections.end(), [&](Connection& conn) {
            return conn.startNode == start && conn.endNode == end;
            }), theConnections.end());
        std::cout << "���������� �� " << start << " � " << end << " ������� �������.\n";
    }

    // ����� ��� ���������� ����� � ����
    void saveGraphToFile(const std::string& fileName) {
        std::ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << graphName << " : " << (directedGraph ? "DIRECTED" : "UNDIRECTED") << " ;\n";

            // ���������� ���� � ����
            for (const auto& nodePair : theNodes) {
                outFile << nodePair.first << " "; // ������ �������� ����
            }
            outFile << ";\n";

            // ���������� ���������� � ����
            for (const auto& conn : theConnections) {
                outFile << conn.startNode << " -> " << conn.endNode;
                // ��������� ��������������
                if (directedGraph) {
                    outFile << " ;";
                }
                else {
                    outFile << " ";
                }
            }

            outFile.close(); // �������� �����
            std::cout << "���� ������� �������� � " << fileName << "\n";
        }
        else {
            std::cout << "������ ��� �������� ����� ��� ����������.\n";
        }
    }

    // ����� ��� �������� ����� �� �����
    void loadGraphFromFile(const std::string& fileName) {
        std::ifstream inFile(fileName);
        if (inFile.is_open()) {
            theNodes.clear();       // ������� �����
            theConnections.clear();  // ������� ����������

            std::string line;
            getline(inFile, line);  // ������ �������� �����
            size_t pos = line.find(" : ");
            graphName = line.substr(0, pos);
            directedGraph = line.find("DIRECTED") != std::string::npos; // ����������� �������������� �����

            // ������ ����
            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(' ')) != std::string::npos) {
                std::string nodeName = line.substr(0, pos);
                addNode(nodeName);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addNode(line); // ��������� ��������� ����

            // ������ ����������
            getline(inFile, line);
            while ((pos = line.find("->")) != std::string::npos) {
                std::string start = line.substr(0, pos);
                line.erase(0, pos + 2);
                pos = line.find(';');
                std::string end = line.substr(0, pos);
                addConnection(start, end);
                if (pos == std::string::npos) break;
                line.erase(0, pos + 1);
            }
            inFile.close(); // ��������� ����
            std::cout << "���� ������� �������� �� " << fileName << "\n";
        }
        else {
            std::cout << "������ ��� �������� ����� ��� ��������.\n";
        }
    }

    // ����� ��� ����������� ���������� � �����
    void displayGraphInfo() {
        std::cout << "�������� �����: " << graphName << "\n";
        std::cout << "���������� �����: " << theNodes.size() << "\n";
        std::cout << "���������� ����������: " << theConnections.size() << "\n";
    }

    // ����� ��� ������������ ����� � ���� ASCII-���
    void visualizeGraph() {
        std::cout << "\n--- ASCII ������������ ����� ---\n";
        for (const auto& conn : theConnections) {
            std::cout << std::setw(2) << conn.startNode << " --> " << conn.endNode << "\n"; // ��� ������� ������ ����������
            if (!directedGraph) {
                std::cout << std::setw(2) << conn.endNode << " --> " << conn.startNode << "\n"; // ��������� �������� ���������� ��� �������������� �����
            }
        }
        std::cout << "----------------------------------\n";
    }
};

// ������� ��� ����������� ����
void showMainMenu() {
    std::cout << "\n--- ���� ��������� ������ ---\n";
    std::cout << "1. ������� ����\n";
    std::cout << "2. ������� ����\n";
    std::cout << "3. ������� ����������\n";
    std::cout << "4. ������� ����������\n";
    std::cout << "5. �������� ���������� � �����\n";
    std::cout << "6. ��������� ���� � ����\n";
    std::cout << "7. ��������� ���� �� �����\n";
    std::cout << "8. ��������������� ����\n";
    std::cout << "9. ����� �� ����������\n";
    std::cout << "�������� �����: ";
}

int main() {
    NetworkGraph myGraph("MyNetwork", true); // ������� ������ �����
    int userChoice;                          // ���������� ��� ������ �������������
    std::string nodeName, startNode, endNode, fileName;

    while (true) {
        showMainMenu(); // ���������� ����
        std::cin >> userChoice; // �������� ����� ������������
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ����� �����

        switch (userChoice) {
        case 1: // ���������� ����
            std::cout << "������� �������� ����: ";
            std::getline(std::cin, nodeName);
            myGraph.addNode(nodeName);
            break;

        case 2: // �������� ����
            std::cout << "������� �������� ���� ��� ��������: ";
            std::getline(std::cin, nodeName);
            myGraph.removeNode(nodeName);
            break;

        case 3: // ���������� ����������
            std::cout << "������� ��������� ����: ";
            std::getline(std::cin, startNode);
            std::cout << "������� �������� ����: ";
            std::getline(std::cin, endNode);
            myGraph.addConnection(startNode, endNode);
            break;

        case 4: // �������� ����������
            std::cout << "������� ��������� ���� ��� �������� ����������: ";
            std::getline(std::cin, startNode);
            std::cout << "������� �������� ���� ��� �������� ����������: ";
            std::getline(std::cin, endNode);
            myGraph.removeConnection(startNode, endNode);
            break;

        case 5: // ����������� ���������� � �����
            myGraph.displayGraphInfo();
            break;

        case 6: // ���������� �����
            std::cout << "������� ��� ����� ��� ����������: ";
            std::getline(std::cin, fileName);
            myGraph.saveGraphToFile(fileName);
            break;

        case 7: // �������� �����
            std::cout << "������� ��� ����� ��� ��������: ";
            std::getline(std::cin, fileName);
            myGraph.loadGraphFromFile(fileName);
            break;

        case 8: // ������������ �����
            myGraph.visualizeGraph();
            break;

        case 9: // ���������� ������ ���������
            std::cout << "����� �� ���������.\n";
            return 0;

        default: // ��������� ������������� �����
            std::cout << "������������ ����. ���������� �����.\n";
            break;
        }
    }

    return 0; // ���������� ���������
}
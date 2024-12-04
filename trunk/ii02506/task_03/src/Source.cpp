#include <iostream>
#include <fstream>
#include <vector>
#include "GraphAlgorithms.h"

using namespace std;

int main() {
    string fileName;
    cout << "Enter the file name containing graph data: ";
    cin >> fileName;

    ifstream fileInput(fileName);
    int vertexCount, edgeCount;
    fileInput >> vertexCount >> edgeCount;

    int** graphMatrix = new int*[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        graphMatrix[i] = new int[vertexCount];
    }

    vector<bool> visited(vertexCount);
    int* path = new int[vertexCount];
    int* helperArray = new int[vertexCount];

    int menuOption;
    do {
        cout << "Menu:\n";
        cout << "1. Initialize Graph\n";
        cout << "2. Display Graph\n";
        cout << "3. BFS\n";
        cout << "4. DFS\n";
        cout << "9. Prim's Algorithm\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> menuOption;

        switch (menuOption) {
            case 1:
                initializeGraph(graphMatrix, vertexCount, edgeCount, fileName);
                break;

            case 2:
                displayGraph(graphMatrix, vertexCount);
                break;

            case 3:
                fill(visited.begin(), visited.end(), false);
                for (int i = 0; i < vertexCount; ++i) {
                    if (!visited[i]) {
                        breadthFirstSearch(graphMatrix, vertexCount, i, visited);
                    }
                }
                cout << endl;
                break;

            case 4:
                fill(visited.begin(), visited.end(), false);
                for (int i = 0; i < vertexCount; ++i) {
                    if (!visited[i]) {
                        depthFirstSearch(graphMatrix, vertexCount, i, visited);
                    }
                }
                cout << endl;
                break;

            case 9:
                primAlgorithm(graphMatrix, vertexCount);
                break;
        }
    } while (menuOption != 0);

    // Очистка памяти
    for (int i = 0; i < vertexCount; ++i) {
        delete[] graphMatrix[i];
    }
    delete[] graphMatrix;
    delete[] path;
    delete[] helperArray;

    return 0;
}

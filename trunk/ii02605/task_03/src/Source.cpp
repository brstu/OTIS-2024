#include <iostream>
#include <fstream>
#include <vector>
#include "header.h"

using namespace std;

int main()
{
    string fileName;
    cout << "Enter file's name: ";
    cin >> fileName;
    ifstream inputFile(fileName);
    int vertexCount, edgesCount;
    inputFile >> vertexCount >> edgesCount;

    // Инициализация матрицы смежности
    int** adjacencyMatrix = new int* [vertexCount];
    for (int i = 0; i < vertexCount; i++)
        adjacencyMatrix[i] = new int[vertexCount];

    // Вектор для отслеживания посещенных вершин
    vector<bool> visited(vertexCount, false);
    int res;
    int* path = new int[vertexCount];
    int* visitedStatus = new int[vertexCount];

    // Меню
    int choice;
    do
    {
        cout << "1. Fill Matrix\n";
        cout << "2. Paint Matrix\n";
        cout << "\nLab 1\n3. BFS\n";
        cout << "4. DFS\n";
        cout << "\nLab 2\n5. Hamiltonian Cycle\n";
        cout << "6. Eulerian Cycle\n";
        cout << "\nLab 3\n7. Dijkstra\n";
        cout << "8. Floyd-Warshall\n";
        cout << "\nLab 5\n9. Prim's Algorithm\n";
        cout << "10. Kruskal's Algorithm\n";
        cout << "\nLab 4\n11. Kali Algorithm\n";
        cout << "12. Generate Permutation\n";
        cout << "\nLab 6\n13. Strong Connectivity\n";
        cout << "14. Biconnected Components\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Fill Matrix
            system("cls");
            fillMatrix(adjacencyMatrix, vertexCount, edgesCount, fileName);
            break;

        case 2: // Paint Matrix
            system("cls");
            paintMatrix(adjacencyMatrix, vertexCount);
            break;

        case 3: // BFS
            system("cls");
            res = 0;
            for (int i = 0; i < vertexCount; i++)
                if (!visited[i])
                {
                    res++;
                    breadthFirstSearch(adjacencyMatrix, vertexCount, i, visited);
                }
            cout << endl << "Number of connectivity components: " << res << endl;
            break;

        case 4: // DFS
            system("cls");
            res = 0;
            for (int i = 0; i < vertexCount; i++)
                if (!visited[i])
                {
                    res++;
                    depthFirstSearch(adjacencyMatrix, vertexCount, i, visited);
                }
            cout << endl << "Number of connectivity components: " << res << endl;
            break;

        case 5: // Hamiltonian Cycle
            system("cls");
            int startVertex;
            cout << "Enter first vertex: ";
            cin >> startVertex;
            startVertex--;
            for (int i = 0; i < vertexCount; i++)
                visitedStatus[i] = -1;
            visitedStatus[startVertex] = startVertex;
            path[0] = startVertex;
            if (findHamiltonianCycle(adjacencyMatrix, path, visitedStatus, vertexCount, 1, startVertex))
            {
                printPath(path, vertexCount);
                cout << endl;
            }
            else
                cout << "No Hamiltonian Cycle found\n";
            break;

        case 6: // Eulerian Cycle
            system("cls");
            if (res > 1)
                cout << "Graph is not connected. Cannot find Eulerian Cycle.\n";
            else
            {
                int oddDegreeCount = 0;
                int buf;
                for (int i = 0; i < vertexCount; i++)
                {
                    buf = 0;
                    for (int j = 0; j < vertexCount; j++)
                        buf += adjacencyMatrix[i][j];
                    if (buf % 2 != 0)
                        oddDegreeCount++;
                }
                if (oddDegreeCount > 0)
                    cout << "Graph doesn't have an Eulerian Cycle.\n";
                else
                {
                    vector<int> eulerPath;
                    findEulerianCycle(adjacencyMatrix, eulerPath, vertexCount);
                    for (int i = 1; i < eulerPath.size(); i++)
                        cout << eulerPath[i] + 1 << " ";
                    cout << endl;
                }
            }
            break;

        case 7: // Dijkstra
            system("cls");
            applyDijkstraAlgorithm(adjacencyMatrix, vertexCount);
            break;

        case 8: // Floyd-Warshall
            system("cls");
            applyFloydWarshallAlgorithm(adjacencyMatrix, vertexCount);
            break;

        case 9: // Prim's Algorithm
            system("cls");
            applyPrimAlgorithm(adjacencyMatrix, vertexCount);
            break;

        case 10: // Kruskal's Algorithm
            system("cls");
            applyKruskalAlgorithm(adjacencyMatrix, vertexCount, edgesCount, fileName);
            break;

        case 11: // Kali Algorithm
            system("cls");
            runKaliAlgorithm();
            break;

        case 12: // Generate Permutation
            system("cls");
            generatePermutation(fileName);
            break;

        case 13: // Strong Connectivity
            system("cls");
            findStronglyConnectedComponents(adjacencyMatrix, vertexCount);
            break;

        case 14: // Biconnected Components
            system("cls");
            findBiconnectedComponents(adjacencyMatrix, vertexCount);
            break;

        case 0: // Exit
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    // Очистка памяти
    for (int i = 0; i < vertexCount; i++)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;
    delete[] path;
    delete[] visitedStatus;

    return 0;
}

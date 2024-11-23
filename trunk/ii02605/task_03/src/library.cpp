#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 10000;

void depthFirstSearch(int** adjacencyMatrix, int numVertices, int startVertex, vector<bool>& visitedNodes) // Поиск в глубину
{
    cout << endl;
    stack<int> searchStack;
    searchStack.push(startVertex);
    while (!searchStack.empty())
    {
        startVertex = searchStack.top();
        searchStack.pop();
        if (visitedNodes[startVertex])
            continue;
        visitedNodes[startVertex] = true;
        cout << startVertex + 1;
        for (int i = 0; i < numVertices; i++)
            if (!visitedNodes[i] && adjacencyMatrix[startVertex][i])
                searchStack.push(i);
    }
}

void breadthFirstSearch(int** adjacencyMatrix, int numVertices, int startVertex, vector<bool>& visitedNodes) // Поиск в ширину
{
    cout << endl;
    queue<int> searchQueue;
    searchQueue.push(startVertex);
    visitedNodes[startVertex] = true;
    while (!searchQueue.empty())
    {
        int vertex = searchQueue.front();
        searchQueue.pop();
        cout << vertex + 1 << " ";
        for (int i = 0; i < numVertices; i++)
        {
            if (!visitedNodes[i] && adjacencyMatrix[vertex][i])
            {
                searchQueue.push(i);
                visitedNodes[i] = true;
            }
        }
    }
}

void loadGraph(int**& adjacencyMatrix, int numVertices, int numEdges, string filename)
{
    ifstream inputFile(filename);
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            adjacencyMatrix[i][j] = false;
    int temp1, temp2;
    inputFile >> temp1 >> temp2;
    for (int i = 0; i < numEdges; i++)
    {
        int u, v, w;
        inputFile >> u >> v >> w;
        cout << u << " -> " << v << endl;
        u--; v--;
        adjacencyMatrix[u][v] = w;
    }
}

void displayMatrix(int**& adjacencyMatrix, int numVertices)
{
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
            cout << adjacencyMatrix[i][j] << " ";
        cout << endl;
    }
}

void displayPath(int*& path, int numVertices)
{
    for (int i = 0; i < numVertices; i++)
        cout << path[i] + 1 << " ";
    cout << path[0] + 1;
}

bool findHamiltonianCycle(int**& adjacencyMatrix, int*& path, int*& visitedNodes, int numVertices, int step, int startVertex)
{
    bool result = false;
    for (int i = 0; i < numVertices; i++)
    {
        if (adjacencyMatrix[i][path[step - 1]])
        {
            if (step == numVertices && i == startVertex)
                result = true;
            else if (visitedNodes[i] == -1)
            {
                visitedNodes[i] = step;
                path[step] = i;
                result = findHamiltonianCycle(adjacencyMatrix, path, visitedNodes, numVertices, step + 1, startVertex);
                if (!result) visitedNodes[i] = -1;
            }
        }
    }
    return result;
}

void findEulerianCycle(int**& adjacencyMatrix, vector<int>& path, int numVertices)
{
    int* vertexDegree = new int[numVertices];
    for (int i = 0; i < numVertices; i++)
        vertexDegree[i] = NULL;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (adjacencyMatrix[i][j])
                vertexDegree[i]++;
    stack<int> dfsStack;
    dfsStack.push(0);
    path.push_back(0);
    while (!dfsStack.empty())
    {
        int vertex = dfsStack.top();
        if (vertexDegree[vertex] == NULL)
        {
            dfsStack.pop();
            path.push_back(vertex);
        }
        else
        {
            for (int i = 0; i < numVertices; i++)
                if (adjacencyMatrix[vertex][i])
                {
                    adjacencyMatrix[vertex][i] = NULL;
                    adjacencyMatrix[i][vertex] = NULL;
                    vertexDegree[vertex]--;
                    vertexDegree[i]--;
                    dfsStack.push(i);
                    break;
                }
        }
    }
}

void applyDijkstraAlgorithm(int**& adjacencyMatrix, int numVertices)
{
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
        {
            if (adjacencyMatrix[i][j] == NULL)
                adjacencyMatrix[i][j] = INF;
        }
    vector<int> dist(numVertices, INF);
    vector<bool> visitedNodes(numVertices, false);
    vector<int> previousNodes(numVertices, -1);

    dist[0] = NULL;
    visitedNodes[0] = true;
    previousNodes[0] = NULL;

    for (int i = 0; i < numVertices; i++)
        if (adjacencyMatrix[0][i] <= dist[i])
        {
            dist[i] = adjacencyMatrix[0][i];
            previousNodes[i] = NULL;
        }

    for (int i = 0; i < numVertices - 1; i++)
    {
        int min = INF;
        for (int j = 0; j < dist.size(); j++)
            if (min > dist[j] && !visitedNodes[j])
                min = j;
        int minDist = dist[min];
        visitedNodes[min] = true;

        for (int j = 0; j < numVertices; j++)
        {
            if (!visitedNodes[j] && dist[j] > adjacencyMatrix[min][j] + minDist && minDist > 0)
            {
                dist[j] = adjacencyMatrix[min][j] + minDist;
                previousNodes[j] = min;
            }
        }
    }
    for (int i = 0; i < numVertices; i++) {
        cout << i + 1 << "\t" << dist[i] << "\t" << previousNodes[i] + 1 << endl;
    }
}

void applyFloydWarshallAlgorithm(int**& adjacencyMatrix, int numVertices)
{
    int** temp = adjacencyMatrix;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
        {
            if (i == j) temp[i][j] = NULL;
            else if (adjacencyMatrix[i][j]) temp[i][j] = adjacencyMatrix[i][j];
            else temp[i][j] = INF;
        }
    for (int k = 0; k < numVertices; k++)
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                if (temp[i][j] > temp[i][k] + temp[k][j])
                    temp[i][j] = temp[i][k] + temp[k][j];
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
            cout << temp[i][j] << "\t";
        cout << endl;
    }
}

void applyPrimAlgorithm(int**& adjacencyMatrix, int numVertices)
{
    bool* selectedVertices = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        selectedVertices[i] = false;
    selectedVertices[0] = true;
    int searchCount = NULL;
    int column = 0, row = 0;
    int weight = NULL;
    while (searchCount < numVertices - 1)
    {
        int min = INF;
        for (int i = 0; i < numVertices; i++)
            if (selectedVertices[i])
                for (int j = 0; j < numVertices; j++)
                    if (!selectedVertices[j] && adjacencyMatrix[i][j])
                        if (min > adjacencyMatrix[i][j])
                        {
                            min = adjacencyMatrix[i][j];
                            row = i;
                            column = j;
                        }
        cout << row + 1 << " -> " << column + 1 << " = " << min;
        searchCount++;
        weight += min;
        cout << endl;
        selectedVertices[column] = true;
    }
    cout << "Total weight is " << weight << endl;
}

int findParent(int* root, int a)
{
    while (root[a] != a)
    {
        root[a] = root[root[a]];
        a = root[a];
    }
    return a;
}

void performUnion(int* root, int a, int b)
{
    int d = findParent(root, a);
    int e = findParent(root, b);
    root[d] = root[e];
}

int applyKruskalAlgorithm(pair<int, pair<int, int>>* edges, int* root, int**& adjacencyMatrix, int numVertices, int numEdges)
{
    int minCost = NULL;

    for (int i = 0; i < numEdges; i++)
    {
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        int cost = edges[i].first;
        if (findParent(root, a) != findParent(root, b))
        {
            performUnion(root, a, b);
            adjacencyMatrix[a][b] = cost;
            adjacencyMatrix[b][a] = cost;
            minCost += cost;
        }
    }
    return minCost;
}

int main()
{
    int numVertices, numEdges;
    cout << "Enter number of vertices and edges: ";
    cin >> numVertices >> numEdges;

    // Инициализация матрицы смежности
    int** adjacencyMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; i++)
        adjacencyMatrix[i] = new int[numVertices];

    // Загрузка графа из файла
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    loadGraph(adjacencyMatrix, numVertices, numEdges, filename);

    // Вывод матрицы смежности
    cout << "Adjacency Matrix:" << endl;
    displayMatrix(adjacencyMatrix, numVertices);

    // Выбор алгоритма для выполнения
    cout << "Choose an algorithm to run:" << endl;
    cout << "1. Depth First Search (DFS)" << endl;
    cout << "2. Breadth First Search (BFS)" << endl;
    cout << "3. Find Hamiltonian Cycle" << endl;
    cout << "4. Find Eulerian Cycle" << endl;
    cout << "5. Dijkstra Algorithm" << endl;
    cout << "6. Floyd-Warshall Algorithm" << endl;
    cout << "7. Prim Algorithm" << endl;
    cout << "8. Kruskal Algorithm" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1: {
        vector<bool> visited(numVertices, false);
        int startVertex;
        cout << "Enter start vertex for DFS: ";
        cin >> startVertex;
        startVertex--; // Индексы начинаются с 0
        depthFirstSearch(adjacencyMatrix, numVertices, startVertex, visited);
        break;
    }
    case 2: {
        vector<bool> visited(numVertices, false);
        int startVertex;
        cout << "Enter start vertex for BFS: ";
        cin >> startVertex;
        startVertex--; // Индексы начинаются с 0
        breadthFirstSearch(adjacencyMatrix, numVertices, startVertex, visited);
        break;
    }
    case 3: {
        int* path = new int[numVertices];
        int* visitedNodes = new int[numVertices];
        for (int i = 0; i < numVertices; i++)
            visitedNodes[i] = -1; // Отметки для посещенных вершин
        int startVertex;
        cout << "Enter start vertex for Hamiltonian Cycle: ";
        cin >> startVertex;
        startVertex--; // Индексы начинаются с 0
        path[0] = startVertex;
        visitedNodes[startVertex] = 0;

        if (findHamiltonianCycle(adjacencyMatrix, path, visitedNodes, numVertices, 1, startVertex)) {
            cout << "Hamiltonian Cycle found: ";
            displayPath(path, numVertices);
        }
        else {
            cout << "No Hamiltonian Cycle found." << endl;
        }
        break;
    }
    case 4: {
        vector<int> path;
        cout << "Eulerian Cycle: ";
        findEulerianCycle(adjacencyMatrix, path, numVertices);
        displayPath(path.data(), path.size());
        break;
    }
    case 5: {
        applyDijkstraAlgorithm(adjacencyMatrix, numVertices);
        break;
    }
    case 6: {
        applyFloydWarshallAlgorithm(adjacencyMatrix, numVertices);
        break;
    }
    case 7: {
        applyPrimAlgorithm(adjacencyMatrix, numVertices);
        break;
    }
    case 8: {
        int numEdges;
        cout << "Enter the number of edges for Kruskal: ";
        cin >> numEdges;
        pair<int, pair<int, int>>* edges = new pair<int, pair<int, int>>[numEdges];
        int* root = new int[numVertices];
        for (int i = 0; i < numVertices; i++)
            root[i] = i;

        cout << "Enter edges in the format: weight vertex1 vertex2:" << endl;
        for (int i = 0; i < numEdges; i++) {
            int weight, vertex1, vertex2;
            cin >> weight >> vertex1 >> vertex2;
            vertex1--; vertex2--; // Индексы начинаются с 0
            edges[i] = make_pair(weight, make_pair(vertex1, vertex2));
        }

        int minCost = applyKruskalAlgorithm(edges, root, adjacencyMatrix, numVertices, numEdges);
        cout << "Minimum cost of the spanning tree: " << minCost << endl;
        break;
    }
    default:
        cout << "Invalid choice!" << endl;
    }

    // Освобождение памяти
    for (int i = 0; i < numVertices; i++)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;

    return 0;
}

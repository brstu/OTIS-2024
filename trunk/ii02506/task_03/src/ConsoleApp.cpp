#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

const int LARGE_NUMBER = 10000;

// Поиск в глубину
void depthFirstSearch(int** graph, int vertices, int start, vector<bool>& visitedNodes) {
    cout << endl;
    stack<int> dfsStack;
    dfsStack.push(start);
    while (!dfsStack.empty()) {
        int node = dfsStack.top();
        dfsStack.pop();
        if (visitedNodes[node]) continue;
        visitedNodes[node] = true;
        cout << node + 1 << " ";
        for (int i = 0; i < vertices; ++i) {
            if (!visitedNodes[i] && graph[node][i]) {
                dfsStack.push(i);
            }
        }
    }
}

// Поиск в ширину
void breadthFirstSearch(int** graph, int vertices, int start, vector<bool>& visitedNodes) {
    cout << endl;
    queue<int> bfsQueue;
    bfsQueue.push(start);
    visitedNodes[start] = true;
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        cout << current + 1 << " ";
        for (int i = 0; i < vertices; ++i) {
            if (!visitedNodes[i] && graph[current][i]) {
                bfsQueue.push(i);
                visitedNodes[i] = true;
            }
        }
    }
}

// Заполнение графа из файла
void initializeGraph(int**& graph, int vertices, int edges, const string& filePath) {
    ifstream fileInput(filePath);
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < vertices; ++j)
            graph[i][j] = 0;
    int a, b, weight;
    for (int i = 0; i < edges; ++i) {
        fileInput >> a >> b >> weight;
        cout << a << " -> " << b << " [" << weight << "]\n";
        graph[a - 1][b - 1] = weight;
    }
}

// Печать графа
void displayGraph(int**& graph, int vertices) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j)
            cout << graph[i][j] << " ";
        cout << endl;
    }
}

// Пример функции алгоритма Прима (рефакторинг)
void primAlgorithm(int**& graph, int vertices) {
    vector<bool> selected(vertices, false);
    selected[0] = true;
    int totalWeight = 0;

    for (int edges = 1; edges < vertices; ++edges) {
        int minWeight = LARGE_NUMBER;
        int startVertex = -1, endVertex = -1;

        for (int u = 0; u < vertices; ++u) {
            if (selected[u]) {
                for (int v = 0; v < vertices; ++v) {
                    if (!selected[v] && graph[u][v] && graph[u][v] < minWeight) {
                        minWeight = graph[u][v];
                        startVertex = u;
                        endVertex = v;
                    }
                }
            }
        }

        cout << startVertex + 1 << " -> " << endVertex + 1 << " [" << minWeight << "]\n";
        totalWeight += minWeight;
        selected[endVertex] = true;
    }

    cout << "Total weight of the minimum spanning tree: " << totalWeight << endl;
}

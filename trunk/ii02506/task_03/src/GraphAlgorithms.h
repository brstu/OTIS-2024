#pragma once
#include <vector>
#include <string>
using namespace std;

void depthFirstSearch(int** graph, int vertices, int start, vector<bool>& visitedNodes);
void breadthFirstSearch(int** graph, int vertices, int start, vector<bool>& visitedNodes);
void initializeGraph(int**& graph, int vertices, int edges, const string& filePath);
void displayGraph(int**& graph, int vertices);
void primAlgorithm(int**& graph, int vertices);

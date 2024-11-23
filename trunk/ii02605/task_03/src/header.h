using namespace std;
#pragma once

void depthFirstSearch(int**, int, int, vector<bool>&);
void breadthFirstSearch(int**, int, int, vector<bool>&);
void fillMatrix(int**&, int, int, string);
void paintMatrix(int**&, int);
bool hamiltonianPath(int**&, int*&, int*&, int, int, int);
void printPath(int*&, int);
void eulerianPath(int**&, vector<int>&, int);
void dijkstraAlgorithm(int**&, int);
void floydWarshall(int**&, int);
void primAlgorithm(int**&, int);
int findParent(int*, int);
void unionFind(int*, int, int);
void kruskalAlgorithm(pair<int, pair<int, int>>*, int*, int**&, int, int);
void mainKruskal(int**&, int, int, string);
void kaliAlgorithm();
void generatePermutation(string);
void strongConnectedComponents(int**&, int);
void findBiconnectedComponents(int**&, int);
void findArticulationPointsAndBridges(int**&, int);

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 2147483647

class Graph {
private:
    int V;  // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list with weights
    vector<vector<int>> dist; // Distance matrix for Floyd-Warshall

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V + 1);
        dist.resize(V + 1, vector<int>(V + 1, INF));
        
        // Initialize diagonal to 0
        for(int i = 1; i <= V; i++) 
            dist[i][i] = 0;
    }
    
    void addEdge(int src, int dest, int weight) {
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight}); // For undirected graph
        dist[src][dest] = weight;
        dist[dest][src] = weight;
    }
    
    vector<int> dijkstra(int start) {
        vector<int> distance(V + 1, INF);
        distance[start] = 0;
        
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, start});
        
        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            for(auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if(distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    pq.push({distance[v], v});
                }
            }
        }
        return distance;
    }
    
    void floydWarshall() {
        for(int k = 1; k <= V; k++) {
            for(int i = 1; i <= V; i++) {
                for(int j = 1; j <= V; j++) {
                    if(dist[i][k] != INF && dist[k][j] != INF && 
                       dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    void printDistances(vector<int>& distances) {
        cout << "Кратчайшие расстояния от начальной вершины:\n";
        for(int i = 1; i <= V; i++) {
            cout << "До вершины " << i << ": ";
            if(distances[i] == INF)
                cout << "БесКон";
            else
                cout << distances[i];
            cout << endl;
        }
    }
    
    void printFloydWarshall() {
        cout << "\nКратчайшие пути между всеми парами вершин (Флойд-Уоршелл):\n";
        for(int i = 1; i <= V; i++) {
            for(int j = 1; j <= V; j++) {
                if(dist[i][j] == INF)
                    cout << "БесКон ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(6); // 6 vertices
    
    // Adding edges with weights
    g.addEdge(1, 2, 4);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 3, 6);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 4);
    g.addEdge(3, 5, 7);
    g.addEdge(3, 6, 8);
    g.addEdge(4, 5, 5);
    g.addEdge(5, 6, 6);
    
    // Dijkstra's algorithm from vertex 1
    cout << "Результаты алгоритма Дейкстры:\n";
    vector<int> dijkstraResult = g.dijkstra(1);
    g.printDistances(dijkstraResult);
    
    // Floyd-Warshall algorithm
    g.floydWarshall();
    g.printFloydWarshall();
    
    return 0;
}
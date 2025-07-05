#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj; //Списки инцидентности
    void bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, 
                   vector<int>& low, vector<int>& parent, int& bridgeCount);

public:
    Graph(int V);
    void addEdge(int u, int v);
    int findBridges();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::bridgeUtil(int u, vector<bool>& visited, vector<int>& disc, 
                      vector<int>& low, vector<int>& parent, int& bridgeCount) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent, bridgeCount);

            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                bridgeCount++;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int Graph::findBridges() {
    vector<bool> visited(V, false);
    vector<int> disc(V, 0);
    vector<int> low(V, 0);
    vector<int> parent(V, -1);
    int bridgeCount = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            bridgeUtil(i, visited, disc, low, parent, bridgeCount);
        }
    }

    return bridgeCount;
}

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << g.findBridges() << endl;

    return 0;
}
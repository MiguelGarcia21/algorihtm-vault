#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();

void floydWarshall(int V, vector<vector<int>>& dist, vector<vector<int>>& next) {
    for (int i = 0; i < V; ++i) {
        dist[i][i] = 0;
        next[i][i] = i;
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

bool hasNegativeCycle(const vector<vector<int>>& dist) {
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i][i] < 0) return true;
    }
    return false;
}

vector<int> reconstructPath(int u, int v, const vector<vector<int>>& next) {
    if (next[u][v] == -1) return {};
    vector<int> path = {u};
    while (u != v) {
        u = next[u][v];
        if (u == -1) return {};
        path.push_back(u);
    }
    return path;
}

void printDistanceMatrix(const vector<vector<int>>& dist) {
    int V = dist.size();
    cout << "\nAll-pairs shortest distances:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << setw(3) << dist[i][j] << " "; // setw is for spreadsheet-like formatting
        }
        cout << "\n";
    }
}

void printPathMatrix(const vector<vector<int>>& next) {
    int V = next.size();
    cout << "\nShortest paths between all pairs:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << "Path from " << i << " to " << j << ": ";
            vector<int> path = reconstructPath(i, j, next);
            if (path.empty()) {
                cout << "No path";
            } else {
                for (size_t k = 0; k < path.size(); ++k) {
                    cout << path[k];
                    if (k + 1 < path.size()) cout << " -> ";
                }
            }
            cout << "\n";
        }
    }
}

int main() {
    int V, E;
    cout << "Enter number of nodes and edges: ";
    cin >> V >> E;

    vector<vector<int>> dist(V, vector<int>(V, INF));
    vector<vector<int>> next(V, vector<int>(V, -1));

    cout << "Enter edges (from to weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        next[u][v] = v;
    }

    floydWarshall(V, dist, next);

    if (hasNegativeCycle(dist)) {
        cout << "\nNegative weight cycle detected.\n";
    } else {
        printDistanceMatrix(dist);
        printPathMatrix(next);
    }

    return 0;
}
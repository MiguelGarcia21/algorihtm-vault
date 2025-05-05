#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int from, to, weight;
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
};

class Graph {
public:
    int V;
    vector<Edge> edges;

    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int w) {
        edges.emplace_back(u, v, w);
    }

    bool bellmanFord(int start, unordered_map<int, int>& dist, unordered_map<int, int>& prev) {
        dist.clear();
        prev.clear();
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
            prev[i] = -1;
        }
        dist[start] = 0;

        for (int i = 1; i < V; ++i) {
            for (const auto& edge : edges) {
                if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                    prev[edge.to] = edge.from;
                }
            }
        }

        for (const auto& edge : edges) {
            if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
                return false; // Negative cycle found
            }
        }

        return true;
    }

    vector<int> reconstructPath(int target, const unordered_map<int, int>& prev) {
        vector<int> path;
        for (int at = target; at != -1; at = prev.at(at)) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int V, E;
    cout << "Enter number of nodes and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter edges (from to weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int start;
    cout << "Enter start node: ";
    cin >> start;

    unordered_map<int, int> distances, previous;

    if (g.bellmanFord(start, distances, previous)) {
        cout << "\nShortest paths from node " << start << ":\n";
        for (int node = 0; node < V; ++node) {
            cout << "Node " << node << ": ";
            if (distances[node] == INF) {
                cout << "Unreachable\n";
            } else {
                cout << "Distance = " << distances[node] << ", Path = ";
                vector<int> path = g.reconstructPath(node, previous);
                for (size_t i = 0; i < path.size(); ++i) {
                    cout << path[i];
                    if (i + 1 < path.size()) cout << " -> ";
                }
                cout << "\n";
            }
        }
    } else {
        cout << "\nNegative weight cycle detected. Shortest paths not defined.\n";
    }

    return 0;
}
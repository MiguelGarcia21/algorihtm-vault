#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <stack>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

struct Node {
    int id;
    vector<Edge> edges;
    Node(int i) : id(i) {}
};

class Graph {
public:
    unordered_map<int, Node*> nodes;

    ~Graph() {
        for (auto& pair : nodes) delete pair.second;
    }

    void addNode(int id) {
        if (nodes.find(id) == nodes.end()) {
            nodes[id] = new Node(id);
        }
    }

    void addEdge(int from, int to, int weight) {
        addNode(from);
        addNode(to);
        nodes[from]->edges.emplace_back(to, weight);
    }

    pair<unordered_map<int, int>, unordered_map<int, int>> dijkstra(int start) {
        unordered_map<int, int> dist;
        unordered_map<int, int> prev;
        for (auto& pair : nodes) {
            dist[pair.first] = INF;
            prev[pair.first] = -1;
        }
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [curDist, u] = pq.top(); pq.pop();
            if (curDist > dist[u]) continue;

            for (const Edge& e : nodes[u]->edges) {
                int v = e.to;
                int weight = e.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        return {dist, prev};
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
    Graph g;

    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter edges in this order (from to weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int start;
    cout << "Enter start node: ";
    cin >> start;

    auto [distances, previous] = g.dijkstra(start);

    cout << "\nShortest paths from node " << start << ":\n";
    for (auto& [node, dist] : distances) {
        cout << "Node " << node << ": ";
        if (dist == INF) {
            cout << "Unreachable\n";
        } else {
            cout << "Distance = " << dist << ", Path = ";
            vector<int> path = g.reconstructPath(node, previous);
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i + 1 < path.size()) cout << " -> ";
            }
            cout << "\n";
        }
    }

    return 0;
}
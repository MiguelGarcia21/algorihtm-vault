# Dijkstra's Algorithm - Shortest Path Finder

## 🏰 Problem Description
Dijkstra's algorithm finds the shortest paths from a starting node to all other nodes in a weighted graph with non-negative edge weights. This implementation:
- Handles directed/undirected graphs
- Returns both distances and full paths
- Uses efficient priority queue operations

## 🏗️ Code Architecture

### 📦 Header Includes
```cpp
#include <iostream>       // Basic I/O
#include <vector>         // Dynamic arrays
#include <queue>          // Priority queue
#include <unordered_map>  // Hash-based mapping
#include <limits>         // INF constant
#include <stack>          // Path reconstruction
#include <algorithm>      // reverse()
```
Essential libraries for graph operations and data management.

### 📊 Core Data Structures
```cpp
const int INF = numeric_limits<int>::max();

struct Edge {
    int to;       // Destination node
    int weight;   // Edge cost
    Edge(int t, int w) : to(t), weight(w) {}
};

struct Node {
    int id;               // Node identifier
    vector<Edge> edges;   // Outgoing connections
    Node(int i) : id(i) {}
};
```

### 🌐 Graph Class
```cpp
class Graph {
    unordered_map<int, Node*> nodes;  // All nodes storage
    
    ~Graph() { /* Cleanup */ }
    
    void addNode(int id) { /* Add new node */ }
    
    void addEdge(int from, int to, int weight) {
        addNode(from);
        addNode(to);
        nodes[from]->edges.emplace_back(to, weight);
    }
```
Manages graph construction and memory.

## 🚀 Algorithm Implementation

### Priority Queue Initialization
```cpp
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
pq.push({0, start});  // (distance, node)
```
Min-heap prioritized by distance.

### Main Dijkstra Loop
```cpp
while (!pq.empty()) {
    auto [curDist, u] = pq.top(); pq.pop();
    if (curDist > dist[u]) continue;  // Skip outdated entries
    
    for (const Edge& e : nodes[u]->edges) {
        int v = e.to;
        if (dist[u] + e.weight < dist[v]) {
            dist[v] = dist[u] + e.weight;  // Relaxation (distance update)
            prev[v] = u;                   // Path tracking
            pq.push({dist[v], v});
        }
    }
}
```
Core relaxation process that updates shortest paths.

### Path Reconstruction
```cpp
vector<int> reconstructPath(int target, const unordered_map<int, int>& prev) {
    vector<int> path;
    for (int at = target; at != -1; at = prev.at(at)) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
```
Backtracks from target to source using predecessor map.

## 💻 Input/Output Example

### Sample Input
```
5 7
0 1 4
0 2 2
1 2 3
1 3 2
1 4 3
2 1 1
2 3 4
2 4 5
0
```

### Expected Output
```
Shortest paths from node 0:
Node 0: Distance = 0, Path = 0
Node 1: Distance = 3, Path = 0 -> 2 -> 1
Node 2: Distance = 2, Path = 0 -> 2
Node 3: Distance = 5, Path = 0 -> 2 -> 1 -> 3
Node 4: Distance = 6, Path = 0 -> 2 -> 1 -> 4
```

## 📊 Performance Analysis
- **Time Complexity**: O((V + E) log V) with priority queue
- **Space Complexity**: O(V + E) for graph storage

## 🎯 Key Knowledge Concepts
- Clean OOP implementation
- Handles disconnected nodes
- Provides full path reconstruction
- Memory-safe with proper cleanup
# 📌 Bellman-Ford Shortest Path Algorithm (C++)

This unit implements the **Bellman-Ford algorithm** in C++ to find the shortest paths from a **single source node** to all other nodes in a **weighted, directed graph**. The algorithm also **detects negative weight cycles**.

---

## 🔧 Features

* Calculates shortest distances from a start node to all other nodes.
* Supports negative weight edges.
* Detects negative weight cycles.
* Command-line input for number of vertices, edges, and edge details.
* Reconstructs and displays the shortest path from the source to each node.
---

## 🧠 Bellman-Ford Algorithm Explained

### ✅ Time Complexity:

* **O(V × E)** — where V = number of vertices and E = number of edges.

### 🛑 Warning:

* Slower than Dijkstra's algorithm for graphs without negative weights.
* Works when Dijkstra fails due to negative edge weights.

---

## 📄 Code Overview (Granular Explanation)

### 1. **Includes and Setup**

```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;
const int INF = numeric_limits<int>::max();
```

* Includes standard headers.
* `INF` is defined for initializing infinite distances.

---

### 2. **Edge Structure**

```cpp
struct Edge {
    int from, to, weight;
};
```

* Represents a **directed edge** from `from` to `to` with a `weight`.

---

### 3. **Bellman-Ford Function**

```cpp
bool bellmanFord(int V, int start, const vector<Edge>& edges, vector<int>& dist, vector<int>& pred)
```

* Arguments:

  * `V`: Number of vertices.
  * `start`: Starting node.
  * `edges`: List of edges in the graph.
  * `dist`: Output vector for shortest distances.
  * `pred`: Output vector for predecessors (used to reconstruct paths).
* Initializes distances to `INF`, except the `start` node which is `0`.
* **Loops V-1 times**, relaxing all edges:

  * If `dist[u] + weight < dist[v]`, it updates `dist[v]` and sets `pred[v] = u`.
* **Extra loop** to check for negative weight cycles:

  * If another relaxation is possible, returns `false`.

---

### 4. **Path Reconstruction**

```cpp
vector<int> reconstructPath(int end, const vector<int>& pred)
```

* Traces back from the `end` node using `pred` array.
* Builds and reverses the path from end to start.

---

### 5. **Main Function and Input Handling**

```cpp
int main() {
    int V, E;
    cin >> V >> E;
    ...
}
```

* Reads number of vertices and edges.
* Reads each edge as: `from to weight`.
* Reads the start node.
* Calls `bellmanFord()` and checks return value.
* If no negative cycle is detected, prints distances and reconstructed paths.
* If there is a negative cycle, a warning is printed.

---

## 🧪 Sample Input

```
5 8
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
0
```

### 💬 Explanation:

* `5` nodes (0 through 4), `8` directed edges.
* Nodes definition.
* Start node: `0`.

---

## 📤 Sample Output

```
Shortest distances from node 0:
Node 0: Distance = 0, Path = 0
Node 1: Distance = -1, Path = 0 -> 1
Node 2: Distance = 2, Path = 0 -> 1 -> 2
Node 3: Distance = -2, Path = 0 -> 1 -> 4 -> 3
Node 4: Distance = 1, Path = 0 -> 1 -> 4
```

---

## ⚠️ Output with a Negative Cycle (Example)

If a negative cycle is present:

```
Graph contains a negative weight cycle.
```

---


## 🛠️ Application improvements by use-case

* Add early stopping if no updates in an iteration.
* Support node labels (like strings or custom IDs).
* Support input/output from files.

---
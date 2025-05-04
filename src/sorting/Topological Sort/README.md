# 🎯 Topological Sorting in C++

This units contains two standalone C++ programs that demonstrate **Topological Sorting** on a **Directed Acyclic Graph (DAG)**:

- `topsort_dfs.cpp` - Depth-First Search (DFS) based implementation
- `topsort_bfs.cpp` - Breadth-First Search (BFS) based implementation using **Kahn's Algorithm**
---

## 🔎 Overview of Topological Sort

Topological sorting is used for ordering vertices in a **Directed Acyclic Graph (DAG)** such that for every directed edge `u -> v`, vertex `u` appears before `v` in the ordering.

---

## 🧠 Solution Approaches

### 1️⃣ DFS-Based Topological Sort (`topsort_dfs.cpp`)

Uses depth-first traversal to process all dependencies of a node before marking it as finished.

#### ✅ Features:
- Recursive DFS traversal
- Post-order node insertion into result stack
- Reverse final stack for topological order

---

### 2️⃣ BFS-Based Topological Sort - **Kahn’s Algorithm** (`topsort_bfs.cpp`)

Uses in-degree of nodes to find the order via BFS traversal.

#### ✅ Features:
- In-degree calculation
- BFS queue starting from nodes with 0 in-degree
- Visited count check to detect cycles

---

## 🏗️ Code Breakdown

### ✨ Common Concepts

- **Graph Representation**: `adjacency list`
- **Input**: number of vertices and list of directed edges
- **Output**: topological ordering or error message if a cycle exists

---

### 🧵 DFS Topo Sort: Key Components (`topsort_dfs.cpp`)

#### 1. Includes & Graph Setup
```
#include <iostream>
#include <vector>
#include <stack>
````

#### 2. DFS Recursive Function

```
void dfs(int node, vector<bool> &visited, stack<int> &stk, vector<vector<int>> &adj)
```

* Visits unvisited neighbors recursively
* Pushes current node to stack **after** visiting all neighbors

#### 3. Main Logic

* Initializes `visited` vector
* Calls DFS for all unvisited nodes
* Pops from stack to get topological order

---

### 📊 BFS Topo Sort: Kahn’s Algorithm (`topsort_bfs.cpp`)

#### 1. Includes & Graph Setup

```
#include <iostream>
#include <vector>
#include <queue>
```

#### 2. In-Degree Calculation

```
vector<int> in_degree(n, 0);
```

* For every edge `u -> v`, increment `in_degree[v]`

#### 3. BFS Loop

```
queue<int> q;
for (int i = 0; i < n; i++)
    if (in_degree[i] == 0) q.push(i);

while (!q.empty()) {
    int node = q.front(); q.pop();
    topo_order.push_back(node);
    for (int neighbor : adj[node]) {
        if (--in_degree[neighbor] == 0)
            q.push(neighbor);
    }
}
```

#### 4. Cycle Detection

If `topo_order.size() != n`, a cycle exists.

---

## 🧪 Sample Input

```
6 6
5 2
5 0
4 0
4 1
2 3
3 1
```

## ✅ Sample Output

```
Topological Order (DFS): 4 5 2 3 1 0
Topological Order (BFS): 4 5 0 2 3 1
```

(Note: multiple valid topological orders may exist.)

---

## ⏱️ Performance

| Algorithm     | Time Complexity | Space Complexity |
| ------------- | --------------- | ---------------- |
| DFS Topo Sort | O(V + E)        | O(V + E)         |
| BFS (Kahn’s)  | O(V + E)        | O(V + E)         |

---

## 📌 Notes

* Input assumes zero-indexed nodes.
* Handles any DAG with up to `10^5` nodes.
* Cycle detection included in Kahn's Algorithm.

---

## 📎 References

* [Topological Sorting (GeeksforGeeks)](https://www.geeksforgeeks.org/topological-sorting/)
* [Kahn's Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm)


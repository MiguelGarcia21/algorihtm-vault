# Floyd-Warshall Algorithm – All-Pairs Shortest Path

This Unit implements the **Floyd-Warshall algorithm** in C++ for solving the *All-Pairs Shortest Path* problem in a directed weighted graph.

---

## 📌 What is Floyd-Warshall?

The Floyd-Warshall algorithm computes the shortest distances between **all pairs of vertices** in a graph. It works for both **positive and negative edge weights** but **not for graphs with negative cycles**.

It uses **dynamic programming** and progressively refines shortest paths by considering every possible intermediate node.

## 🧠 How It Works (Step-by-Step Breakdown)

### 1. **Headers and Constants**
```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
````

* `iostream`: For input/output.
* `vector`: To represent matrices (2D vectors).
* `limits`: For representing infinity (`INT_MAX`).
* `iomanip`: Used to align printed matrix columns with `setw()`.

```cpp
const int INF = numeric_limits<int>::max();
```

* Represents an unreachable distance.

---

### 2. **Floyd-Warshall Core Function**

```cpp
void floydWarshall(int V, vector<vector<int>>& dist, vector<vector<int>>& next)
```

* `dist[i][j]`: Current shortest distance from `i` to `j`.
* `next[i][j]`: The next hop from `i` to `j` for path reconstruction.

#### 🔁 Core Idea:

* For each pair `(i, j)` and each node `k`, check if going through `k` gives a shorter path:

  ```
  if dist[i][k] + dist[k][j] < dist[i][j]:
      dist[i][j] = dist[i][k] + dist[k][j]
      next[i][j] = next[i][k]
  ```

#### 🧾 Path Table Initialization:

```cpp
dist[i][i] = 0;
next[i][i] = i;
```

---

### 3. **Negative Cycle Detection**

```cpp
bool hasNegativeCycle(const vector<vector<int>>& dist)
```

* Checks if `dist[i][i] < 0` which means a negative cycle exists.

---

### 4. **Path Reconstruction**

```cpp
vector<int> reconstructPath(int u, int v, const vector<vector<int>>& next)
```

* Builds the path by following `next[u][v]`, `next[next[u][v]][v]`, ..., until destination.

---

### 5. **Matrix Output Functions**

```cpp
void printDistanceMatrix(...)
void printPathMatrix(...)
```

* Print `dist` and full reconstructed paths between each pair.
* Uses `setw(3)` to align numbers in matrix output.

---

## 🧪 Sample Input/Output

### 🧾 Input

```
Enter number of vertices and edges: 
4 5
Enter edges in the format (u v w): 
0 1 5
0 3 10
1 2 3
2 3 1
3 0 7
```

### 📤 Output

```
Distance Matrix:
  0  5  8  9
 11  0  3  4
  8 13  0  1
  7 12 15  0

Shortest Paths:
Path from 0 to 0: 0
Path from 0 to 1: 0 -> 1
Path from 0 to 2: 0 -> 1 -> 2
Path from 0 to 3: 0 -> 1 -> 2 -> 3
...
```

---

## 🖼️ Matrix Visual walkthrough
### 🔄 Initialization
This is the Graph representation of the input:

![sjjsj drawio](https://github.com/user-attachments/assets/e56ac42c-0e01-4001-8637-71b9d80c8a89)

---



#### 🧮 Distance Matrix (`dist`)

|   | 0 | 1 | 2 | 3  |
| - | - | - | - | -- |
| 0 | 0 | 5 | ∞ | 10 |
| 1 | ∞ | 0 | 3 | ∞  |
| 2 | ∞ | ∞ | 0 | 1  |
| 3 | 7 | ∞ | ∞ | 0  |

#### 🧭 Path Matrix (`next`)

|   | 0 | 1 | 2 | 3 |
| - | - | - | - | - |
| 0 | 0 | 1 | - | 3 |
| 1 | - | 1 | 2 | - |
| 2 | - | - | 2 | 3 |
| 3 | 0 | - | - | 3 |

---

### 🧩 Iteration by Intermediate Node `k = 0`

#### ✅ Updated Distance Matrix

|   | 0 | 1  | 2 | 3  |
| - | - | -- | - | -- |
| 0 | 0 | 5  | ∞ | 10 |
| 1 | ∞ | 0  | 3 | ∞  |
| 2 | ∞ | ∞  | 0 | 1  |
| 3 | 7 | 12 | ∞ | 0  |

#### ✅ Updated Path Matrix

|   | 0 | 1 | 2 | 3 |
| - | - | - | - | - |
| 0 | 0 | 1 | - | 3 |
| 1 | - | 1 | 2 | - |
| 2 | - | - | 2 | 3 |
| 3 | 0 | 0 | - | 3 |

---

### 🧩 Iteration by Intermediate Node `k = 1`

#### ✅ Updated Distance Matrix

|   | 0 | 1  | 2  | 3  |
| - | - | -- | -- | -- |
| 0 | 0 | 5  | 8  | 10 |
| 1 | ∞ | 0  | 3  | ∞  |
| 2 | ∞ | ∞  | 0  | 1  |
| 3 | 7 | 12 | 15 | 0  |

#### ✅ Updated Path Matrix

|   | 0 | 1 | 2 | 3 |
| - | - | - | - | - |
| 0 | 0 | 1 | 1 | 3 |
| 1 | - | 1 | 2 | - |
| 2 | - | - | 2 | 3 |
| 3 | 0 | 0 | 0 | 3 |

---

### 🧩 Iteration by Intermediate Node `k = 2`

#### ✅ Updated Distance Matrix

|   | 0 | 1  | 2  | 3 |
| - | - | -- | -- | - |
| 0 | 0 | 5  | 8  | 9 |
| 1 | ∞ | 0  | 3  | 4 |
| 2 | ∞ | ∞  | 0  | 1 |
| 3 | 7 | 12 | 15 | 0 |

#### ✅ Updated Path Matrix

|   | 0 | 1 | 2 | 3 |
| - | - | - | - | - |
| 0 | 0 | 1 | 1 | 1 |
| 1 | - | 1 | 2 | 2 |
| 2 | - | - | 2 | 3 |
| 3 | 0 | 0 | 0 | 3 |

---

### 🧩 Iteration by Intermediate Node `k = 3`

#### ✅ Final Distance Matrix

|   | 0  | 1  | 2  | 3 |
| - | -- | -- | -- | - |
| 0 | 0  | 5  | 8  | 9 |
| 1 | 11 | 0  | 3  | 4 |
| 2 | 8  | 13 | 0  | 1 |
| 3 | 7  | 12 | 15 | 0 |

#### ✅ Final Path Matrix

|   | 0 | 1 | 2 | 3 |
| - | - | - | - | - |
| 0 | 0 | 1 | 1 | 1 |
| 1 | 2 | 1 | 2 | 2 |
| 2 | 3 | 3 | 2 | 3 |
| 3 | 0 | 0 | 0 | 3 |

---

## 🔧 Future Features (optional, based on use case)

These features may be added if required in use-case:

* ✅ Export shortest path matrices to `.csv` for further analysis.
* ✅ Visual graph rendering of shortest paths.
* ✅ Optimized sparse-matrix version using adjacency lists.
* ✅ Interface to detect and highlight negative cycles graphically.
* ✅ Dijkstra/Floyd hybrid mode for runtime efficiency in sparse graphs.

---

## 🧠 Key Takeaways

* Floyd-Warshall is elegant for **dense graphs** and **all-pairs shortest paths**.
* Handles **negative weights** (unlike Dijkstra).
* Cannot handle **negative cycles**.
* Easy to extend with **path reconstruction** thanks to the `next[][]` matrix.

---

## 📚 References

* [Floyd-Warshall Algorithm - GeeksforGeeks](https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/)
* [CP Algorithms - Floyd-Warshall](https://cp-algorithms.com/graph/all_shortest_paths_floyd_warshall.html)

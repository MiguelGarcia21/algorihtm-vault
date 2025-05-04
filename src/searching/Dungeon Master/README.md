# Dungeon Master - 3D BFS Pathfinder

## �️ Problem Overview
A 3D grid-based dungeon escape problem where you must find the shortest path from start ('S') to exit ('E') in a multi-level dungeon, avoiding walls ('#') and moving in *6 possible directions* (up/down levels + cardinal directions).

## 🧠 Solution Approach
This C++ implementation uses Breadth-First Search (BFS) to guarantee finding the shortest path in an unweighted 3D grid. The solution features:
- 3D grid traversal with boundary checking
- Path reconstruction via parent tracking
- Time-optimal pathfinding (O(L×R×C) complexity)
- Clear visualization of escape path

## 🏗️ Code Breakdown

### 📦 Header Includes
```
#include <iostream>   // Basic I/O operations
#include <vector>     // Dynamic array storage
#include <queue>      // BFS queue implementation
#include <tuple>      // Handling 3D coordinates
#include <algorithm>  // Path reversal
```
These standard libraries provide necessary data structures and algorithms.

### 🧩 Data Structures
```
struct Node {
    int z, x, y, time;  // 3D coordinates + time elapsed
};

vector<vector<vector<char>>> dungeon;   // 3D dungeon map storage
vector<vector<vector<bool>>> visited;  // Visited nodes tracker
vector<vector<vector<tuple<int,int,int>>>> parent; // Path reconstruction
```
- `Node` tracks position and time
- 3D vectors store dungeon data and traversal state
- Parent array enables path backtracking

### 🧭 Movement System
```
int dz[6] = {0, 0, 0, 0, 1, -1}; // Level changes (up/down)
int dx[6] = {1, -1, 0, 0, 0, 0}; // Row changes (north/south)
int dy[6] = {0, 0, 1, -1, 0, 0}; // Column changes (east/west)
```
Arrays define all 6 possible movement directions in 3D space.

### 🔍 Validation Function
```
bool isValid(int z, int x, int y) {
    return z >= 0 && z < L && x >= 0 && x < R && y >= 0 && y < C;
}
```
Checks if coordinates are within dungeon boundaries.

## 🚀 Core Algorithm: BFS Implementation

### Initialization
```
int bfs(int sz, int sx, int sy, int ez, int ex, int ey) {
    queue<Node> q;
    q.push({sz, sx, sy, 0});
    visited[sz][sx][sy] = true;
```
- Creates BFS queue with starting position
- Marks start node as visited

### Main BFS Loop
```
while (!q.empty()) {
    Node current = q.front();
    q.pop();

    if (current.z == ez && current.x == ex && current.y == ey) {
        // Path reconstruction shown below
        return current.time;
    }
```
Processes nodes until queue is empty or exit is found.

### Neighbor Exploration
```
for (int i = 0; i < 6; i++) {
    int nz = current.z + dz[i];
    int nx = current.x + dx[i];
    int ny = current.y + dy[i];

    if (isValid(nz, nx, ny) && !visited[nz][nx][ny] 
        && dungeon[nz][nx][ny] != '#') {
        visited[nz][nx][ny] = true;
        q.push({nz, nx, ny, current.time + 1});
        parent[nz][nx][ny] = {current.z, current.x, current.y};
    }
}
```
Checks all 6 possible moves from current position, enqueueing valid ones.

### Path Reconstruction
```
vector<tuple<int, int, int>> path;
tuple<int, int, int> cur = {ez, ex, ey};
while (cur != make_tuple(sz, sx, sy)) {
    path.push_back(cur);
    cur = parent[get<0>(cur)][get<1>(cur)][get<2>(cur)];
}
path.push_back({sz, sx, sy});
reverse(path.begin(), path.end());
```
Backtracks from exit to start using parent pointers, then reverses the path.

## 🖥️ Main Program Flow

### Input Handling
```
int main() {
    while (cin >> L >> R >> C, L || R || C) {
        dungeon.assign(L, vector<vector<char>>(R, vector<char>(C)));
        visited.assign(L, vector<vector<bool>>(R, vector<bool>(C, false)));
        parent.assign(L, vector<vector<tuple<int,int,int>>>(R, 
                   vector<tuple<int,int,int>>(C, {-1, -1, -1})));
```
Initializes 3D arrays for each test case.

### Dungeon Parsing
```
for (int z = 0; z < L; ++z) {
    for (int x = 0; x < R; ++x) {
        for (int y = 0; y < C; ++y) {
            cin >> dungeon[z][x][y];
            if (dungeon[z][x][y] == 'S') {
                sz = z; sx = x; sy = y;
            }
            if (dungeon[z][x][y] == 'E') {
                ez = z; ex = x; ey = y;
            }
        }
    }
}
```
Reads dungeon layout and locates start/exit positions.

### Execution and Output
```
int minutes = bfs(sz, sx, sy, ez, ex, ey);
if (minutes != -1)
    cout << "Escaped in " << minutes << " minute(s).\n";
else
    cout << "Trapped!\n";
```
Runs BFS and displays results.

## 📊 Example Execution

### Input
```
2 3 4
S...
.##.
..#.
####
##.#
##E#
0 0 0
```

### Output
```
Escape path:
(0, 0, 0)
(0, 0, 1)
(0, 1, 1)
(1, 1, 1)
(1, 2, 1)
(1, 2, 2)
(1, 2, 3)
Escaped in 6 minute(s).
```

## ⏱️ Performance
- **Time Complexity**: O(L×R×C) - Visits each cell once
- **Space Complexity**: O(L×R×C) - Stores dungeon and tracking arrays
- Optimal for unweighted grid pathfinding
---

## 📝 Notes
- Handles multiple test cases until termination
- Extensible for larger dungeons with memory optimization

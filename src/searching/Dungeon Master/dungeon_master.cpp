#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

struct Node {
    int z, x, y, time;
};

int L, R, C;
vector<vector<vector<char>>> dungeon;
vector<vector<vector<bool>>> visited;
vector<vector<vector<tuple<int, int, int>>>> parent;

int dz[6] = {0, 0, 0, 0, 1, -1};
int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};

bool isValid(int z, int x, int y) {
    return z >= 0 && z < L && x >= 0 && x < R && y >= 0 && y < C;
}

int bfs(int sz, int sx, int sy, int ez, int ex, int ey) {
    queue<Node> q;
    q.push({sz, sx, sy, 0});
    visited[sz][sx][sy] = true;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.z == ez && current.x == ex && current.y == ey) {
            vector<tuple<int, int, int>> path;
            tuple<int, int, int> cur = {ez, ex, ey};
            while (cur != make_tuple(sz, sx, sy)) {
                path.push_back(cur);
                cur = parent[get<0>(cur)][get<1>(cur)][get<2>(cur)];
            }
            path.push_back({sz, sx, sy});
            reverse(path.begin(), path.end());

            cout << "Escape path:\n";
            for (auto [pz, px, py] : path) {
                cout << "(" << pz << ", " << px << ", " << py << ")\n";
                if (dungeon[pz][px][py] == '.')
                    dungeon[pz][px][py] = '*'; 
            }

            return current.time;
        }

        for (int i = 0; i < 6; i++) {
            int nz = current.z + dz[i];
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nz, nx, ny) && !visited[nz][nx][ny] && dungeon[nz][nx][ny] != '#') {
                visited[nz][nx][ny] = true;
                q.push({nz, nx, ny, current.time + 1});
                parent[nz][nx][ny] = {current.z, current.x, current.y};
            }
        }
    }

    return -1; // Not reachable
}

int main() {
    while (cin >> L >> R >> C, L || R || C) {
        dungeon.assign(L, vector<vector<char>>(R, vector<char>(C)));
        visited.assign(L, vector<vector<bool>>(R, vector<bool>(C, false)));
        parent.assign(L, vector<vector<tuple<int, int, int>>>(R, vector<tuple<int, int, int>>(C, {-1, -1, -1})));

        int sz, sx, sy, ez, ex, ey;

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

        int minutes = bfs(sz, sx, sy, ez, ex, ey);
        if (minutes != -1)
            cout << "Escaped in " << minutes << " minute(s).\n";
        else
            cout << "Trapped!\n";
    }

    return 0;
}
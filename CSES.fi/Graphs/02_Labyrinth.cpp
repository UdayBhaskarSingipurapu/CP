#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<int>> dist;
vector<vector<char>> parentDir;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char dir[4] = {'U', 'D', 'L', 'R'};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    grid.resize(n);
    dist.assign(n, vector<int>(m, -1));
    parentDir.assign(n, vector<char>(m, 0));

    int si = -1, sj = -1, ei = -1, ej = -1;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                si = i; sj = j;
            } else if (grid[i][j] == 'B') {
                ei = i; ej = j;
            }
        }
    }

    queue<pair<int,int>> q;
    q.push({si, sj});
    dist[si][sj] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d];
            int nc = c + dy[d];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                dist[nr][nc] == -1 &&
                (grid[nr][nc] == '.' || grid[nr][nc] == 'B')) {

                dist[nr][nc] = dist[r][c] + 1;
                parentDir[nr][nc] = dir[d];
                q.push({nr, nc});
            }
        }
    }

    if (dist[ei][ej] == -1) {
        cout << "NO\n";
        return 0;
    }

    // Reconstruct path
    string path;
    int r = ei, c = ej;
    while (r != si || c != sj) {
        char d = parentDir[r][c];
        path.push_back(d);
        if (d == 'U') r++;
        else if (d == 'D') r--;
        else if (d == 'L') c++;
        else if (d == 'R') c--;
    }

    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << "\n";
    cout << path << "\n";

    return 0;
}

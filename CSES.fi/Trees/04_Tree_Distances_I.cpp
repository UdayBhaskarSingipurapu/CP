#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> tree;

vector<int> bfs(int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : tree[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    cin>>n;
    tree.resize(n + 1);

    for(int i = 1; i < n; i++) {
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Step 1: BFS from node 1 → find A
    auto d1 = bfs(1);
    int A = max_element(d1.begin(), d1.end()) - d1.begin();

    // Step 2: BFS from A → find B and distA
    auto distA = bfs(A);
    int B = max_element(distA.begin(), distA.end()) - distA.begin();

    // Step 3: BFS from B → distB
    auto distB = bfs(B);

    // Step 4: Answer
    for(int i = 1; i <= n; i++) {
        cout<<max(distA[i], distB[i])<<" ";
    }
    cout<<"\n";

    return 0;
}

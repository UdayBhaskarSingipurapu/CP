#include<bits/stdc++.h>
using namespace std;

int n, ans;
vector<vector<int>> tree;
queue<int> q;
vector<bool> vis;

int bfs(int node, bool dist = false){
    q = queue<int>();
    vis = vector<bool>(n + 1, false);
    q.push(node);
    vis[node] = true;
    int last = node, lvl = 0;

    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            int nd = q.front();
            q.pop();
            last = nd;
            for(int adj: tree[nd]){
                if(!vis[adj]){
                    q.push(adj);
                    vis[adj] = true;
                }
            }
        }
        lvl++;
    }
    return dist ? lvl : last;
}

int main(){
    cin>>n;
    tree = vector<vector<int>>(n + 1);
    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    int last = bfs(1);
    cout<<bfs(last, true) - 1;
}
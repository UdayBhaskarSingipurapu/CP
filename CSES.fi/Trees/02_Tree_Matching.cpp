#include<bits/stdc++.h>
using namespace std;

int n, cnt;
vector<bool> used;
vector<vector<int>> tree;

void dfs(int node, int par){
    for(int adj: tree[node]){
        if(adj != par) dfs(adj, node);
    }
    if(!used[node] && !used[par] && par != 0){
        used[node] = used[par] = true;
        cnt++;
    }
}

int main(){
    cin>>n;
    cnt = 0;
    tree = vector<vector<int>>(n + 1);
    used = vector<bool>(n + 1, false);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1, 0);
    cout<<cnt;
}
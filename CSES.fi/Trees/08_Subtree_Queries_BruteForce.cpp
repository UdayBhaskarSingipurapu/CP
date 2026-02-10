#include<bits/stdc++.h>
using namespace std;

int n, q;
vector<vector<int>> tree;
vector<int> par, nodeVal;
vector<long long> subtreeVal;

void dfs(int node, int p){
    par[node] = p;
    for(int adj: tree[node]){
        if(adj == p) continue;
        dfs(adj, node);
        subtreeVal[node] += subtreeVal[adj];
    }
}

int main(){
    cin>>n>>q;
    tree = vector<vector<int>>(n + 1);
    nodeVal = par = vector<int>(n + 1);
    subtreeVal = vector<long long>(n + 1);
    for(int i = 1; i <= n; i++){
        cin>>nodeVal[i];
        subtreeVal[i] = nodeVal[i];
    }
    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1, 0);

    while(q--){
        int t;
        cin>>t;
        if(t == 1){
            int u, d;
            cin>>u>>d;
            int diff = d - nodeVal[u];
            nodeVal[u] = d;
            while(u != par[u]){
                subtreeVal[u] += diff;
                u = par[u];
            }
            subtreeVal[u] += diff;
        }
        else {
            int u;
            cin>>u;
            cout<<subtreeVal[u]<<'\n';
        }
    }
}
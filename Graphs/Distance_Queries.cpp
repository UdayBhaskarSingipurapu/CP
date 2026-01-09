#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> depth;
vector<vector<int>> parent;
int m = 20;

void dfsBinaryLifting(int node, int par){
    depth[node] = depth[par] + 1;

    parent[node][0] = par;
    for(int i = 1; i < m; i++){
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }

    for(int adj: graph[node]){
        if(adj != par){
            dfsBinaryLifting(adj, node);
        }
    }
}

int LCABinaryLifting(int u, int v){
    if(u == v) return u;
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    
    for(int i = m - 1; i >= 0; i--){
        if((diff >> i) & 1){
            u = parent[u][i];
        }
    }
    if(u == v) return u;
    for(int i = m - 1; i >= 0; i--){
        if(parent[u][i] != parent[v][i]){
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int distance(int u, int v){
    int lca = LCABinaryLifting(u, v);
    // cout<<u<<" "<<v<<" "<<lca<<" "<<depth[u]<<" "<<depth[v]<<" "<<depth[lca]<<"\n";
    return (depth[u] + depth[v]) - (2 * depth[lca]);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin>>n>>q;

    depth.resize(n + 1);
    parent.resize(n + 1, vector<int>(m));     // for many problems n <= 10^5 to logn will at max 20

    graph.resize(n + 1);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin>>u>>v;
        // cout<<u<<" "<<v<<"\n";
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    depth[0] = -1;
    dfsBinaryLifting(1, 0);
    while(q--){
        int u, v;
        cin>>u>>v;
        // cout<<u<<" "<<v<<"\n";
        // cout<<LCA2Ptr(u, v)<<"\n";
        cout<<distance(u, v)<<"\n";
    }
}
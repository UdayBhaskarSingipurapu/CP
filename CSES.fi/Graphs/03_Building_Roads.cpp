#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<vector<int>> roads;
vector<bool> vis;

void dfs(int node, vector<int>& grp){
    vis[node] = true;
    grp.push_back(node);
    
    for(int adj: graph[node]){
        if(!vis[adj]) dfs(adj, grp);
    }
}

int main(){
    cin>>n>>m;
    graph = vector<vector<int>>(n + 1);
    while(m--){
        int u, v;
        cin>>u>>v;
        graph[u].push_back(v); 
        graph[v].push_back(u); 
    }
    vis = vector<bool>(n + 1, false);
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            vector<int> grp;
            dfs(i, grp);
            roads.push_back(grp);
        }
    }
    if(roads.size() == 1){
        cout<<0;
        return 0;
    }
    cout<<roads.size() - 1<<"\n";
    for(int i = 0; i < roads.size() - 1; i++){
        cout<<roads[i][roads[i].size() - 1]<<" "<<roads[i + 1][0]<<"\n";
    }
}
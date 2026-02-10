#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> par, cycle;
vector<bool> vis;
bool found = false;

void dfs(int u, int p){
    if(found) return;

    vis[u] = true;
    par[u] = p;
    for(int v: graph[u]){
        if(v == p) continue;

        if(vis[v]){
            found = true;
            cycle.push_back(v);

            int cur = u;
            while(cur != v){
                cycle.push_back(cur);
                cur = par[cur];
            }
            cycle.push_back(v);
            return;
        }
        dfs(v, u);
        if(found) return;
    }
}


int main(){
    cin>>n>>m;
    graph = vector<vector<int>>(n + 1);
    while(m--){
        int u,v ;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    par = vector<int>(n + 1);
    cycle = vector<int>();
    vis = vector<bool>(n + 1, false);

    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            found = false;
            dfs(i, -1);
            if(found){
                cout<<cycle.size()<<'\n';
                for(int i: cycle) cout<<i<<" ";
                return 0;
            }
        }
    }
    if(!found) {
        cout<<"IMPOSSIBLE";
    }
}
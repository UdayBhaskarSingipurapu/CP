#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> par;

int bfs(){
    queue<int> q;
    vector<int> dist(n + 1, -1);
    q.push(1);
    dist[1] = 0;
    int steps = 0;

    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            int node = q.front();
            q.pop();
            if(node == n) return steps;
            for(int adj: graph[node]){
                if(dist[adj] == -1){
                    dist[adj] = dist[node] + 1;
                    par[adj] = node;
                    q.push(adj);
                }
            }
        }
        steps++;
    }
    return -1;
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

    par = vector<int>(n + 1);
    iota(par.begin(), par.end(), 0);

    int steps = bfs();
    if(steps == -1){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    vector<int> path;
    while(par[n] != n){
        path.push_back(n);
        n = par[n];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    
    cout<<steps + 1<<"\n";
    for(int i: path){
        cout<<i<<" ";
    }
}
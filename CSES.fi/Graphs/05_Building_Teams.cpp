#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> team;

bool bfs(int node){
    queue<int> q;
    q.push(node);
    team[node] = 1;

    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            int node = q.front();
            q.pop();
            for(int adj: graph[node]){
                if(team[adj] != -1 && team[node] == team[adj]) return false;
                else if(team[adj] == -1){
                    q.push(adj);
                    if(team[node] == 1) team[adj] = 2;
                    else team[adj] = 1;
                }
            }
        }
    }
    return true;
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
    
    team = vector<int>(n + 1, -1);
    for(int i = 1; i <= n; i++){
        if(team[i] == -1){
            if(!bfs(i)){
                cout<<"IMPOSSIBLE";
                return 0;
            }

        }
    }
    for(int i = 1; i <= n; i++) cout<<team[i]<<" ";
    
}
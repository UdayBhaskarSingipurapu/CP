#include<bits/stdc++.h>
using namespace std;

int dfs(vector<vector<int>>& graph, int node, int par, vector<int>& subs){
    int cnt = 0;
    for(int adj: graph[node]){
        if(adj == par) continue;
        cnt += dfs(graph, adj, node, subs);
    }
    subs[node] = cnt;
    return cnt + 1;
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> graph(n + 1);
    for(int i = 2; i <= n; i++){
        int x;
        cin>>x;
        graph[x].push_back(i);
    }
    vector<int> subs(n + 1, 0);
    dfs(graph, 1, 0, subs);
    for(int i = 1; i <= n; i++) cout<<subs[i]<<" ";
}\
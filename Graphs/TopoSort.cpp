// #include<bits/stdc++.h>
#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> vis;

void dfs(int node, stack<int> &st){
    vis[node] = true;
    for(int adj: graph[node]){
        if(!vis[adj]){
            dfs(adj, st);
        }
    }
    st.push(node);
}

int main(){
    int n, m;
    cin>>n>>m;
    graph.resize(n + 1);
    vis.resize(n + 1);
    while(m--){
        int u, v;
        cin>>u>>v;
        graph[u].push_back(v);
    }

    stack<int> st;
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            dfs(i, st);
        }
    }
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
}
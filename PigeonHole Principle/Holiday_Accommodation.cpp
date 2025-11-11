#include<bits/stdc++.h>
using namespace std;

int dfs(vector<vector<pair<int, int>>> &graph, int n, int node, int par, long long &ans){

    int currTreeSize = 1;
    for(auto adj: graph[node]){
        int v = adj.first, wt = adj.second;
        if(v == par) continue;

        int childTreeSize = dfs(graph, n, v, node, ans);
        long long edgeContribution = 1LL * 2 * min(childTreeSize, n - childTreeSize) * wt;
        ans += edgeContribution;
        currTreeSize += childTreeSize;
    }
    return currTreeSize;
}

int main(){
    int t;
    cin>>t;
    int l = 1;
    while(l <= t){
        int n;
        cin>>n;
        vector<vector<pair<int, int>>> graph(n + 1);
        for(int i = 0; i < n - 1; i++){
            int u, v, w;
            cin>>u>>v>>w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        long long ans = 0;
        dfs(graph, n, 1, -1, ans);
        cout<<"Case #"<<l<<": "<<ans<<"\n";
        l++;
    }
}
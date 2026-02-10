#include<bits/stdc++.h>
using namespace std;

long long n, m;
vector<vector<pair<long long, long long>>> graph;

vector<long long> dijkstra(long long node){
    vector<long long> dist(n + 1, LLONG_MAX);
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
    pq.push({0, node});
    dist[node] = 0;

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(d > dist[u]) continue;
        for(auto adj: graph[u]){
            long long v = adj.first, wt = adj.second;
            if(dist[v] > d + wt){
                dist[v] = d + wt;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}


int main(){
    cin>>n>>m;
    graph = vector<vector<pair<long long, long long>>>(n + 1);
    while(m--){
        long long u, v, w;
        cin>>u>>v>>w;
        graph[u].push_back({v, w});
    }
    vector<long long> dist = dijkstra(1);
    for(long long i = 1; i <= n; i++){
        cout<<dist[i]<<" ";
    }
}
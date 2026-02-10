#include<bits/stdc++.h>
using namespace std;

long long n, m, q;
vector<vector<pair<long long, long long>>> graph;
vector<vector<long long>> allDist;

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
    cin>>n>>m>>q;
    graph = vector<vector<pair<long long, long long>>>(n + 1);
    allDist = vector<vector<long long>>(n + 1, vector<long long>(n + 1, LLONG_MAX));
    while(m--){
        long long u, v, w;
        cin>>u>>v>>w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        allDist[u][v] = min(allDist[u][v], w);
        allDist[v][u] = min(allDist[v][u], w);
    }
    // for(int i = 1; i <= n; i++){
    //     allDist[i] = dijkstra(i);
    // }
    for(int i = 1; i <= n; i++){
        allDist[i][i] = 0;
    }
    for(int via = 1; via <= n; via++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(allDist[i][via] != LLONG_MAX && allDist[via][j] != LLONG_MAX && allDist[i][j] > allDist[i][via] + allDist[via][j]){
                    allDist[i][j] = allDist[i][via] + allDist[via][j];
                }
            }
        }
    }
    while(q--){
        int u, v;
        cin>>u>>v;
        if(allDist[u][v] == LLONG_MAX) cout<<-1<<"\n";
        else cout<<allDist[u][v]<<"\n";
    }
}
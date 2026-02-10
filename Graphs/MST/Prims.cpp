#include <bits/stdc++.h>
using namespace std;

/*
 Prim's Algorithm
 ----------------
 Finds the Minimum Spanning Tree of a connected, undirected graph.

 Graph is represented as an adjacency list:
 adj[u] = { {v, weight}, ... }
*/

long long primMST(int n, vector<vector<pair<int,int>>> &adj) {
    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    long long mstCost = 0;

    // start from node 0
    pq.push({0, 0}); // {weight, node}

    while(!pq.empty()) {
        auto [wt, u] = pq.top();
        pq.pop();
        if(inMST[u]) continue;
        inMST[u] = true;
        mstCost += wt;
        // add all edges from u
        for(auto &[v, w] : adj[u]) {
            if(!inMST[v]) {
                pq.push({w, v});
            }
        }
    }

    return mstCost;
}

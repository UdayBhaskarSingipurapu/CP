// We have a tree with n vertices numbered 1,2,…,n.

// You are given an array edges where edges[i] = [ui, vi, wi] indicates vertex ui connects vertex vi and has a weight wi.

// For different vertices u and v, let f(u,v) be the greatest weight of an edge contained in the shortest path from Vertex u to Vertex v.

// Find over sum of f(u, v) for every node pair

// Constraints:

// 2 <= n <= 10^5

// 1 <= ui, vi <= n

// 1 <= wi <= 10^7

// Example 1:

// Input: n = 3, edges = [[1,2,10],[2,3,20]]
 
// Output: 50
 
// Explanation: We have f(1,2)=10, f(2,3)=20, and f(1,3)=20, so we should print their sum, or 50.

#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b, long long &contribution, int w) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        // contribution of this edge
        contribution += 1LL * w * sz[a] * sz[b];

        // union by size
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

long long solve(int n, vector<vector<int>>edges){
    sort(edges.begin(), edges.end(),
            [](auto &a, auto &b) {
                return a[2] < b[2];
            });

    DSU dsu(n);
    long long ans = 0;

    for(auto &e : edges) {
        dsu.unite(e[0], e[1], ans, e[2]);
    }

    return ans;
}
//  Strategy:
//  ---------
//  1. Sort edges by increasing weight
//  2. Process edges one by one using DSU
//  3. Each edge contributes:
//         weight * (size of component A) * (size of component B)
//     when it merges two components
// */
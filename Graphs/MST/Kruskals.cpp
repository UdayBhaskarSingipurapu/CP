#include <bits/stdc++.h>
using namespace std;

/*
 Kruskal's Algorithm
 ------------------
 Finds the Minimum Spanning Tree using DSU.
*/

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return false;

        if(sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

long long kruskalMST(int n, vector<vector<int>> &edges) {
    // edges: {u, v, w}
    sort(edges.begin(), edges.end(),[](auto &a, auto &b) {
            return a[2] < b[2];
        });

    DSU dsu(n);
    long long mstCost = 0;

    for(auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if(dsu.unite(u, v)) {
            mstCost += w;
        }
    }

    return mstCost;
}

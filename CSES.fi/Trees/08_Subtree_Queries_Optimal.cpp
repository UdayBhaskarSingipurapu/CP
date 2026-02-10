#include<bits/stdc++.h>
using namespace std;

int n, q;
vector<int> nodeVal, tin, tout, flat;
vector<vector<int>> tree;
int timer = 1;

void dfs(int node, int par){
    tin[node] = timer;
    flat[timer] = nodeVal[node];
    timer++;

    for(int adj: tree[node]){
        if(adj == par) continue;
        dfs(adj, node);
    }

    tout[node] = timer - 1;
}

struct SegmentTree {
    int n;
    vector<long long> seg;
    SegmentTree(int n){
        this->n = n;
        seg.resize(4 * n);
    }

    void build(int idx, int low, int high){
        if(low == high){
            seg[idx] = flat[low]; 
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * idx, low, mid);
        build(2 * idx + 1, mid + 1, high);
        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }

    void update(int idx, int low, int high, int up_idx, int up_val){
        if(low == high){
            seg[idx] = up_val;
            return;
        }

        int mid = low + (high - low) / 2;

        if(mid >= up_idx){
            update(2 * idx, low, mid, up_idx, up_val);
        }
        else {
            update(2 * idx + 1, mid + 1, high, up_idx, up_val);
        }

        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }

    long long query(int idx, int low, int high, int rlow, int rhigh){
        if(low > rhigh || high < rlow) return 0;

        if(rlow <= low && rhigh >= high){
            return seg[idx];
        }

        int mid = low + (high - low) / 2;
        return query(2 * idx, low, mid, rlow, rhigh) + query(2 * idx + 1, mid + 1, high, rlow, rhigh);
    }
};


int main() {
    cin>>n>>q;
    tree = vector<vector<int>>(n + 1);
    nodeVal = tin = tout = flat = vector<int>(n + 1);

    for(int i = 1; i <= n; i++){
        cin>>nodeVal[i];
    }

    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, 0);

    SegmentTree segTree(n);
    segTree.build(1, 1, n);

    while(q--){
        int t; cin>>t;
        if(t == 1){
            int u, d;
            cin>>u>>d;
            segTree.update(1, 1, n, tin[u], d);
        }
        else {
            int u;
            cin>>u;
            cout<<segTree.query(1, 1, n, tin[u], tout[u])<<"\n";
        }
    }
}
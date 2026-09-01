#include<bits/stdc++.h>
using namespace std;

int n, q;
vector<vector<int>> tree;
vector<int> nodeVal, tin, tout, flat;
int timer = 1;

void eulerTour(int node, int par){
    tin[node] = timer;
    flat[tin[node]] += nodeVal[node];
    timer++;

    for(int adj: tree[node]){
        if(adj == par) continue;
        eulerTour(adj, node);
    }

    tout[node] = timer;
    flat[tout[node]] -= nodeVal[node];
    timer++;
}

struct SegmentTree {
    int n;
    vector<long long> seg;

    SegmentTree(int n){
        this->n = n;
        seg = vector<long long>(4 * n);
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
            seg[idx] += up_val;
            return;
        }
        
        int mid = low + (high - low) / 2;
        if(mid >= up_idx){
            update(2 * idx, low, mid, up_idx, up_val);
        }
        else update(2 * idx + 1, mid + 1, high, up_idx, up_val);
        
        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }

    long long query(int idx, int low, int high, int rl, int rh){
        if(low > rh || high < rl) return 0;

        if(low >= rl && high <= rh) return seg[idx];

        int mid = low + (high - low) / 2;
        return query(2 * idx, low, mid, rl, rh) + query(2 * idx + 1, mid + 1, high, rl, rh);
    }
};

int main(){
    cin>>n>>q;
    tree = vector<vector<int>>(n + 1);
    nodeVal = tin = tout = vector<int>(n + 1);
    flat = vector<int>(2 * n + 2);

    for(int i = 1; i <= n; i++){
        cin>>nodeVal[i];
    }

    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    eulerTour(1, 0);

    SegmentTree segTree(2 * n);
    segTree.build(1, 1, 2 * n);

    while(q--){
        int t;
        cin>>t;
        if(t == 1){
            int u, x;
            cin>>u>>x;
            int diff = x - nodeVal[u];
            nodeVal[u] = x;
            segTree.update(1, 1, 2 * n, tin[u], diff);
            segTree.update(1, 1, 2 * n, tout[u], -diff);
        }
        else {
            int u;
            cin>>u;
            cout<<segTree.query(1, 1, 2 * n, 1, tin[u])<<'\n';
        }
    }
}
#include<bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> seg;
    SegmentTree(int n) {
        seg.resize(4 * n);
    }
    
    void build(vector<int> &ar, int idx, int low, int high, int lvl){
        if(low == high){
            seg[idx] = ar[low];
            return;
        }
        
        int mid = low + (high - low) / 2;
        build(ar, 2 * idx + 1, low, mid, lvl - 1);
        build(ar, 2 * idx + 2, mid + 1, high, lvl - 1);
        
        if(lvl % 2 == 0){
            seg[idx] = (seg[2 * idx + 1] ^ seg[2 * idx + 2]);
        }
        else {
            seg[idx] = (seg[2 * idx + 1] | seg[2 * idx + 2]);
        }
    }
    
    void update(int idx, int low, int high, int up_idx, int up_val, int lvl){
        if(low == high){
            seg[idx] = up_val;
            return;
        }
        
        int mid = low + (high - low) / 2;
        if(up_idx <= mid){
            update(2 * idx + 1, low, mid, up_idx, up_val, lvl - 1);
        }
        else {
            update(2 * idx + 2, mid + 1, high, up_idx, up_val, lvl - 1);
        }
        if(lvl % 2 == 0){
            seg[idx] = (seg[2 * idx + 1] ^ seg[2 * idx + 2]);
        }
        else {
            seg[idx] = (seg[2 * idx + 1] | seg[2 * idx + 2]);
        }
    }
};

vector<int> solve(int n, vector<int>& a, vector<vector<int>>& queries){
    vector<int> ans;
    int lvl = n;
    n = 1 << n;
    SegmentTree segmentTree(n);
    segmentTree.build(a, 0, 0, n - 1, lvl);
    
    for(auto& q: queries){
        segmentTree.update(0, 0, n - 1, q[0] - 1, q[1], lvl);
        ans.push_back(segmentTree.seg[0]);
    }
    return ans;
}

int main() {
    int n, m;
    cin>>n>>m;
    int sz = 1 << n;
    vector<int> ar(sz);
    for(int &i: ar) cin>>i;
    vector<vector<int>> queries;
    while(m--){
        int p, b;
        cin>>p>>b;
        queries.push_back({p, b});
    }
    vector<int> ans = solve(n, ar, queries);
    for(int &i: ans){
        cout<<i<<"\n";
    }
}
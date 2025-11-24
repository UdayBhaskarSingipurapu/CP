#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<long long> seg, lazy;
    SegmentTree(int n){
        seg.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void buildTree(vector<int>& ar, int idx, int low, int high){
        if(low == high){
            seg[idx] = ar[low];
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(ar, 2 * idx + 1, low, mid);
        buildTree(ar, 2 * idx + 2, mid + 1, high);
        seg[idx] = max(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    void lazyPropagateDown(int idx, int low, int high){
        if(lazy[idx] != 0){
            seg[idx] += lazy[idx];
            if(low != high){
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void updateTree(int idx, int low, int high, int l, int r, int val){
        // Complete previous lazy updates
        lazyPropagateDown(idx, low, high);

        // check for overlaps
        if(low > r || high < l) return;

        if(low >= l && high <= r){
            seg[idx] += val;
            if(low != high){
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }

        int mid = low + (high - low) / 2;
        updateTree(2 * idx + 1, low, mid, l, r, val);
        updateTree(2 * idx + 2, mid + 1, high, l, r, val);
        seg[idx] = max(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    long long query(int idx, int low, int high, int l, int r){
        // complete previous lazy updates
        lazyPropagateDown(idx, low, high);

        if(low > r || high < l) return LLONG_MIN;

        if(low >= l && high <= r) return seg[idx];

        int mid = low + (high - low) / 2;
        long long left = query(2 * idx + 1, low, mid, l, r);
        long long right = query(2 * idx + 2, mid + 1, high, l, r);
        return max(left, right);
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> ar(n);
        for(int &i: ar) cin>>i;
        SegmentTree segTree(n);
        segTree.buildTree(ar, 0, 0, n - 1);
        
        int q;
        cin>>q;
        while(q--){
            int type;
            cin>>type;
            if(type == 1){
                int l, r;
                cin>>l>>r;
                cout<<segTree.query(0, 0, n - 1, l - 1, r - 1)<<"\n";
            }
            else {
                int l, r, val;
                cin>>l>>r>>val;
                segTree.updateTree(0, 0, n - 1, l - 1, r - 1, val);
            }
        }
        cout<<"\n";
    }
    return 0;
}
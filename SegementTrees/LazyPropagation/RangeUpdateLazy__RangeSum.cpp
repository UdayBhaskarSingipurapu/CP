#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> seg, lazy;
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
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    void lazyPropagateDown(int idx, int low, int high){
        if(lazy[idx] != 0){
            seg[idx] += (high - low + 1) * lazy[idx];
            // propagate lazy update downwards for it children if present
            if(low != high){    // children will definetely there if low != high
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void updateTree(int idx, int low, int high, int l, int r, int val){
        // Step 1: Update the previous remaining updates and propagate downwards for children
        lazyPropagateDown(idx, low, high);

        // step 2: check for the overlaps
        if(low > r || high < l) return;     // No overlap

        if(low >= l && high <= r){      // Complete overlap
            // Update the seg[idx] for this range with val * total children
            seg[idx] += (high - low + 1) * val;
            // propagate update downwards
            if(low != high){
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }
        
        // Partial overlap
        int mid = low + (high - low) / 2;
        updateTree(2 * idx + 1, low, mid, l, r, val);
        updateTree(2 * idx + 2, mid + 1, high, l, r, val);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int high, int l, int r){
        // If any previous lazy updates are remaining complete it
        lazyPropagateDown(idx, low, high);

        // check overlaps
        if(low > r || high < l) return 0;

        if(low >= l && high <= r) return seg[idx];

        int mid = low + (high - low) / 2;
        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);
        return left + right;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin>>t;
    while(t--){
        int n, m;
        cin>>n>>m;
        vector<int> ar(n);
        for(int &i: ar) cin>>i;
        SegmentTree segmentTree(n);
        segmentTree.buildTree(ar, 0, 0, n - 1);

        while(m--){
            int type;
            cin>>type;
            if(type == 1){
                int l, r;
                cin>>l>>r;
                cout<<segmentTree.query(0, 0, n - 1, l, r)<<"\n";
            }
            else {
                int l, r, val;
                cin>>l>>r>>val;
                segmentTree.updateTree(0, 0, n - 1, l, r, val);
            }
        }
    }
    return 0;
}
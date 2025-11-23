#include<bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> seg;
    SegmentTree(int n){
        seg.resize(4 * n);
    }
    
    void buildTree(vector<int>& freq, int idx, int low, int high){
        if(low == high){
            seg[idx] = freq[low];
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(freq, 2 * idx + 1, low, mid);
        buildTree(freq, 2 * idx + 2, mid + 1, high);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    
    int query(int idx, int low, int high, int l, int r){
        if(low >= l && high <= r) return seg[idx];
        if(low > r || high < l) return 0;
        int mid = low + (high - low) / 2;
        return query(2 * idx + 1, low, mid, l, r) + query(2 * idx + 2, mid + 1, high, l, r);
    }
    
    void update(int idx, int low, int high, int up_idx, int val){
        if(low == high){
            seg[idx] += val;
            return;
        }
        int mid = low + (high - low) / 2;
        if(up_idx <= mid){
            update(2 * idx + 1, low, mid, up_idx, val);
        }
        else update(2 * idx + 2, mid + 1, high, up_idx, val);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
};


class Solution {
public:
    int inversionCount(vector<int> &arr) {
        // Code Here
        int mx = arr[0];
        for(int i = 1; i < arr.size(); i++){
            mx = max(mx, arr[i]);
        } 
        mx++;
        vector<int> freq(mx, 0);
        for(int i: arr){
            freq[i]++;
        }
        SegmentTree segmentTree(mx);
        segmentTree.buildTree(freq, 0, 0, mx - 1);
        int ans = 0;
        for(int i = 0; i < arr.size(); i++){
            segmentTree.update(0, 0, mx - 1, arr[i], -1);
            ans += segmentTree.query(0, 0, mx - 1, 1, arr[i] - 1);
        }
        return ans;
    }
};
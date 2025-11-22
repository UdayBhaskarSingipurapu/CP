// Given an array of N size, perform queries of the form:

// Query 1 (i,j): Find max(a[i], a[i+1],...,a[j])
// Query 2 (i,x): a[i]=x

// Input Format
// The first line of input contains T - number of test cases. First line of each test case contains N - size of the array. The second line contains N integers - elements of the array. The third line contains Q - number of queries. Each of the next Q lines are of the form:
// 1 i j, or
// 2 i x

// Output Format
// For each test case, find and print the maximum element for each query for type-1, separated by new line. Print a extra newline between different test cases.

// Constraints
// 30 points
// 1 <= T <= 100
// 1 <= N, Q <= 100

// 120 points
// 1 <= T <= 100
// 1 <= N, Q <= 10000

// General
// -109 <= a[i], x <= 109
// 1 <= i <= j <= N

// Example
// Input
// 2
// 3
// 3 -1 2
// 3
// 1 1 3
// 2 3 10
// 1 1 3
// 5
// 10 -8 -3 4 1
// 4
// 1 2 3
// 2 2 8
// 1 2 5
// 1 1 5

// Output
// 3
// 10

// -3
// 8
// 10

#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> seg;
    SegmentTree(int n){
        seg.resize(4 * n);
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

    int query(vector<int>& ar, int idx, int low, int high, int l, int r){

        // our current range completely lies in query range
        if(low >= l && high <= r) return seg[idx];

        // current range is out of query range
        if(low > r || high < l) return INT_MIN;

        // partial overlap
        int mid = low + (high - low) / 2;
        return max(query(ar, 2 * idx + 1, low , mid, l, r), query(ar, 2 * idx + 2, mid + 1, high, l, r));
    }

    void update(int idx, int low, int high, int up_idx, int up_val){
        // Base case -> we reached the index where we need to update
        if(low == high){
            seg[idx] = up_val;
            return;
        }
        int mid = low + (high - low) / 2;
        // check where the index lies in segment tree range -> whether in left sub tree or right sub tree
        if(up_idx <= mid){
            update(2 * idx + 1, low, mid, up_idx, up_val);
        }
        else {
            update(2 * idx + 2, mid + 1, high, up_idx, up_val);
        }
        seg[idx] = max(seg[2 * idx + 1], seg[2 * idx + 2]);
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
        SegmentTree segmentTree(n);
        segmentTree.buildTree(ar, 0, 0, n - 1);
        int q;
        cin>>q;
        while(q--){
            int type, l, r;
            cin>>type>>l>>r;
            if(type == 1){
                int ans = segmentTree.query(ar, 0, 0, n - 1, l - 1, r - 1);
                cout<<ans<<"\n";
            }
            else segmentTree.update(0, 0, n - 1, l - 1, r);
        }
        cout<<"\n";
    }
    return 0;
}
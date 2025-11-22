// Given an array of N size, answer queries of the form:
// Query(i,j): Max (a[i], a[i+1],...,a[j])

// Input Format
// The first line of input contains T - number of test cases. First line of each test case contains N - size of the array. The second line contains N integers - elements of the array. The third line contains Q - number of queries. Each of the next Q lines contains 2 space separated indexes - i and j.

// Output Format
// For each test case, find and print the maximum element for each query, separated by newline. Print a extra new line between different test cases.

// Constraints
// 30 points
// 1 <= T <= 100
// 1 <= N, Q <= 100

// 120 points
// 1 <= T <= 100
// 1 <= N, Q <= 10000

// General
// -109 <= a[i] <= 109
// 1 <= i <= j <= N

// Example
// Input
// 2
// 3
// 3 -1 2
// 2
// 2 3
// 1 3
// 5
// 10 -8 -3 4 1
// 3
// 2 3
// 1 4
// 5 5

// Output
// 2
// 3

// -3
// 10
// 1

// Explanation 

// Example 1:
// Q1: max(ar[2], ar[3]) = max(-1, 2) = 2
// Q2: max(ar[1], ar[2], ar[3]) = max(3, -1, 2) = 3

// Example 2:
// Q1: max(ar[2], ar[3]) = max(-8, -3) = -3
// Q2: max(ar[1], ar[2], ar[3], ar[4]) = max(10, -8, -3, 4) = 10
// Q3: max(ar[5]) = max(1) = 1


#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> seg;
    SegmentTree(int n){
        seg.resize(4 * n, INT_MIN);
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
            int l, r;
            cin>>l>>r;
            int ans = segmentTree.query(ar, 0, 0, n - 1, l - 1, r - 1); // 1-based indexing
            cout<<ans<<"\n";
        }
        cout<<"\n";
    }
    return 0;
}
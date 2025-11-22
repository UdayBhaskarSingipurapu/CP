// Ashish and Bit Operations
// Ashish the beginner programmer has a sequence a, consisting of 2^n non-negative integers: a1, a2, ..., a2^n. Ashish is currently studying bit operations. To better understand how they work, Ashish decided to calculate some value v for a.

// Namely, it takes several iterations to calculate value v. At the first iteration, Ashish writes a new sequence a1 or a2, a3 or a4, ..., a2^n - 1 or a2^n, consisting of 2^(n - 1) elements. In other words, he writes down the bit-wise OR of adjacent elements of sequence a. At the second iteration, Ashish writes the bitwise exclusive OR of adjacent elements of the sequence obtained after the first iteration. At the third iteration Ashish writes the bitwise OR of the adjacent elements of the sequence obtained after the second iteration. And so on; the operations of bitwise exclusive OR and bitwise OR alternate. In the end, he obtains a sequence consisting of one element, and that element is v.

// Let's consider an example. Suppose that sequence a = (1, 2, 3, 4). Then let's write down all the transformations :

// (1, 2, 3, 4) → (1 or 2 = 3, 3 or 4 = 7) → (3 xor 7 = 4). The result is v = 4.

// You are given Ashish's initial sequence. But to calculate value v for a given sequence would be too easy, so you are given additional queries. Each query is a pair of integers p, b. Query p, b means that you need to perform the assignment ap = b and calculate the new value v for the new sequence a.

// Return an array containing answer for each query respectively.

// Constraints:

// 1<= n <= 17

// 1<= queries.length <= 10^5

// 1<= ai, b <= 2^30

// 1<= p <= 2^n

// Example:

// Input

// n = 2 , a =[1, 6, 3, 5]
// queries = [
//     [1, 4],
//     [3, 4],
//     [1, 2],
//     [1, 2]
// ]
// Output

// [1, 3, 3, 3]

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

vector<int> solve(int n, vector<int>a, vector<vector<int>> queries){
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
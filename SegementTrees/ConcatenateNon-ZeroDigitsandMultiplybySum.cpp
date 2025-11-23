#include<bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;

struct Node {
    long long con_val;
    long long sum;
    long long len;
    Node(){
        con_val = 0;
        sum = 0;
        len = 0;
    }
    Node(long long _con_val, long long _sum, long long _len){
        con_val = _con_val;
        sum = _sum;
        len = _len;
    }
};

struct SegmentTree {
    vector<Node> seg;
    SegmentTree(int n){
        seg.resize(4 * n);
    }

    long long pow10(long long a, long long b){
        long long res = 1;
        while(b){
            if(b & 1){
                res = (1LL * res * a) % mod;
            }
            b >>= 1;
            a = (1LL * a * a) % mod;
        }
        return res;
    }

    Node merge(Node a, Node b){
        Node res;
        res.con_val = ((a.con_val * pow10(10, b.len) % mod) + b.con_val) % mod;
        res.sum = (a.sum + b.sum) % mod;
        res.len = a.len + b.len;
        return res;
    }

    void buildTree(string& s, int idx, int low, int high){
        if(low == high){
            if(s[low] == '0'){
                seg[idx] = Node();
            }
            else {
                seg[idx] = Node(s[low] - '0', s[low] - '0', 1);
            }
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(s, 2 * idx + 1, low, mid);
        buildTree(s, 2 * idx + 2, mid + 1, high);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    Node query(int idx, int low, int high, int l, int r){
        if(low >= l && high <= r) return seg[idx];
        if(low > r || high < l) return Node(0, 0, 0);
        int mid = low + (high - low) / 2;
        Node q1 = query(2 * idx + 1, low, mid, l, r);
        Node q2 = query(2 * idx + 2, mid + 1, high, l, r);
        return merge(q1, q2);
    }
};

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();
        SegmentTree segmentTree(n);
        segmentTree.buildTree(s, 0, 0, n - 1);

        vector<int> ans;
        for(auto& q: queries){
            Node res = segmentTree.query(0, 0, n - 1, q[0], q[1]);
            long long val = (res.con_val * res.sum) % mod;
            ans.push_back(val);
        }
        return ans;
    }
};
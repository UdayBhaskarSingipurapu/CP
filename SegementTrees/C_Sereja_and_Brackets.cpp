#include<bits/stdc++.h>
using namespace std;

struct Node {
    int op, cl, full;
    Node(){
        op = cl = full = 0;
    }
    Node(int _op, int _cl, int _full){
        op = _op;
        cl = _cl;
        full = _full;
    }
};

struct SegmentTree {
    vector<Node> seg;
    SegmentTree(int n){
        seg.resize(4 * n);
    }

    Node merge(Node a, Node b){
        int full = a.full + b.full + min(a.op, b.cl);
        int op = a.op + b.op - min(a.op, b.cl);
        int cl = a.cl + b.cl - min(a.op, b.cl);
        return Node(op, cl, full);
    }

    void buildTree(string& ar, int idx, int low, int high){
        if(low == high){
            if(ar[low] == '(') {
                seg[idx] = Node(1, 0, 0);
            }
            else seg[idx] = Node(0, 1, 0);
            return;
        }

        int mid = low + (high - low) / 2;
        buildTree(ar, 2 * idx + 1, low, mid);
        buildTree(ar, 2 * idx + 2, mid + 1, high);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    Node query(int idx, int low, int high, int l, int r){

        // Complete overlap of segment range with query range
        if(low >= l && high <= r){
            return seg[idx];
        }
        // No overlap 
        if(low > r || high < l) return Node(0, 0, 0);

        // Partial overlap
        int mid = low + (high - low) / 2;
        Node q1 = query(2 * idx + 1, low, mid, l, r);
        Node q2 = query(2 * idx + 2, mid + 1, high, l, r);
        return merge(q1, q2);
    }
};

int main(){
    string s;
    cin>>s;
    int n = s.length();
    SegmentTree segmentTree(n);
    segmentTree.buildTree(s, 0, 0, n - 1);
    int m;
    cin>>m;
    while(m--){
        int l, r;
        cin>>l>>r;
        Node ans = segmentTree.query(0, 0, n - 1, l - 1, r - 1);
        cout<<ans.full * 2<<"\n";
    }
}
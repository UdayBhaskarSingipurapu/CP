/*******************************************************
 * Problem Statement
 *
 * Problem: Distance Queries / Lowest Common Ancestor
 *
 * You are given a tree consisting of n nodes numbered
 * from 1 to n. The tree is represented by n-1 edges,
 * where each edge connects two nodes bidirectionally.
 *
 * You are also given q queries. In each query, you are
 * asked to find the Lowest Common Ancestor (LCA) of two
 * nodes u and v.
 *
 * The Lowest Common Ancestor of two nodes u and v in a
 * tree is the deepest node that is an ancestor of both.
 *
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 1 ≤ q ≤ 10^5
 * 1 ≤ u, v ≤ n
 *
 * Input:
 * n
 * n-1 lines of edges
 * q
 * q lines of queries (u v)
 *
 * Output:
 * For each query, print the LCA of u and v.
 *
 * Expected Solution:
 * Preprocess the tree using Binary Lifting and answer
 * each LCA query in O(log n) time.
 *******************************************************/

#include<bits/stdc++.h>
using namespace std;

vector<int> dep, par;
vector<vector<int>> graph;

void dfs(int node, int parent){
    dep[node] = dep[parent] + 1;
    par[node] = parent;
    
    for(int adj: graph[node]){
        if(adj != parent){
            dfs(adj, node);
        }
    }
}

int LCA2Ptr(int u, int v){
    if(u == v) return u;
    if(dep[u] < dep[v]) swap(u, v);

    int diff = dep[u] - dep[v];
    while(diff--){
        u = par[u];
    }
    while(u != v){
        u = par[u];
        v = par[v];
    }
    return u;
}

vector<int> depth;
vector<vector<int>> parent;
int m = 20;

void dfsBinaryLifting(int node, int par){
    depth[node] = depth[par] + 1;

    parent[node][0] = par;
    for(int i = 1; i < m; i++){
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }

    for(int adj: graph[node]){
        if(adj != par){
            dfsBinaryLifting(adj, node);
        }
    }
}

int LCABinaryLifting(int u, int v){
    if(u == v) return u;
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    
    for(int i = m - 1; i >= 0; i--){
        if((diff >> i) & 1){
            u = parent[u][i];
        }
    }
    for(int i = m - 1; i >= 0; i--){
        if(parent[u][i] != parent[v][i]){
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}


int main(){
    int n;
    cin>>n;

    depth.resize(n + 1);
    parent.resize(n + 1, vector<int>(m));     // for many problems n <= 10^5 to logn will at max 20

    graph.resize(n + 1);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfsBinaryLifting(1, 0);
    int q;
    cin>>q;
    while(q--){
        int u, v;
        cin>>u>>v;
        // cout<<u<<" "<<v<<"\n";
        // cout<<LCA2Ptr(u, v)<<"\n";
        cout<<LCABinaryLifting(u, v);
    }
}

/*
-------------------------------------------------------
Explanation: Naive 2-Pointer LCA Approach (COMMENTED)
-------------------------------------------------------

This is the simplest way to find LCA using only:
- parent[] array (immediate parent of each node)
- depth[] array (depth from the root)

Idea:
1. Every node has a unique path to the root.
2. If two nodes are at different depths, lift the deeper
   node upward until both nodes are at the same depth.
3. Once both nodes are on the same level, move BOTH nodes
   upward together (like two pointers).
4. The first node where both pointers meet is the LCA.

Why this works:
- Any ancestor above the LCA is common.
- The first common ancestor encountered while moving
  upward is the LOWEST common ancestor.

Important limitation:
- In the worst case (skewed tree), this approach takes
  O(n) time per query.
- With many queries, this becomes too slow.
- This is why Binary Lifting is preferred.

Use cases:
- Small trees
- Very few queries
- Learning / understanding LCA basics

-------------------------------------------------------
*/
// Naive 2-Pointer LCA:
// - Preprocessing: O(n)
// - Query: O(n)
// - Not suitable for large inputs

/*
-------------------------------------------------------
Explanation of Approach (Binary Lifting for LCA)
-------------------------------------------------------

We preprocess the tree so that for every node, we know
its 2^k-th ancestor for all k such that 2^k ≤ n.

Key observations:
1. Any integer can be represented as a sum of powers of 2.
2. We can lift a node upwards by decomposing the required
   jump into powers of two.
3. This allows us to move nodes up in O(log n) time.

Data Structures Used:
- depth[node]  : depth of each node from the root
- parent[node][i] :
    the 2^i-th ancestor of node
- graph        : adjacency list representation of tree

Steps:
1. Run DFS from root to compute depth[] and parent[node][0].
2. Build parent[node][i] using DP:
      parent[node][i] = parent[parent[node][i-1]][i-1]
3. To find LCA(u, v):
   a) Make sure u and v are at the same depth.
   b) Lift the deeper node up.
   c) Lift both nodes together from highest power of 2
      to lowest until their parents differ.
   d) The parent of either node is the LCA.
-------------------------------------------------------
*/

/*
-------------------------------------------------------
Time and Space Complexity Analysis
-------------------------------------------------------

Preprocessing:
- DFS traversal: O(n)
- Building binary lifting table: O(n log n)

Query:
- Each LCA query: O(log n)

Total Complexity:
- Time: O(n log n + q log n)
- Space: O(n log n)

Why this is optimal:
- Handles up to 10^5 nodes and queries efficiently
- Much faster than naive O(n) LCA per query
- Standard and widely accepted solution in interviews
  and competitive programming.

-------------------------------------------------------
*/
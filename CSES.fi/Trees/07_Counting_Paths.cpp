#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> tree, parents;
vector<long long> pathCount;
vector<int> depth;
int LOG = 0;

// void bfs(int u, int v){
//     queue<int> q;
//     vector<int> par(n + 1);
//     vector<bool> vis(n + 1, false);
//     q.push(u);
//     par[u] = u;
//     vis[u] = true;

//     while(!q.empty()){
//         int node = q.front();
//         q.pop();
//         if(node == v) break;
//         for(int adj: tree[node]){
//             if(!vis[adj]){
//                 vis[adj] = true;
//                 par[adj] = node;
//                 q.push(adj);
//             }
//         }
//     }

//     int curr = v;
//     while(curr != par[curr]){
//         pathCount[curr]++;
//         curr = par[curr];
//     }
//     pathCount[curr]++;
// }

// Fill Depth and store ancestors using binary lifting
void fillDepthAndAncestors(int node, int par, int d){
    depth[node] = d;
    parents[node][0] = par;
    for(int i = 1; i < LOG; i++){
        parents[node][i] = parents[parents[node][i - 1]][i - 1];
    }

    for(int adj: tree[node]){
        if(adj == par) continue;
        fillDepthAndAncestors(adj, node, d + 1);
    }
}

// LCA of 2 nodes using Binary Lifting
int LCA(int u, int v){
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];

    for(int i = LOG - 1; i >= 0; i--){
        if((diff >> i) & 1){
            u = parents[u][i];
        }
    }
    if(u == v) return u;

    for(int i = LOG - 1; i >= 0; i--){
        if(parents[u][i] != parents[v][i]){
            u = parents[u][i];
            v = parents[v][i];
        }
    }
    return parents[u][0];
}

// Accumulate counts of nodes
void dfs(int node, int par){

    for(int adj: tree[node]){
        if(adj == par) continue;
        dfs(adj, node);
        pathCount[node] += pathCount[adj];
    }
}

int main(){
    cin>>n>>m;
    tree = vector<vector<int>>(n + 1);
    for(int i = 1; i < n; i++){
        int u, v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    while((1 << LOG) <= n) LOG++;
    parents = vector<vector<int>>(n + 1, vector<int>(LOG));
    depth = vector<int>(n + 1, 0);
    pathCount = vector<long long>(n + 1, 0);

    fillDepthAndAncestors(1, 0, 0);

    while(m--){
        int u, v;
        cin>>u>>v;
        // bfs(u, v);
        pathCount[u]++;
        pathCount[v]++;
        int lca = LCA(u, v);
        pathCount[lca]--;
        pathCount[parents[lca][0]]--;
    }

    dfs(1, 0);

    for(int i = 1; i <= n; i++) cout<<pathCount[i]<<" ";
}

/*

Goal:
For every node, find how many paths pass through it.

=========================================================
WHY NAIVE FAILS
---------------------------------------------------------
- Finding path for each query using BFS/DFS costs O(n)
- m queries → O(n * m) → TLE

So we need to process ALL paths together efficiently.

=========================================================
CORE IDEA
---------------------------------------------------------
1. Tree has a UNIQUE path between any two nodes.
2. Instead of updating every node on every path,
    we mark only where paths START and where they STOP.
3. A single DFS will convert these markers into final answers.

This is called:
"Tree Difference Array + DFS Accumulation"

=========================================================
STEP 1: ROOT THE TREE
---------------------------------------------------------
- Root the tree at node 1 (or any node).
- Needed so that "parent" and "ancestor" are well-defined.

=========================================================
STEP 2: PREPROCESS LCA (Lowest Common Ancestor)
---------------------------------------------------------
Why LCA?
- For any path (u, v), the path splits at LCA(u, v).
- LCA tells us where two upward flows meet.

How?
- Use DFS to compute depth[] and immediate parent[]
- Build binary lifting table parent[k][v]
- LCA query in O(log n)

=========================================================
STEP 3: DIFFERENCE MARKING FOR EACH PATH
---------------------------------------------------------
For a path between u and v:

Let L = LCA(u, v)

We do FOUR updates:

1) cnt[u]++        // start path flow from u
2) cnt[v]++        // start path flow from v
3) cnt[L]--        // remove double count at LCA
4) cnt[parent[L]]--// stop path from going above LCA

Intuition:
- +1 means "this path starts contributing here"
- -1 means "this path stops contributing here"

IMPORTANT:
- parent[L] is the FIRST node that must NOT be on the path
- subtracting here blocks the flow upward

=========================================================
STEP 4: DFS ACCUMULATION (POST-ORDER)
---------------------------------------------------------
Run a DFS from the root:

For each node:
- First process all children
- Add each child's cnt value to the current node

Effect:
- Path contributions "flow upward"
- Stops exactly where we placed -1 markers

=========================================================
STEP 5: FINAL RESULT
---------------------------------------------------------
After DFS:
- cnt[x] = number of paths that pass through node x

No extra processing needed.

=========================================================
TIME COMPLEXITY
---------------------------------------------------------
- LCA preprocessing: O(n log n)
- Each path query: O(log n)
- DFS accumulation: O(n)

Total: O((n + m) log n)  ✅

=========================================================
KEY INVARIANT (MEMORIZE THIS)
---------------------------------------------------------
"Each path contributes +1 to all nodes from u to LCA
 and from v to LCA, and zero above LCA."

=========================================================
WHY parent(LCA) IS SUBTRACTED
---------------------------------------------------------
- DFS automatically propagates values to ancestors
- To STOP propagation, we subtract at the FIRST non-path node
- That node is parent(LCA)
- One subtraction is enough to block all higher ancestors

=========================================================
MENTAL MODEL
---------------------------------------------------------
Think of path contribution as water flowing upward:
- Starts at u and v
- Merges at LCA
- Is blocked right above LCA

=========================================================
END
=========================================================
*/

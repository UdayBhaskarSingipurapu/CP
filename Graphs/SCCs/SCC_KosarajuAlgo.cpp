/********************************************************************************************
PROBLEM STATEMENT
-------------------
Given a directed graph with N nodes and M edges, find the number of
Strongly Connected Components (SCCs) in the graph.

A Strongly Connected Component (SCC) is a maximal group of vertices such that
every vertex is reachable from every other vertex in the group.

INPUT:
- First line: Two integers N and M (number of nodes and edges)
- Next M lines: Each line contains two integers u v representing a directed edge u → v

OUTPUT:
- Print a single integer: the total number of SCCs in the graph

Example:
Input:
9 11
1 2
2 3
3 1
3 4
4 5
5 6
6 4
6 7
7 8
8 9
9 7

Output:
3

--------------------------------------------------------------------------------------------

ALGORITHM USED: KOSARAJU'S ALGORITHM
--------------------------------------

Kosaraju’s Algorithm finds SCCs using **two DFS passes**.

🔹 STEP 1: Topological Ordering (DFS on Original Graph)
- Perform DFS on the original graph.
- Push nodes into a stack after exploring all outgoing edges.
- This stack stores nodes in decreasing order of finishing time.

🔹 STEP 2: Reverse the Graph
- Reverse every edge (u → v becomes v → u).

🔹 STEP 3: DFS on Reversed Graph (Using Stack Order)
- Pop nodes from the stack one by one.
- If a node is unvisited, start DFS from it in the reversed graph.
- All nodes visited in this DFS form **one SCC**.

🔹 STEP 4: Count SCCs
- Each DFS in step 3 represents one strongly connected component.

TIME COMPLEXITY: O(N + M)
SPACE COMPLEXITY: O(N + M)

--------------------------------------------------------------------------------------------
********************************************************************************************/

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph, reverseGraph;
vector<bool> vis;

void buildTopoSort(int node, stack<int>& st){
    vis[node] = true;
    for(int adj: graph[node]){
        if(!vis[adj]){
            buildTopoSort(adj, st);
        }
    }
    st.push(node);
}

void dfs(int node, vector<int>& component){
    vis[node] = true;
    component.push_back(node);
    for(int adj: reverseGraph[node]){
        if(!vis[adj]) dfs(adj, component);
    }
}

int main(){
    int n, m;
    cin>>n>>m;
    graph.resize(n + 1);
    reverseGraph.resize(n + 1);
    while(m--){
        int u, v;
        cin>>u>>v;
        graph[u].push_back(v);
        reverseGraph[v].push_back(u);
    }
    // build topo order for original graph
    stack<int> st;
    vis.assign(n + 1, false);
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            buildTopoSort(i, st);
        }
    }

    // for each node in topo order start dfs
    int sccTotal = 0;
    unordered_map<int, vector<int>> mp;
    vis.assign(n + 1, false);
    while(!st.empty()){
        int top = st.top();
        st.pop();
        if(!vis[top]){
            vector<int> component;
            dfs(top, component);
            sccTotal++;
            mp[sccTotal] = component;
        }
    }
    cout<<sccTotal<<"\n";
}
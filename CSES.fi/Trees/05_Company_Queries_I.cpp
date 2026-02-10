#include<bits/stdc++.h>
using namespace std;

int n, q;
vector<vector<int>> tree;
vector<vector<int>> parents;
vector<int> depth;
int LOG = 0;

void dfs(int node, int par, int d){
    depth[node] = d;
    parents[node][0] = par;
    for(int i = 1; i < LOG; i++){
        parents[node][i] = parents[parents[node][i - 1]][i - 1];
    }

    for(int adj: tree[node]){
        if(adj == par) continue;
        dfs(adj, node, d + 1);
    }
}

int main(){
    cin>>n>>q;
    tree.resize(n + 1);

    while((1 << LOG) <= n) LOG++;
    parents.resize(n + 1, vector<int>(LOG, 0));


    for(int i = 2; i <= n; i++){
        int x;
        cin>>x;
        tree[x].push_back(i);
    }
    depth.resize(n + 1);
    dfs(1, 0, 0);

    while(q--){
        int u, k;
        cin>>u>>k;
        // cout<<depth[u]<<" ";
        if(depth[u] < k){
            cout<<-1<<'\n';
        }
        else {
            for(int i = LOG; i >= 0; i--){
                if((k >> i) & 1){
                    u = parents[u][i];
                }
            }
            cout<<u<<'\n';
        }
    }
}
// Game Routes
// A game has n levels numbered 1 to n, connected by some teleporters. Your task is to get from level 1 to level n.

// You are given an array teleporters  where teleporters[i]= [ui, vi]  is a directed edge from level ui to level  vi .

// The game has been designed so that there are no directed cycles in the underlying graph.

// Return in how many ways you can complete the game. Since, the result may be large, print it modulo 10^9 + 7 .

// Constraints:

// 1<= n <= 10^5

// 1<= teleporters.length <= 10^5

// 1<= ui, vi <= n

// Input : n = 5, teleporters = {{1,  2}, {1, 3}, {2, 3}, {1,  4}, {4, 5}}
// Output : 1

#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007 

int gameRoutes(int n, vector<vector<int>> teleporters)
{
    long long x,y;
    vector<vector<int>>v(n+1);
    vector<int>ind(n+1);
    vector<long long>dp(n+1);
    for(int i=0;i<teleporters.size();i++)
    {
        x=teleporters[i][0],y=teleporters[i][1];
        v[x].push_back(y);
        ind[y]++;
    }
    queue<int>q;
    vector<int>topo;
    for(int i=1;i<=n;i++)
    {
        if(ind[i]==0)
        {
            q.push(i);
        }
    }
    while(q.size())
    {
        x=q.front();
        q.pop();
        topo.push_back(x);
        for(auto itr:v[x])
        {
            ind[itr]--;
            if(ind[itr]==0)
            {
                q.push(itr);
            }
        }
    }
    dp[1]=1;
    for(auto itr:topo)
    {
        for(auto it:v[itr])
        {
            dp[it]=(dp[it]+dp[itr])%mod;
        }
    }
    return dp[n];
}
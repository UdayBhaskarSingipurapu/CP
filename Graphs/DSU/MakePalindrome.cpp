// Make Palindrome
// You are given a sequence of n positive integers: a=(a1​,a2​,…an​). You can do the operation below zero or more times. At least how many operations are needed to make A a palindrome?

// Choose a pair (x,y) of positive integers, and replace every occurrence of x in a with y.

// Here, we say a is a palindrome if and only if ai​=an+1−i​ holds for every (1≤i≤n).

// Constraints:

// 1 <= n <= 2*10^5

// 1 <= ai <= 2*10^5

// Example:

// Input: n= 8 , a= [1, 5, 3, 2, 5, 2, 3, 1]
 
// Output: 2
 
// Explanation:
// Initially, we have A=(1,5,3,2,5,2,3,1).
// After replacing every occurrence of 3 in A with 2, we have A=(1,5,2,2,5,2,2,1).
// After replacing every occurrence of 2 in A with 5, we have A=(1,5,5,5,5,5,5,1).
// In this way, we can make A a palindrome in two operations, which is the minimum needed.

#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, size;
    DSU(int n){
        par.resize(n);
        size.assign(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    
    int find(int x){
        return par[x] == x ? x : par[x] = find(par[x]);
    }
    
    void unite(int u, int v){
        int x = find(u), y = find(v);
        if(x != y){
            if(size[x] >= size[y]){
                par[y] = x;
                size[x] += size[y];
            }
            else {
                par[x] = y;
                size[y] += size[x];
            }
        }
    }
    
    int getSize(int x){
        return size[x];
    }
};

int solve(int n, vector<int> a){
    DSU dsu(200001);
    set<int> s(a.begin(), a.end());
    for(int i = 0; i < n / 2; i++){
        if(a[i] != a[n - i - 1]){
            dsu.unite(a[i], a[n - i - 1]);
        }
    }
    int ans = 0;
    for(int i: s){
        if(dsu.find(i) == i){
            ans += dsu.getSize(i) - 1;
        }
    }
    return ans;
}
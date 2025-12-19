#include<bits/stdc++.h>
using namespace std;

vector<int> wei, val;
vector<vector<long long>> dp;

long long backtrack(int n, int w){
    if(n < 0) return 0;

    long long notp = backtrack(n - 1, w);
    long long pick = 0;
    if(w - wei[n] >= 0){
        pick = 0LL + val[n] + backtrack(n - 1, w - wei[n]);
    }
    return max(notp, pick);
}

long long memoize(int n, int w){
    if(n < 0) return 0;
    if(dp[n][w] != -1) return dp[n][w];

    long long notp = memoize(n - 1, w);
    long long pick = 0;
    if(w - wei[n] >= 0){
        pick = 0LL + val[n] + memoize(n - 1, w - wei[n]);
    }
    return dp[n][w] = max(notp, pick);
}

long long tabulation(int n, int w){
    dp.assign(n + 1, vector<long long>(w + 1, 0));

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= w; j++){
            long long notp = dp[i - 1][j];
            long long pick = 0;
            if(j - wei[i - 1] >= 0){
                pick = 0LL + val[i - 1] + dp[i - 1][j - wei[i - 1]];
            }
            dp[i][j] = max(notp, pick);
        }
    }
    return dp[n][w];
}

long long spaceOptimize(int n, int w){
    vector<long long> curr(w + 1, 0);
    for(int i = 1; i <= n; i++){
        vector<long long> prev(w + 1, 0);
        for(int j = 0; j <= w; j++){
            long long notp = curr[j];
            long long pick = 0;
            if(j - wei[i - 1] >= 0){
                pick = 0LL + val[i - 1] + curr[j - wei[i - 1]];
            }
            prev[j] = max(pick, notp);
        }
        curr = prev;
    }
    return curr[w];
}

int main() {
    int n, w;
    cin>>n>>w;
    wei.resize(n); val.resize(n);
    for(int i = 0; i < n; i++) cin>>wei[i]>>val[i];
    // dp.assign(n, vector<long long>(w + 1, -1));
    // cout<<memoize(n - 1, w);

    // cout<<tabulation(n, w);

    cout<<spaceOptimize(n, w);
}
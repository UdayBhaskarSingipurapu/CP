#include<bits/stdc++.h>
using namespace std;

long long backtrack(long long n, long long k){
    if(n == 0) return 1;
    if(n < 0) return 0;

    long long ans = 0;
    for(long long i = 1; i <= k; i++){
        ans += backtrack(n - i, k);
    }
    return ans;
}

long long memoize(long long n, long long k, vector<long long>& dp){
    if(n == 0) return 1;
    if(n < 0) return 0;
    if(dp[n] != -1) return dp[n];

    long long ans = 0;
    for(long long i = 1; i <= k; i++){
        ans += memoize(n - i, k, dp);
    }
    return dp[n] = ans;
}

long long iterateDp(long long n, long long k){
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for(long long i = 1; i <= n; i++){
        long long ans = 0;
        for(long long j = 1; j <= k; j++){
            if(i - j >= 0)
                ans += dp[i - j];
        }
        dp[i] = ans;
    }
    return dp[n];
}

long long optimizedIterativeDp(long long n, long long k){
    vector<long long> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    for(long long i = 2; i <= n; i++){
        dp[i] = (2 * dp[i - 1]) - ((i - k - 1) >= 0 ? dp[i - k - 1] : 0);
        // cout<<dp[i]<<" ";
    }
    return dp[n];
}


int main() {
    long long n, k;
    cin>>n>>k;
    cout<<backtrack(n, k)<<"\n";

    // memoization
    vector<long long> dp(n + 1, -1);
    cout<<memoize(n, k, dp)<<"\n";

    // iterative dp
    cout<<iterateDp(n, k)<<"\n";

    // optimized iterative dp
    cout<<optimizedIterativeDp(n, k);
}
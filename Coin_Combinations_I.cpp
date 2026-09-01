#include<bits/stdc++.h>
using namespace std;

static const int MOD = 1e9+7;
static int dp[1000005];
int coins[105];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin>>n>>x;

    for(int i = 0; i < n; i++)
        cin>>coins[i];

    sort(coins, coins + n);

    dp[0] = 1;
    for(int i = 0; i <= x; i++){
        if(dp[i] == 0) continue;
        for(int j = 0; j < n; j++){
            int next = i + coins[j];
            if(next > x) break;
            dp[next] += dp[i];
            if(dp[next] >= MOD) dp[next] -= MOD;
        }
    }

    cout<<dp[x];
}

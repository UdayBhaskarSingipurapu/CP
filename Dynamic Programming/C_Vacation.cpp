#include<bits/stdc++.h>
using namespace std;

vector<int> a, b, c;
vector<vector<int>> dp;

int backtrack(int n, int task){
    if(n == 0) {
        if(task == 1){
            return a[n];
        }
        else if(task == 2) return b[n];
        return c[n];
    }
    if(dp[n][task] != -1) return dp[n][task];
    
    int ans = 0;
    if(task == 1){
        ans = max(ans, a[n] + max(backtrack(n - 1, 2), backtrack(n - 1, 3)));
    }
    else if(task == 2){
        ans = max(ans, b[n] + max(backtrack(n - 1, 1), backtrack(n - 1, 3)));
    }
    else {
        ans = max(ans, c[n] + max(backtrack(n - 1, 1), backtrack(n - 1, 2)));
    }
    return dp[n][task] = ans;
}

int main(){
    int n;
    cin>>n;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    for(int i = 0; i < n; i++) cin>>a[i]>>b[i]>>c[i];

    dp.assign(n, vector<int>(4, -1));
    int ans = backtrack(n - 1, 1);
    ans = max(ans, backtrack(n - 1, 2));
    ans = max(ans, backtrack(n - 1, 3));
    
    cout<<ans;
}

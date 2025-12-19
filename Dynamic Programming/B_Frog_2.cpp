#include<bits/stdc++.h>
using namespace std;

vector<int> dp;

int backtrack(vector<int>& nums, int n, int k, int idx){
    if(idx == n - 1) return 0;
    if(dp[idx] != -1) return dp[idx];

    int ans = 1e9;
    for(int i = 1; i <= k; i++){
        if(idx + i < n){
            ans = min(ans, abs(nums[i + idx] - nums[idx]) + backtrack(nums, n, k, idx + i));
        }
    }

    return dp[idx] = ans;
}

int main(){
    int n, k;
    cin>>n>>k;
    vector<int> heights(n);
    for(int &i: heights) cin>>i;
    dp.resize(n, -1);
    cout<<backtrack(heights, n, k, 0);
}
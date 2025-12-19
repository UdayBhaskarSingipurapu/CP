#include<bits/stdc++.h>
using namespace std;

vector<int> dp;

int backtrack(vector<int>& nums, int n, int idx){
    if(idx == n - 1) return 0;
    if(dp[idx] != -1) return dp[idx];

    int ans = 1e9;
    if(idx + 1 < n) {
        ans = min(ans, abs(nums[idx + 1] - nums[idx]) + backtrack(nums, n, idx + 1));
    }

    if(idx + 2 < n) {
        ans = min(ans, abs(nums[idx + 2] - nums[idx]) + backtrack(nums, n, idx + 2));
    }

    return dp[idx] = ans;
}

int main(){
    int n;
    cin>>n;
    vector<int> heights(n);
    for(int &i: heights) cin>>i;
    dp.resize(n, -1);
    cout<<backtrack(heights, n, 0);
}
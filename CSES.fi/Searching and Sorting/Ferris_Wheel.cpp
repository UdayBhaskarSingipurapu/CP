#include<bits/stdc++.h>
using namespace std;


int main() {
    int n, x;
    cin>>n>>x;
    vector<int> nums(n);
    for(int &i: nums) cin>>i;
    sort(nums.begin(), nums.end());

    int i = 0, j = n - 1;
    int ans = 0;
    while(i <= j){
        if(nums[i] + nums[j] <= x){
            ans++;
            i++; j--;
        }
        else {
            ans++; j--;
        }
    }
    cout<<ans;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int &i: nums){
        cin>>i;
    }
    sort(nums.begin(), nums.end());
    int med = nums[n / 2];
    long long ans = 0;
    for(int i: nums){
        ans += abs(i - med);
    }
    cout<<ans;
}
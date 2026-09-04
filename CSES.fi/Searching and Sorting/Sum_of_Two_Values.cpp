#include<bits/stdc++.h>
using namespace std;

int bs(vector<pair<int, int>> &nums, int low, int high, int tar){
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(nums[mid].first == tar){
            return nums[mid].second;
        }
        else if(nums[mid].first < tar){
            low = mid + 1;
        }
        else high = mid - 1;
    }
    return -1;
}

int main(){
    int n, x;
    cin>>n>>x;
    // unordered_map<int, int> mp;
    // vector<int> ans;
    // for(int i = 0; i < n; i++){
    //     int a;
    //     cin>>a;
    //     int diff = x - a;
    //     if(mp.count(diff)){
    //         ans.push_back(mp[diff] + 1);
    //         ans.push_back(i + 1);
    //         break;
    //     }
    //     mp[a] = i;
    // }
    // if(ans.size() == 0){
    //     cout<<"IMPOSSIBLE";
    // }
    // else {
    //     cout<<ans[0]<<" "<<ans[1];
    // }

    vector<pair<int, int>> nums;
    nums.reserve(n);
    for(int i = 0; i < n; i++){
        int a;
        cin>>a;
        nums.push_back({a, i + 1});
    }
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        int diff = x - nums[i].first;
        int idx = bs(nums, i + 1, n - 1, diff);
        if(idx != -1){
            cout<<nums[i].second<<" "<<idx;
            return 0;
        }
    }
    cout<<"IMPOSSIBLE";
}
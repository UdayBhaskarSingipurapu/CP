// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     cin>>n;
//     vector<int> nums(n);
//     for(int &i: nums){
//         cin>>i;
//     }
//     unordered_map<int, int> mp;
//     int l = 0, ans = 0;
//     for(int r = 0; r < n; r++){
//         if(mp.count(nums[r])){
//             l = max(l, mp[nums[r]] + 1);
//         }
//         mp[nums[r]] = r;
//         ans = max(ans, r - l + 1);
//     }
//     cout<<ans;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vector<int> nums(n);

    for(int &x : nums)
        cin>>x;

    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    vector<int> last(sorted.size(), -1);

    int l = 0;
    int ans = 0;

    for(int r = 0; r < n; r++) {
        int id = lower_bound(sorted.begin(), sorted.end(), nums[r]) - sorted.begin();

        if(last[id] >= l)
            l = last[id] + 1;

        last[id] = r;

        ans = max(ans, r - l + 1);
    }

    cout << ans;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin>>n>>m;
    vector<int> nums(n), pos(n + 1);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
        pos[nums[i]] = i + 1;
    }
    int ans = 1;
    for(int i = 1; i < n; i++){
        if(pos[i] > pos[i + 1]) ans++;
    }
    // cout<<ans<<'\n';

    while(m--){
        int i, j;
        cin>>i>>j;
        int a = nums[i - 1];
        int b = nums[j - 1];
        set<int> affected = {a - 1, a, b - 1, b};

        for(int x : affected) {
            if(x >= 1 && x < n && pos[x] > pos[x + 1])
                ans--;
        }

        swap(nums[i - 1], nums[j - 1]);
        swap(pos[a], pos[b]);

        for(int x : affected) {
            if(x >= 1 && x < n && pos[x] > pos[x + 1])
                ans++;
        }

        cout<<ans<<'\n';
    }
}
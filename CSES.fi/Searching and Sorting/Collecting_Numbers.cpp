#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    vector<int> pos(n + 1);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
        pos[nums[i]] = i;
    }

    int ans = 1;
    for(int i = 1; i < n; i++){
        if(pos[i] > pos[i + 1])
            ans++;
    }

    cout<<ans;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> ar(n);
    long long totalSum = 0;
    for(auto &i: ar){
        cin>>i;
        totalSum += i;
    }
    long long ans = LLONG_MAX;
    for(int mask = 0; mask < (1 << n); mask++){
        long long subSum = 0;
        for(int i = 0; i < n; i++){
            if((mask >> i) & 1){
                subSum += ar[i];
            }
        }
        long long rem = totalSum - subSum;
        ans = min(ans, abs(subSum - rem));
    }
    cout<<ans;
}
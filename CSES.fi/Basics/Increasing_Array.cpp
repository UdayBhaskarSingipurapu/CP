#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    long long ans = 0, prev;
    cin>>prev;
    for(int i = 0; i < n - 1; i++){
        int x;
        cin>>x;
        if(x < prev){
            ans += 0ll + prev - x;
            x = prev;
        }
        prev = x;
    }
    cout<<ans;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int ans = 0;
    while(n){
        n /= 5;
        ans += n;
    }
    cout<<ans;
}
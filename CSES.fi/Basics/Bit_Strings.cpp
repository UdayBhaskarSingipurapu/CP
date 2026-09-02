#include<bits/stdc++.h>
using namespace std;

void solve(int b, int a = 2){
    long long sum = 1;
    int mod = 1e9 + 7;
    while(b){
        if(b & 1){
            sum = (1ll * sum * a) % mod;
        }
        a = (1ll * a * a) % mod;
        b >>= 1;
    }
    cout<<sum;
}

int main(){
    int n;
    cin>>n;
    solve(n);
}
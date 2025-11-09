#include<bits/stdc++.h>
using namespace std;

int pow(int a, int b){
    int res = 1;
    while(b){
        if(b & 1){
            res *= a;
        }
        b >>= 1;
        a *= a;
    }
    return res;
}

int mod = 1e9 + 7;

long long powMod(int a, int b){
    long long res = 1;
    while(b){
        if(b & 1){
            res = (1LL * res * a) % mod;
            // res %= mod;
        }
        a = (1ll * a * a) % mod;
        // a %= mod;
        b >>= 1;
    }
    return res;
}

int main(){
    int a = 20, b = 50;
    cout<<powMod(a, b);
}
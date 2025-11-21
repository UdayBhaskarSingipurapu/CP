#include<bits/stdc++.h>
using namespace std;
#define ll long long

void primeSieve(vector<int>& sieve){
    sieve[0] = sieve[1] = 0;
    for(ll i = 2; i <= 1e3; i++){
        if(sieve[i]){
            cout<<i<<" ";
            for(ll j = 1LL * i * i; j <= 1e3; j += i){
                sieve[j] = 0;
            }
        }
    }
}

int main(){
    vector<int> sieve(1e3, 1);
    primeSieve(sieve);
}
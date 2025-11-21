#include<bits/stdc++.h>
using namespace std;

void bruteForce(int n){
    for(int i = 2; i <= n; i++){
        if(n % i == 0){
            while(n % i == 0){
                n /= i;
                cout<<i<<" ";
            }
        }
    }   
}

// O(sqrt(n))
// Obs: once N is reduced to a prime no. the only factor of the number is N itself
// If a no. doesn't have any factor till sqrt(N) then it is a prime
void sqrtTC(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            while(n % i == 0){
                n /= i;
                cout<<i<<" ";
            }
        }
    }
    // By the time we come out of loop, there can be only 2 possibilities.. n==1 or n is a prime
    // if n == 1 then that's end of our prime factorization
    // else curr N is one of prime factor for actual input N
    if(n != 1){
        cout<<n;
    }
}

// Most Optimal O(nloglogn + logn)
void lognTC(int n){
    vector<int> sieve(n + 1, 1);
    sieve[0] = sieve[1] = 0;
    for(int i = 2; i <= n; i++){
        if(sieve[i] == 1){
            sieve[i] = i;
            for(int j = i * i; j <= n; j += i){
                sieve[j] = i;
            }
        }
    }

    while(n / sieve[n] != 1){
        cout<<sieve[n]<<" ";
        n = n / sieve[n];
    }
    cout<<n<<" ";
}

int main(){
    int n;
    cin>>n;

    // bruteForce(n);
    // sqrtTC(n);
    lognTC(n);
}
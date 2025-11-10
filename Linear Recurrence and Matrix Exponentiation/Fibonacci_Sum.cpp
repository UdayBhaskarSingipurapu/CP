
#include<bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;

struct Matrix {
    int mat[2][2];
    Matrix(){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                mat[i][j] = 0;
            }
        }
    }
};

Matrix multiply(Matrix a, Matrix b){
    Matrix c;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                c.mat[i][j] = (c.mat[i][j] + 1LL * a.mat[i][k] * b.mat[k][j]) % mod;
            }
        }
    }
    return c;
}

Matrix power(Matrix t, long long b){
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = 1;
    while(b){
        if(b & 1){
            res = multiply(res, t);
        }
        b >>= 1;
        t = multiply(t, t);
    }
    return res;
}


long long fib(long long n){
    if(n == 0) return 0;
    if(n == 1 || n == 2) return 1;
    n -= 2;
    Matrix t;
    t.mat[0][0] = t.mat[0][1] = t.mat[1][0] = 1;
    Matrix res = power(t, n);
    return (res.mat[0][0] + res.mat[0][1]) % mod;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        long long n, m;
        cin>>n>>m;
        long long ans = ((fib(m + 2) - 1) - (fib(n + 1) - 1) + mod) % mod;
        cout<<ans<<"\n";
    }
}

// Lets say Sn = f(0) + f(1) + f(2) + .... + f(n)
// Lets say Sm = f(0) + f(1) + f(2) + .... + f(m)
// ans = Sm - Sn-1

// Fn = Fn-1 + Fn-2 ->
// Fn-2 = Fn - Fn-1
// Fn-3 = Fn-1 - Fn-2
// Fn4 = Fn-2 - Fn-3
// ............
// F0 = F2 - F1 --- add all Terms both side and by cancelling out terms
// Fn-2 + Fn-3 + Fn-4 + .... + F0 = Fn - F1 
// Sn-2 = Fn - F1(1);
// Sn = Fn+2 - 1
// Sm = Sm+2 - 1

// Sm - Sn-1 = (Fm+2 - 1) - (Fn+1 - 1)
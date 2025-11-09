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
                c.mat[i][j] += (1LL * a.mat[i][k] * b.mat[k][j]) % mod;
            }
        }
    }
    return c;
}

Matrix power(Matrix t, int b){
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
    if(n <= 2) return n;
    n -= 2;
    Matrix t;
    t.mat[0][0] = t.mat[0][1] = t.mat[1][0] = 1;
    Matrix res = power(t, n);
    return res.mat[0][0] + res.mat[0][1];
}

int main(){
    long long n = 10;
    cout<<fib(n);
}
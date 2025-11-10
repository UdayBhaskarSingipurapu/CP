#include<bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;
struct Matrix {
    int mat[3][3];
    Matrix(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat[i][j] = 0;
            }
        }
    }
};

Matrix multiply(Matrix a, Matrix b){
    Matrix c;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                c.mat[i][j] = (c.mat[i][j] + (1LL * a.mat[i][k] * b.mat[k][j]) % mod) % mod;
            }
        }
    }
    return c;
}

Matrix power(Matrix t, long long b){
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = res.mat[2][2] = 1;
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
    if(n <= 0) return 0;
    if(n == 1) return 1;

    Matrix t;
    t.mat[0][0] = t.mat[0][1] = t.mat[0][2] = t.mat[1][1] = t.mat[1][2] = t.mat[2][1] = 1;
    Matrix res = power(t, n - 1);
    return (res.mat[0][0] + res.mat[0][1]) % mod;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        long long n, m;
        cin>>n>>m;
        long long ans = (fib(m) - fib(n - 1) + mod) % mod;
        cout<<ans<<"\n";
    }
}




//       T             Fn             Fn+1
//   | 1, 1, 1|     | Sn   |        | Sn+1  |
//   | 0, 1, 1|     | Fn   |        | Fn+1  |
//   | 0, 1, 0|     | Fn-1 |        | Fn    |
//       T             F2             F3
//   | 1, 1, 1|     | 1   |        | 2  |
//   | 0, 1, 1|     | 1   |        | 1  |
//   | 0, 1, 0|     | 0   |        | 1  |

// We want to compute Sn = F1 + F2 + F3 + ... + Fn efficiently.
// Recall: F(n+2) = F(n+1) + F(n)
// => Sn = F(n+2) - 1     (derived from telescoping sum)
//
// But instead of using this directly, we can build a matrix that
// computes both Fibonacci numbers and their cumulative sum together.

// Define transformation matrix T such that:
// [ S(n+1) ]   =  T  * [ S(n)  ]
// [ F(n+1) ]             [ F(n) ]
// [ F(n)   ]             [ F(n-1) ]

// T = | 1 1 1 |
//     | 0 1 1 |
//     | 0 1 0 |

// Explanation of each row:
// Row 1 → S(n+1) = S(n) + F(n+1)
//               = S(n) + (F(n) + F(n-1))
//               → uses all 3: S(n), F(n), F(n-1)

// Row 2 → F(n+1) = F(n) + F(n-1)
//               → uses 2nd and 3rd columns

// Row 3 → F(n) shifts down → F(n) = F(n) + 0*F(n-1)
//               → [0, 1, 0]

// So if we multiply this T repeatedly (raise it to power n-1),
// we can jump directly to nth Fibonacci and sum.

// Example (base):
// For n = 2 (F1=1, F2=1, S2=2)
//
// State vector:
// [ S2 ] = [ 2 ]
// [ F2 ]   [ 1 ]
// [ F1 ]   [ 1 ]
//
// Let's multiply once with T:
//
//   | 1 1 1|     | 2 |     | 4 |
//   | 0 1 1|  ×  | 1 |  =  | 2 |
//   | 0 1 0|     | 1 |     | 1 |
//
// Interpretation:
// S3 = 4, F3 = 2, F2 = 1
//
// indeed, F3 = 2, and S3 = F1 + F2 + F3 = 1 + 1 + 2 = 4 ✅

// So —
// Initial vector (base) = [ S2, F2, F1 ] = [ 2, 1, 1 ]
// T^k × base → gives [ S(k+2), F(k+2), F(k+1) ]

// Thus:
// fib(n) → F(n)
// sumFib(n) → S(n) = result[0][0]*base[0] + ... = first element of matrix product

// In your code:
// fib(m) - fib(n-1) = Sum(Fn to Fm)

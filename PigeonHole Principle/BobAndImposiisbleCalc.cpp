// To become the king of CP, Bob has to solve the following problem.

// He is given n numbers a1,a2,…,an. Help Bob to calculate:



// As the result can be very big, return it modulo m.

// If you are not familiar with the short notation,  is equal to |a1−a2|⋅|a1−a3|⋅ …… ⋅|a1−an|⋅|a2−a3|⋅|a2−a4|⋅ …… ⋅|a2−an|⋅ …… ⋅|an−1−an|. In other words, this is the product of |ai−aj| for all 1≤i<j≤n.

// Constraints:

// 2 <= n <= 10^5

// 1 <= m <= 1000

// 0 <= ai <= 10^9

// Example:

// Input: n= 2, m= 10, a= [8, 5]
// Output: 3

#include<bits/stdc++.h>
using namespace std;

int solve(int n,int m, vector<int>& a){
    if(n > m) return 0;
    
    int ans = 1;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            int absval = abs(a[i] - a[j]);
            ans = (1LL * ans * absval) % m;
            if(ans == 0) return 0;
        }
    }
    return ans;
}

int main(){
    int n, m;
    cin>>n>>m;
    vector<int> ar(n);
    for(int &i: ar) cin>>i;
    cout<<solve(n, m, ar);
}

// Goal:
//   Compute the product of |ai - aj| for all pairs (i < j),
//   and return the result modulo m.

// Steps:
// 1. Input:
//    - n = number of elements
//    - m = modulo value
//    - a = array of integers

// 2. Observation (Pigeonhole principle):
//    - There are only 'm' distinct remainders modulo m.
//    - If n > m, two numbers must share the same remainder.
//    - Then |ai - aj| will be divisible by m → product % m = 0.
//    - So immediately return 0 if n > m.

// 3. Otherwise (n ≤ m):
//    - Iterate over all unique pairs (i, j) where i < j.
//    - Compute |a[i] - a[j]|.
//    - Multiply it into 'ans' and take modulo m after each step to avoid overflow.
//    - If 'ans' becomes 0 at any point, we can stop early.

// 4. Output the final result 'ans'.

// Time Complexity:
//    O(n²) — which is fine because n ≤ m ≤ 1000 (at most ~10⁶ operations).

// Example:
//    n = 2, m = 10, a = [8, 5]
//    |8 - 5| = 3 → product = 3 % 10 = 3 → Output: 3
// */
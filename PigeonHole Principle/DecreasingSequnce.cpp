// You are given two integers L and R. Find the smallest non-negative integer N such that

// N%L > N%(L+1) > … > N%(R−1) > N%R.

// Here, % is the modulo operator, so A%B is the remainder of A after division by B. For example, 11%3=2.

// Return the smallest possible N if solution exists otherwise return -1.

// Constraints:

// 1 <= L < R <= 10^8

// Example 1:

// Input: L= 4 , R= 6
// Output: 6
// Explanation:
// N=6 satisfies the given condition, since 6%4(=2)>6%5(=1)>6%6(=0). Notice that N=7 also satisfies the condition, but it is larger.
// Example 2:

// Input: L= 1 , R= 2
// Output: -1
// Explanation:
// It is impossible to find a valid solution because for any non-negative integer N.

#include<bits/stdc++.h>
using namespace std;

int solve(int L, int R){
    if(R-L+1 > L) return -1;
    return R;
}

int main(){
    int l, r;
    cin>>l>>r;
    cout<<solve(l, r);
}

// Using the pigeonhole principle:

// There are R-L+1 remainders to assign (pigeons).

// The maximum possible different values these remainders can take are limited by their modulo bases (holes).

// If R-L+1 (the count of pigeons) is greater than the largest possible range of distinct modulo values available (the holes), then it's impossible to assign strictly decreasing remainders to all modulo operations.
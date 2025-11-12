// Given an array  arr, return the number of  integers between l and r, inclusive, that are divisible by at least one of the elements in arr.

// Constraints:

// 1 <= arr.length <= 18

// 1 <= arr[i] <= 10^9

// 1 <= l <= r <= 10^9

// Example:

// Input: l= 579000, r= 987654, a= [1, 2] 
 
// Output: 408655

#include<bits/stdc++.h>
using namespace std;

int numDivisible(int l,int r, vector<int> arr){
    int n = arr.size();
    // find number of elements which are < L and are divisible by atleast one elements in arr
    // find number of elements which are <= R and are divisible bt altleast one elements in arr
    int ans = 0;
    // Generate all possible subsets
    for(int i = 1; i < (1 << n); i++){
        int lcm = 1;
        int cnt = 0;
        for(int j = 0; j < n; j++){
            if((i >> j) & 1){
                lcm = (lcm * (long long)arr[j] / __gcd(lcm, arr[j]));
                cnt++;
            }
            if(lcm > r) break;
        }
        if(lcm > r) continue;
        
        if(cnt % 2 == 0){
            ans -= r/lcm;
            ans += (l - 1)/lcm;
        }
        else {
            ans += r/lcm;
            ans -= (l - 1)/lcm;
        }
    }
    return ans;
}

int main(){
    int n, l, r;
    cin>>n>>l>>r;
    vector<int> ar(n);
    for(int &i: ar) cin>>i;
    cout<<numDivisible(l, r, ar);
}
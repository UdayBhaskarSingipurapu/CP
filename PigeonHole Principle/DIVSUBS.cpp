// You are given a multiset of N integers. Please find such a nonempty subset of it that the sum of the subset's elements is divisible by N. Otherwise, state that this subset doesn't exist.

// Input
// The first line of the input contains an integer T denoting the number of test cases. The description of T test cases follows.
// The first line of each test consists of a single integer N - the size of the multiset.
// The second line of each test contains N single space separated integers - the multiset's elements.

// Output
// For each test case output:

// -1 if the required subset doesn't exist
// If the required subset exists, output two lines. Output the size of the subset on the first line and output the list of indices of the multiset's element that form the required subset. Of course, any number can be taken in the subset no more than once.
// If there are several such subsets, you can output any.

// Constraints
// 1 <= The sum of N over all the test cases <= 10^5
// Each element of the multiset is a positive integer, not exceeding 10^9.

// Example
// Input:
// 1
// 3
// 4 6 10
// Output:
// 1
// 2

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> ar(n);
        for (int &x : ar) cin >> x;

        vector<int> pre(n);
        pre[0] = ar[0] % n;
        for(int i = 1; i < n; i++) {
            pre[i] = (pre[i - 1] + ar[i]) % n;
        }

        bool found = false;

        // Check if any prefix sum is 0
        for(int i = 0; i < n; i++) {
            if(pre[i] == 0) {
                cout << i + 1 << "\n";
                for(int j = 1; j <= i + 1; j++)
                    cout<<j<<" ";
                cout<<"\n";
                found = true;
                break;
            }
        }
        if(found) continue;

        unordered_map<int, int> mp; 
        for(int i = 0; i < n; i++) {
            if(mp.find(pre[i]) != mp.end()) {
                int start = mp[pre[i]] + 1; 
                int end = i + 1;            
                cout<<(end - start + 1)<<"\n";
                for(int j = start; j <= end; j++) {
                    cout<<j<<" ";
                }
                cout<<"\n";
                found = true;
                break;
            } else {
                mp[pre[i]] = i;
            }
        }
        if(!found) {
            cout<<"-1\n";
        }
    }
    return 0;
}

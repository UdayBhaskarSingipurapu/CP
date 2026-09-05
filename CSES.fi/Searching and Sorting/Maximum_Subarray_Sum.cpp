#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    long long sum = 0, maxSum = 0;
    int maxi = INT_MIN;
    for(int i = 0; i < n; i++){
        int x;
        cin>>x;
        sum += x;
        maxi = max(maxi, x);
        if(sum < 0){
            sum = 0;
        }
        maxSum = max(maxSum, sum);
    }
    cout<<(maxi < 0 ? maxi : maxSum);
}
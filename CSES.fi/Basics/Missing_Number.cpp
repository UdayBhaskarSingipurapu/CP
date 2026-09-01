#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    long long givenSum = 0, actualSum = (1ll * n * (n + 1)) / 2;
    for(int i = 0; i < n - 1; i++){
        int x;
        cin>>x;
        givenSum += x;
    }
    cout<<(actualSum - givenSum);
}
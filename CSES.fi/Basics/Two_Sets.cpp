#include<bits/stdc++.h>
using namespace std;

void solve(int n){
    long long sum = (1ll * n * (n + 1)) / 2;
    if(sum % 2 == 1) {
        cout<<"NO";
        return;
    }

    cout<<"YES\n";
    long long halfSum = sum / 2;
    unordered_set<int> st;
    long long currSum = 0;
    int i = 1, j = n;
    while(currSum < halfSum){
        currSum += j;
        st.insert(j);
        j--;
        if(currSum == halfSum) break;
        currSum += i;
        st.insert(i);
        i++;
    }
    cout<<st.size()<<"\n";
    for(int it: st){
        cout<<it<<" ";
    }
    cout<<"\n";
    cout<<n - st.size()<<"\n";
    for(int i = 1; i < n; i++){
        if(!st.count(i)){
            cout<<i<<" ";
        }
    }
}

int main(){
    int n;
    cin>>n;
    solve(n);
}
#include<bits/stdc++.h>
using namespace std;


void solve(int n){
    if(n == 1){
        cout<<1;
        return;
    }
    if(n == 2 || n == 3){
        cout<<"NO SOLUTION";
        return;
    }
    
    else {
        int ev = 2, od = 1;
        
        while(ev <= n){
            cout<<ev<<" ";
            ev += 2;
        }
        while(od <= n){
            cout<<od<<" ";
            od += 2;
        }
    }
}

int main(){
    int n;
    cin>>n;
    solve(n);
}
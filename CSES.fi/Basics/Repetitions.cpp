#include<bits/stdc++.h>
using namespace std;


int main(){
    string s;
    cin>>s;
    int cnt = 1, ans = 1;
    for(int i = 1; i < s.size(); i++){
        while(i < s.size() && s[i] == s[i - 1]){
            cnt++; i++;
        }
        ans = max(ans, cnt);
        cnt = 1;
    }
    cout<<max(ans, cnt);
}
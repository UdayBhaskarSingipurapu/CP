#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin>>s;

    unordered_map<char, int> mp;
    for(char c: s){
        mp[c]++;
    }
    int oddCnt = 0;
    char oddChar;
    for(auto &it: mp){
        if(it.second % 2 == 1){
            oddChar = it.first;
            oddCnt++;
        }
    }
    if(oddCnt > 1){
        cout<<"NO SOLUTION";
        return 0;
    }

    vector<char> ans(s.size());
    int left = 0, right = s.size() - 1;
    for(auto &it: mp){
        char ch = it.first;
        int cnt = it.second, half = cnt / 2;
        for(int i = 0; i < half; i++){
            ans[left++] = ch;
        }
        for(int i = 0; i < half; i++){
            ans[right--] = ch;
        }
    }
    if(s.size() % 2 == 1) ans[s.size() / 2] = oddChar;
    for(int i = 0; i < ans.size(); i++){
        cout<<ans[i];
    }
}
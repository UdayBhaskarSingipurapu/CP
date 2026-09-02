#include<bits/stdc++.h>
using namespace std;

int fact(int n){
    if(n == 1){
        return 1;
    }
    return n * fact(n - 1);
}

int main(){
    string s;
    cin>>s;

    sort(s.begin(), s.end());
    vector<int> freq(26, 0);
    for(char c: s){
        freq[c - 'a']++;
    }
    int total = fact(s.size());
    int cmnFact = 1;
    for(int i = 0; i < 26; i++){
        if(freq[i] > 1){
            cmnFact *= fact(freq[i]);
        }
    }
    int cnt = total / cmnFact;
    cout<<cnt<<"\n";
    do {
        // cnt++;
        cout<<s<<"\n";
    } while (next_permutation(s.begin(), s.end()));
    // cout<<cnt;
    
}
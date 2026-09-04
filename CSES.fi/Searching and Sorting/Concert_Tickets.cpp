#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin>>n>>m;
    vector<int> base(n), maxp(m);
    map<int, int> mp;
    for(int i = 0; i < n; i++){
        cin>>base[i];
        mp[base[i]]++;
    }
    for(int i = 0; i < m; i++){
        cin>>maxp[i];
    }

    for(int i = 0; i < m; i++){
        auto it = mp.upper_bound(maxp[i]);
        if(it == mp.begin()){
            cout<<-1<<"\n";
            continue;
        }
        else {
            --it;
            cout<<it->first<<"\n";
            if(--it->second == 0){
                mp.erase(it);
            }
        }
    }
}
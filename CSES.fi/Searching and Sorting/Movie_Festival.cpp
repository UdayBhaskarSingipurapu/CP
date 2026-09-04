#include<bits/stdc++.h>
using namespace std; 

int main(){
    int n;
    cin>>n;
    vector<pair<int, int>> movies;
    movies.reserve(n);
    for(int i = 0; i < n; i++){
        int st, end;
        cin>>st>>end;
        movies.push_back({st, end});
    }
    sort(movies.begin(), movies.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.second < b.second;
    });
    int lastEnd = 0, ans = 0;
    for(auto &[st, end]: movies){
        if(st >= lastEnd){
            ans++;
            lastEnd = end;
        }
    }
    cout<<ans;
}
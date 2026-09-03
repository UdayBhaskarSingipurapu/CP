#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m, k;
    cin>>n>>m>>k;
    vector<int> app(n), apa(m);
    for(int i = 0; i < n; i++){
        cin>>app[i];
    }
    for(int i = 0; i < m; i++){
        cin>>apa[i];
    }
    sort(app.begin(), app.end());
    sort(apa.begin(), apa.end());

    int ans = 0, i = 0, j = 0;
    while(i < n && j < m){
        if(apa[j] >= app[i] - k && apa[j] <= app[i] + k){
            ans++;
            i++; j++;
        }
        else if(apa[j] < app[i] - k){
            j++;
        }
        else i++;
    }
    cout<<ans;

}
#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<char>> mat;

void dfs(int i, int j){
    if(i < 0 || i >= n || j < 0 || j >= m || mat[i][j] == '#') return;

    mat[i][j] = '#';
    dfs(i + 1, j);
    dfs(i, j + 1);
    dfs(i - 1, j);
    dfs(i, j - 1);
}

int main(){
    cin>>n>>m;
    mat = vector<vector<char>>(n, vector<char>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>mat[i][j];
        }
    }
    int rooms = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == '.'){
                dfs(i, j);
                rooms++;
            }
        }
    }
    cout<<rooms;
}
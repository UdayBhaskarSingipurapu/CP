#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* child[26];
    bool ends;
    string word;

    TrieNode() {
        for(int i = 0; i < 26; i++)
            child[i] = nullptr;
        ends = false;
        word = "";
    }
};

void insert(TrieNode* root, string s) {
    TrieNode* cur = root;
    for(char c : s) {
        int idx = c - 'A';
        if(cur->child[idx] == nullptr)
            cur->child[idx] = new TrieNode();
        cur = cur->child[idx];
    }
    cur->ends = true;
    cur->word = s;
}

vector<int> dx = {-1, -1, 0, 1, 1, 1, 0, -1};
vector<int> dy = {0, 1, 1, 1, 0, -1, -1, -1};

void dfs(char board[][4], int n, int m, int i, int j, TrieNode* node, vector<vector<bool>>& vis, unordered_set<string>& ans) {
    if(i < 0 || i >= n || j < 0 || j >= m || vis[i][j])
        return;

    int idx = board[i][j] - 'A';
    if(node->child[idx] == nullptr)
        return;

    vis[i][j] = true;
    node = node->child[idx];
    if(node->ends)
        ans.insert(node->word);
        
    for(int d = 0; d < 8; d++) {
        dfs(board, n, m, i + dx[d], j + dy[d], node, vis, ans);
    }

    vis[i][j] = false;
}

int main() {
    int n = 3, m = 4;

    vector<string> words = {
        "SNAKE", "FOR", "QUES", "SNACK",
        "SNACKS", "GO", "TUNES", "CAT"
    };

    char board[3][4] = {
        {'S', 'E', 'R', 'T'},
        {'U', 'N', 'K', 'S'},
        {'T', 'C', 'A', 'T'}
    };

    TrieNode* root = new TrieNode();
    for (string s : words)
        insert(root, s);

    unordered_set<string> ans;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vector<vector<bool>> vis(n, vector<bool>(m, false));
            dfs(board, n, m, i, j, root, vis, ans);
        }
    }
\
    for (string s : ans)
        cout << s << " ";
}

#include<bits/stdc++.h>
using namespace std;

class Solution {
    public int longestCommonSubsequence(String text1, String text2) {
        int n = text1.length(), m = text2.length();
        int[][] dp = new int[n + 1][m + 1];
        // return backtrack(text1, text2, 0, 0, dp);
        for(int i = n - 1; i >= 0; i--){
            for(int j = m - 1; j >= 0; j--){
                if(text1.charAt(i) == text2.charAt(j)){
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                }
                else {
                    dp[i][j] = Math.max(dp[i + 1][j], dp[i][j + 1]);
                }
            }
        }
        return dp[0][0];
    }
    // private int backtrack(String s, String t, int i, int j, Integer[][] dp){
    //     if(i == s.length() || j == t.length()) return 0;

    //     if(dp[i][j] != null) return dp[i][j];

    //     int pick = 0;
    //     if(s.charAt(i) == t.charAt(j)){
    //         pick = 1 + backtrack(s, t, i + 1, j + 1, dp);
    //     }
    //     int notp = Math.max(backtrack(s, t, i + 1, j, dp) , backtrack(s, t, i, j + 1, dp));

    //     dp[i][j] = Math.max(pick, notp);
    //     return dp[i][j];
    // }
}
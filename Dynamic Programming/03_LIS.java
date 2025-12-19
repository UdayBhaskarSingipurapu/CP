import java.util.*;

class Solution {
    public int lengthOfLIS(int[] nums) {
        int n = nums.length;
        // int[][] dp = new int[n + 1][n + 1];

        // // tabulation code
        // // base case filling -> since in memoization we have only one base case and it is returning 0 and we initialized our dp table with 0s so need to again fill

        // // start iteration
        // for(int i = n - 1; i >= 0; i--){
        //     for(int prev_idx = i - 1; prev_idx >= -1; prev_idx--){
        //         int notp = dp[i + 1][prev_idx + 1]; // for offset we use prev_idx + 1
        //         int pick = 0;
        //         if(prev_idx == -1 || nums[i] > nums[prev_idx]){
        //             pick = 1 + dp[i + 1][i + 1];
        //         }
        //         dp[i][prev_idx + 1] = Math.max(pick, notp);
        //     }
        // }
        // return dp[0][0];

        // Space optimization
        // int[] dp = new int[n + 1];
        // for(int i = n - 1; i >= 0; i--){
        //     int[] curr = new int[n + 1];
        //     for(int prev_idx = i - 1; prev_idx >= -1; prev_idx--){
        //         int notp = dp[prev_idx + 1];
        //         int pick = 0;
        //         if(prev_idx == -1 || nums[i] > nums[prev_idx]){
        //             pick = 1 + dp[i + 1];
        //         }
        //         curr[prev_idx + 1] = Math.max(pick, notp);
        //     }
        //     dp = curr;
        // }
        // return dp[0];
        
        // return backtrack(nums, n, 0, -1, dp);

        // Another technique for tabulation
        // We use an array dp[] where:
        // dp[i] = Length of the Longest Increasing Subsequence ending at index i
        // So for each index i, we look at all previous indices j < i and check:
        // If nums[j] < nums[i], then nums[i] can extend the subsequence ending at j.
        // So we take the maximum dp value among all valid js and add 1 (for the current number itself).
        // int[] dp = new int[n];
        // for(int i = 0; i < n; i++){
        //     int maxi = 0;
        //     for(int j = i - 1; j >= 0; j--){
        //         if(nums[i] > nums[j]){
        //             maxi = Math.max(maxi, dp[j]);
        //         }
        //     }
        //     dp[i] = 1 + maxi;
        // }
        // int ans = 0;
        // for(int i: dp){
        //     ans = Math.max(ans, i);
        // }
        // return ans;
        
        // LIS using Binary Search
        // Using BS we don't actually store the LIS but we can find the final length of our LIS
        List<Integer> lis = new ArrayList<>();
        int len = 1;
        lis.add(nums[0]);
        for(int i = 1; i < n; i++){
            if(nums[i] > lis.get(len - 1)){
                lis.add(nums[i]);
                len++;
            }
            else {
                int idx = Collections.binarySearch(lis, nums[i]);
                if(idx < 0) idx = -idx - 1;
                lis.set(idx, nums[i]);
            }
        }
        return len;
    }
    private int backtrack(int[] nums, int n, int idx, int prev_idx, int[][] dp){
        if(idx == n) return 0;

        if(dp[idx][prev_idx + 1] != -1){
            return dp[idx][prev_idx + 1];
        }

        // main logic
        int notp = backtrack(nums, n, idx + 1, prev_idx, dp);
        int pick = 0;
        if(prev_idx == -1 || nums[idx] > nums[prev_idx]){
            pick = 1 + backtrack(nums, n, idx + 1, idx, dp);
        }

        dp[idx][prev_idx + 1] = Math.max(pick, notp);
        return dp[idx][prev_idx + 1];
    }
}

// You are given a 0-indexed array of integers nums of length n. You are initially positioned at index 0.

// Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at index i, you can jump to any index (i + j) where:

// 0 <= j <= nums[i] and
// i + j < n
// Return the minimum number of jumps to reach index n - 1. The test cases are generated such that you can reach index n - 1.

 

// Example 1:

// Input: nums = [2,3,1,1,4]
// Output: 2
// Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
// Example 2:

// Input: nums = [2,3,0,1,4]
// Output: 2
 

// Constraints:

// 1 <= nums.length <= 10^4
// 0 <= nums[i] <= 1000
// It's guaranteed that you can reach nums[n - 1].

import java.util.*;

class Solution {
    int[] dp;
    public int jump(int[] nums) {
        int n = nums.length;
        dp = new int[n];
        // Arrays.fill(dp, -1);
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[n - 1] = 0;

        for(int i = n - 2; i >= 0; i--){
            int ans = Integer.MAX_VALUE;
            for(int j = 1; j <= nums[i] && i + j < n; j++) {
                int sub;
                if (i + j >= n - 1) {
                    sub = 1;               
                } else if (dp[i + j] != Integer.MAX_VALUE) {
                    sub = 1 + dp[i + j];    
                } else {
                    continue;
                }
                ans = Math.min(ans, sub);
            }
            dp[i] = ans;
        }
        return dp[0];
        // return backtrack(nums, n, 0);
    }

    private int backtrack(int[] nums, int n, int idx){
        if(idx >= n - 1){
            return 0;
        }
        if(dp[idx] != -1) return dp[idx];
        
        int ans = Integer.MAX_VALUE;
        for(int i = 1; i <= nums[idx]; i++){
            int sub = backtrack(nums, n, idx + i);
            if(sub != Integer.MAX_VALUE) {
                ans = Math.min(ans, 1 + sub);
            }
        }
        return dp[idx] = ans;
    }
}
import java.util.*;

class Solution {
    public ArrayList<Integer> getLIS(int arr[]) {
        // Code here
        int n = arr.length;
        int[] dp = new int[n];
        int[] lisIdx = new int[n];
        for(int i = 0; i < n; i++){
            lisIdx[i] = i;
        }
        for(int i = 0; i < n; i++){
            int maxi = 0, idx = -1;
            for(int j = 0; j < i; j++){
                if(arr[j] < arr[i]){
                    if(dp[j] > maxi){
                        maxi = dp[j];
                        idx = j;
                    }
                }
            }
            if(idx != -1){
                lisIdx[i] = idx;
            }
            dp[i] = maxi + 1;
        }
        int maxi = dp[0], maxiIdx = 0;
        for(int i = 1; i < n; i++){
            if(dp[i] > maxi){
                maxi = dp[i];
                maxiIdx = i;
            }
        }
        ArrayList<Integer> ans = new ArrayList<>();
        while(lisIdx[maxiIdx] != maxiIdx){
            ans.add(arr[maxiIdx]);
            maxiIdx = lisIdx[maxiIdx];
        }
        ans.add(arr[maxiIdx]);
        Collections.reverse(ans);
        return ans;
    }
}

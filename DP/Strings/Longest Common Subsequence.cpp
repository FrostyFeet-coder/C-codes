// Longest Common Subsequence (LCS) Problem
// Yahan teen tarike diye gaye hain LCS nikalne ke:
// 1. Recursion + Memoization (Top-Down DP)
// 2. Tabulation (Bottom-Up DP)
// 3. Space Optimized DP

// 1. Recursion + Memoization Approach
// TC: O(n*m), SC: O(n*m) (DP table) + O(n+m) (recursion stack)
class Solution {
public:
    // solve function LCS nikalta hai text1[0..idx1] aur text2[0..idx2] ke liye
    int solve(string &text1, int idx1, string &text2, int idx2, vector<vector<int>>& dp) {
        // Base case: agar koi bhi string ka index -1 ho gaya toh LCS 0 hoga
        if(idx1 < 0 || idx2 < 0) return 0;

        // Agar pehle se answer calculate hai toh wahi return kar do (memoization)
        if(dp[idx1][idx2] != -1) return dp[idx1][idx2];

        // Agar dono string ke current character match karte hain
        if(text1[idx1] == text2[idx2]){
            // 1 add karo aur dono index ek-ek kam karke solve call karo
            return dp[idx1][idx2] = 1 + solve(text1, idx1 - 1, text2, idx2 - 1, dp); 
        }

        // Agar match nahi karte toh dono me se kisi ek ka index kam karke max le lo
        return dp[idx1][idx2] = max(
            solve(text1, idx1 - 1, text2, idx2, dp),
            solve(text1, idx1, text2, idx2 - 1, dp)
        );
    }

    // Main function jo user call karega
    int longestCommonSubsequence(string text1, string text2) {
        // DP table banate hain, -1 se initialize karte hain
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), -1));
        // Last index se solve start karte hain
        return solve(text1, text1.size() - 1, text2, text2.size() - 1, dp);
    }
};

// 2. Tabulation (Bottom-Up DP) Approach
// TC: O(n*m), SC: O(n*m)
int longestCommonSubsequence(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    // DP table banate hain, 0 se initialize karte hain
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // i = 1 se n tak aur j = 1 se m tak iterate karte hain
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            // Agar current character match kare toh 1 + diagonal value
            if(text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];  // match
            } else {
                // Agar match nahi kare toh upar ya left ka max le lo
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);  // mismatch
            }
        }
    }

    // Final answer last cell me hoga
    return dp[n][m];
}

// 3. Space Optimized DP Approach
// TC: O(n*m), SC: O(m)
int longestCommonSubsequence(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    // Sirf do 1D arrays use karte hain: prev aur curr
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    // Pehli row ko 0 se initialize karte hain
    for(int j = 0; j <= m; j++) {
        prev[j] = 0;
    }

    // i = 1 se n tak iterate karte hain
    for(int i = 1; i <= n; i++) {
        // j = 1 se m tak iterate karte hain
        for(int j = 1; j <= m; j++) {
            // Agar character match kare toh 1 + prev row ka diagonal value
            if(text1[i - 1] == text2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                // Agar match nahi kare toh prev row ya curr row ka left ka max le lo
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        // Curr ko prev bana do next iteration ke liye
        prev = curr;
    }

    // Final answer prev[m] me hoga
    return prev[m];
}

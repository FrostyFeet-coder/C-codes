    // Distinct Subsequences - Topper Notes
    // Problem: Count number of distinct subsequences of s which equals t
    // TC (Time Complexity): O(n*m)
    // SC (Space Complexity): O(m) - Optimized DP

    #include <bits/stdc++.h>
    using namespace std;

    class Solution {
    public:
        int numDistinct(string s, string t) {
            int n = s.size(), m = t.size();

            // prev aur curr arrays banaye, size m+1, sabko 0 se initialize kiya
            vector<unsigned long long> prev(m + 1, 0), curr(m + 1, 0);

            // Base case: jab t empty ho, ek hi subsequence possible hai (empty string)
            prev[0] = 1;

            // s ke har character ke liye loop chalao
            for (int i = 1; i <= n; i++) {
                curr[0] = 1; // t empty ho toh answer 1 hi rahega

                // t ke har character ke liye loop chalao
                for (int j = 1; j <= m; j++) {
                    // Agar s ka current character t ke current character ke barabar hai
                    if (s[i - 1] == t[j - 1]) {
                        // Dono ko include karne ka tarika + skip karne ka tarika
                        curr[j] = prev[j - 1] + prev[j];
                    } else {
                        // Agar match nahi hua toh sirf skip karne ka tarika
                        curr[j] = prev[j];
                    }
                }
                // prev ko curr bana do, next iteration ke liye
                prev = curr;
            }
            // Final answer prev[m] me hoga
            return prev[m];
        }
    };

    
        // DP Table Approach (Tabulation)
        // TC: O(n*m), SC: O(n*m)
        int numDistinct(string s, string t) {
            int n = s.size(), m = t.size();

            // DP table banaya, sabko 0 se initialize kiya
            vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));

            // Base case: jab t empty ho, har s ke liye answer 1 hai
            for (int i = 0; i <= n; i++) {
                dp[i][0] = 1;
            }

            // DP table fill karna start kiya
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    // Agar s ka character t ke character ke barabar hai
                    if (s[i - 1] == t[j - 1]) {
                        // Dono ko include + skip karne ka tarika
                        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                    } else {
                        // Sirf skip karne ka tarika
                        dp[i][j] = dp[i - 1][j];
                    }
                }
            }
            // Answer dp[n][m] me hoga
            return (int)dp[n][m];
        }
    

    
        // Recursive + Memoization Approach
        // TC: O(n*m), SC: O(n*m) + O(n+m) stack
        int solve(string s, int i, string t, int j, vector<vector<int>>& dp) {
            // Agar t khatam ho gaya toh ek subsequence mil gaya
            if (j < 0) return 1;

            // Agar s khatam ho gaya aur t abhi bhi bacha hai toh answer 0
            if (i < 0) return 0;

            // DP check karo, agar already calculated hai toh wahi return karo
            if (dp[i][j] != -1) return dp[i][j];

            // Agar s[i] == t[j], toh include bhi kar sakte aur skip bhi
            if (s[i] == t[j]) {
                return dp[i][j] = solve(s, i - 1, t, j - 1, dp) + solve(s, i - 1, t, j, dp);
            } else {
                // Agar match nahi hua toh sirf skip karo
                return dp[i][j] = solve(s, i - 1, t, j, dp);
            }
        }

        int numDistinct(string s, string t) {
            int n = s.size(), m = t.size();
            vector<vector<int>> dp(n, vector<int>(m, -1));
            return solve(s, n - 1, t, m - 1, dp);
        }
    


    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();

        // prev array banaya, size m+1, sabko 0 se initialize kiya
        vector<unsigned long long> prev(m + 1, 0);

        // Base case: jab t empty ho, ek hi subsequence possible hai (empty string)
        prev[0] = 1;

        // s ke har character ke liye loop chalao
        for (int i = 1; i <= n; i++) {
            // t ke har character ke liye ulte order me loop chalao
            for (int j = m; j >= 1; j--) {
                // Agar s ka current character t ke current character ke barabar hai
                if (s[i - 1] == t[j - 1]) {
                    // Dono ko include karne ka tarika + skip karne ka tarika
                    prev[j] = prev[j - 1] + prev[j];
                }
                // Agar match nahi hua toh kuch nahi karna, prev[j] same rahega
            }
        }
        // Final answer prev[m] me hoga
        return prev[m];
    }

// ✅ Wildcard Matching Problem (Leetcode 44)
// Characters:
//   '?' → ek character ko match karega
//   '*' → zero ya zyada characters ko match karega

// ---------------------------
// 1. Memoization (Top-Down DP)
// ---------------------------
class SolutionMemo {
public:
    bool f(int i, int j, string &s, string &p, vector<vector<int>>&dp) {
        // ✅ Base cases
        if (i < 0 && j < 0) return true;   // dono string aur pattern finish ho gaye
        if (j < 0 && i >= 0) return false; // pattern khatam but string bachi hai
        if (i < 0 && j >= 0) {             // string khatam but pattern bacha hai
            for (int k = 0; k <= j; k++) {
                if (p[k] != '*') return false; // agar koi '*' ke alawa char mila → false
            }
            return true; // pura pattern '*' hai to true
        }

        if (dp[i][j] != -1) return dp[i][j]; // memoized result use karo

        // ✅ Character match ya '?'
        if (p[j] == s[i] || p[j] == '?') {
            return dp[i][j] = f(i - 1, j - 1, s, p, dp);
        }

        // ✅ Agar '*' hai to 2 possibilities:
        // 1. '*' zero char match kare → f(i, j-1)
        // 2. '*' ek char khaye → f(i-1, j)
        if (p[j] == '*') {
            return dp[i][j] = f(i - 1, j, s, p, dp) || f(i, j - 1, s, p, dp);
        }

        return dp[i][j] = false; // otherwise mismatch
    }

    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return f(n - 1, m - 1, s, p, dp);
    }
};

// ---------------------------
// 2. Tabulation (Bottom-Up DP)
// ---------------------------
class SolutionTab {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        // ✅ Base case: empty string, empty pattern
        dp[0][0] = true;

        // ✅ Agar string empty hai, pattern me sirf '*' hone chahiye
        for (int j = 1; j <= m; j++) {
            bool allStar = true;
            for (int k = 1; k <= j; k++) {
                if (p[k - 1] != '*') {
                    allStar = false;
                    break;
                }
            }
            dp[0][j] = allStar;
        }

        // ✅ Fill the DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1]; // match ho gaya
                }
                else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1]; 
                    // case1: '*' zero char lega (dp[i][j-1])
                    // case2: '*' ek char khayega (dp[i-1][j])
                }
                else {
                    dp[i][j] = false; // mismatch
                }
            }
        }

        return dp[n][m];
    }
};

// ---------------------------
// 3. Space Optimized DP
// ---------------------------
class SolutionOptimized {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<bool> prev(m + 1, false), curr(m + 1, false);

        // ✅ Base case
        prev[0] = true;

        // ✅ Empty string case (sirf '*' allowed)
        for (int j = 1; j <= m; j++) {
            bool allStar = true;
            for (int k = 1; k <= j; k++) {
                if (p[k - 1] != '*') {
                    allStar = false;
                    break;
                }
            }
            prev[j] = allStar;
        }

        // ✅ DP table row by row
        for (int i = 1; i <= n; i++) {
            curr[0] = false; // pattern empty but string bachi → false
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                    curr[j] = prev[j - 1];
                }
                else if (p[j - 1] == '*') {
                    curr[j] = prev[j] || curr[j - 1];
                }
                else {
                    curr[j] = false;
                }
            }
            prev = curr; // move to next row
        }

        return prev[m];
    }
};

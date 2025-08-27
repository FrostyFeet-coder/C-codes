// Longest Palindromic Subsequence (LPS) - Topper Notes
// Approaches: 
// 1. DP (Tabulation) using LCS
// 2. DP (Space Optimized) using LCS
// 3. DP (Memoization)
// 4. Simple Recursion (for understanding, not for use in interviews)
// TC/SC mentioned for each

#include <bits/stdc++.h>
using namespace std;

// 1. DP (Tabulation) using LCS
// TC: O(n^2), SC: O(n^2)
// Yahan pe hum string ka reverse leke, LCS nikalte hain dono ka
class Solution_Tabulation {
public:
    int longestPalindromeSubseq(string s) {
        string rev = s; // Original string ko copy kar liya
        reverse(rev.begin(), rev.end()); // String ko reverse kar diya
        int n = s.size(); // String ki length nikal li
        // DP table banaya, size (n+1)x(n+1), sabko 0 se initialize kiya
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // DP table fill kar rahe hain
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                // Agar dono string ke current char same hain
                if(s[i-1] == rev[j-1]){
                    // Palindrome ka part hai, to 1 add kar do previous diagonal value me
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    // Nahi match kiya, to max le lo left ya upar wali value ka
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        // Last cell me answer hoga, pura LCS ka length
        return dp[n][n];
    }
};

// 2. DP (Space Optimized) using LCS
// TC: O(n^2), SC: O(n)
// Yahan pe hum sirf 2 rows use karte hain, space bachane ke liye
class Solution_SpaceOptimized {
public:
    int longestPalindromeSubseq(string s) {
        string rev = s; // String ko copy kiya
        reverse(rev.begin(), rev.end()); // Reverse kar diya
        int n = s.size(); // Length nikal li
        // Sirf 2 rows use kar rahe hain: prev aur curr
        vector<int> prev(n+1, 0), curr(n+1, 0);
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                // Agar dono char match karte hain
                if(s[i-1] == rev[j-1]){
                    // Diagonal se 1 add kar do
                    curr[j] = 1 + prev[j-1];
                } else {
                    // Max le lo left ya upar se
                    curr[j] = max(prev[j], curr[j-1]);
                }
            }
            // Curr row ko prev bana do, next iteration ke liye
            prev = curr;
        }
        // Last row ka last element answer hai
        return prev[n];
    }
};

// 3. DP (Memoization)
// TC: O(n^2), SC: O(n^2) + O(n) (stack space)
// Yahan pe hum recursion + dp use karte hain, overlapping subproblems ko store karte hain
class Solution_Memoization {
public:
    // Helper function, i aur j denote karte hain substring ke start aur end ko
    int solve(int i, int j, string &s, vector<vector<int>> &dp){
        if(i > j) return 0; // Agar i bada ho gaya j se, to empty substring, answer 0
        if(i == j) return 1; // Single character hai, to palindrome length 1
        if(dp[i][j] != -1) return dp[i][j]; // Agar already calculated hai, to wahi return kar do
        if(s[i] == s[j]){
            // Agar dono end ke char same hain, to 2 add kar do beech wale ka answer
            dp[i][j] = 2 + solve(i+1, j-1, s, dp);
        } else {
            // Nahi match kiya, to dono possibilities check karo, max le lo
            dp[i][j] = max(solve(i+1, j, s, dp), solve(i, j-1, s, dp));
        }
        return dp[i][j]; // Answer return kar do
    }
    int longestPalindromeSubseq(string s) {
        int n = s.size(); // Length nikal li
        // DP table banaya, sabko -1 se initialize kiya (matlab abhi calculate nahi hua)
        vector<vector<int>> dp(n, vector<int>(n, -1));
        // 0 se n-1 tak ke liye solve call kiya
        return solve(0, n-1, s, dp);
    }
};

// 4. Simple Recursion (for understanding only, not for interviews)
// TC: O(2^n), SC: O(n) (stack space)
// Yahan pe hum sirf recursion use karte hain, koi dp nahi
class Solution_Recursion {
public:
    // Helper function, i aur j denote karte hain substring ke start aur end ko
    int solve(int i, int j, string &s){
        if(i > j) return 0; // Agar i bada ho gaya j se, to empty substring, answer 0
        if(i == j) return 1; // Single character hai, to palindrome length 1
        if(s[i] == s[j]){
            // Agar dono end ke char same hain, to 2 add kar do beech wale ka answer
            return 2 + solve(i+1, j-1, s);
        } else {
            // Nahi match kiya, to dono possibilities check karo, max le lo
            return max(solve(i+1, j, s), solve(i, j-1, s));
        }
    }
    int longestPalindromeSubseq(string s) {
        int n = s.size(); // Length nikal li
        // 0 se n-1 tak ke liye solve call kiya
        return solve(0, n-1, s);
    }
};

/*
Summary:
- Tabulation (LCS): O(n^2) TC, O(n^2) SC
- Space Optimized: O(n^2) TC, O(n) SC
- Memoization: O(n^2) TC, O(n^2) SC
- Recursion: O(2^n) TC, O(n) SC (not for interviews)
*/

// Interview ke liye Space Optimized ya Memoization best hai!
// Hinglish comments har approach ke andar diye gaye hain, har step pe detail me samjhaya hai.
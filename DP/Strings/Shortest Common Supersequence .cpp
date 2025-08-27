class Solution {
public:
    // Function jo shortest common supersequence return karega
    string shortestCommonSupersequence(string s, string t) {
        int n = s.size(); // s string ki length nikal li
        int m = t.size(); // t string ki length nikal li

        // 2D DP array banaya, jisme dp[i][j] longest common subsequence ka length store karega
        vector<vector<int>> dp(n + 1 , vector<int>(m + 1 , 0));

        // DP table fill kar rahe hain
        for(int i = 1 ; i <= n ; i++){
            for(int j = 1 ; j <= m ; j++){
                // Agar dono string ka current character same hai
                if(s[i - 1] == t[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1]; // LCS length 1 se badha do
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // Nahi toh max le lo previous subproblems ka
            }
        }

        int i = n, j = m; // Last cell se start karenge
        string ans = ""; // Answer string banane ke liye empty string

        // DP table ko reverse traverse karte hue supersequence banayenge
        while(i > 0 && j > 0){
            // Agar dono string ka character same hai toh usko answer me daal do
            if(s[i - 1] == t[j - 1]){
                ans += s[i - 1];  
                i--; j--; // Dono pointer ek step peeche le jao
            } 
            // Agar upar wala cell bada hai toh s ka character daal do
            else if(dp[i - 1][j] > dp[i][j - 1]){
                ans += s[i - 1];  
                i--; // s ka pointer peeche le jao
            } 
            // Nahi toh t ka character daal do
            else {
                ans += t[j - 1];  
                j--; // t ka pointer peeche le jao
            }
        }

        // Agar s me abhi bhi characters bache hain toh unko add kar lo
        while(i > 0) ans += s[i-- - 1];
        // Agar t me abhi bhi characters bache hain toh unko add kar lo
        while(j > 0) ans += t[j-- - 1];

        // Kyunki humne answer reverse banaya hai, toh usko sahi order me kar lo
        reverse(ans.begin(), ans.end());

        return ans; // Final answer return karo
    }
};
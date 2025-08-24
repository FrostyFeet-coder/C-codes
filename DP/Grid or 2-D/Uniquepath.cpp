// Unique Paths problem ke 3 alag-alag approaches ek hi code me explain kiye hain.
// Har approach ke upar detailed comments (Hinglish me) diye hain.

class Solution {
public:

    // 1. Recursive + Memoization Approach (Top-Down DP)
    // Isme hum har cell (m, n) se kitne unique paths hai, wo calculate karte hain.
    // Agar hum 0,0 pahunch gaye to ek path mil gaya, to 1 return karte hain.
    // Agar index out of bounds ho gaya to 0 return karte hain.
    // DP array se already calculated value le lete hain (memoization).
    int solve(int m , int n , vector<vector<int>>&dp){
        // Base case: agar hum starting cell (0,0) pe aa gaye to ek path mil gaya
        if(m == 0 && n == 0) return 1;

        // Agar index negative ho gaya to invalid path hai
        if(m < 0 || n < 0) return 0;

        // Agar already calculate kar chuke hain to wahi value return karo
        if(dp[m][n] != -1) return dp[m][n];

        // Upar se (m-1, n) aur left se (m, n-1) se aane wale paths ka sum
        return dp[m][n] = solve(m - 1 , n , dp) + solve(m , n - 1 , dp);
    }

    int uniquePaths(int m, int n) {
        // 2D DP array banate hain, sabko -1 se initialize karte hain
        vector<vector<int>>dp(m , vector<int>(n , -1));

        // Approach 1: Recursive + Memoization (Top-Down)
        // return solve(m - 1 , n - 1 , dp);  

        // Approach 2: Tabulation (Bottom-Up DP)
        // Isme hum 0,0 se start karke har cell tak kitne unique paths hai, wo calculate karte hain
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n; j++){
                if(i == 0 && j == 0) 
                    dp[i][j] = 1; // Starting cell pe ek hi path hai
                else{ 
                    int top = 0 , left = 0;
                    if(i > 0)  top = dp[i - 1][j]; // Upar se aane wale paths
                    if(j > 0)  left = dp[i][j - 1]; // Left se aane wale paths

                    dp[i][j] = top + left; // Total paths
                }
            }
        }
        // Tabulation ka answer last cell me hoga
        // return dp[m-1][n-1];

        // Approach 3: Space Optimized Tabulation
        // Isme hum sirf 1D array use karte hain, kyunki har row sirf previous row pe depend karti hai
        vector<int>dp1(n , 0); // Current row ke liye
        for (int i = 0; i < m; i++) {
            vector<int> temp(n, 0); // Nayi row banate hain
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) 
                    temp[j] = 1; // Starting cell
                else {
                    int top = 0, left = 0;
                    if (i > 0) top = dp1[j]; // Upar se aane wale paths (previous row)
                    if (j > 0) left = temp[j-1]; // Left se aane wale paths (current row)
                    temp[j] = top + left;
                }
            }
            dp1 = temp; // Current row ko previous row bana do
        }

        // Space optimized ka answer last cell me hoga
        return dp1[n-1];
    }
};

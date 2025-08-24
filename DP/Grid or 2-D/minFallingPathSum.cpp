// Minimum Falling Path Sum problem ka solution
// Is code mein top-down (recursion + memoization) aur bottom-up (tabulation) dono approach hai
// Detailed notes jaise topper ki copy mein likhte hain, waise explanation ke saath

/*
Problem Statement:
Given an n x n integer matrix, find the minimum sum of any falling path through matrix.
A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right.

Approach 1: Top-Down DP (Recursion + Memoization)
-------------------------------------------------
- Har cell se neeche, left-diagonal, ya right-diagonal ja sakte hain.
- Har cell par minimum path sum calculate karte hain, aur memoization se overlapping subproblems avoid karte hain.
- Base case: Agar last row par hain, toh wahi value return karo.
- Memoization: Agar dp[row][col] already calculated hai, toh wahi return karo.
- Recursive calls: down, left-diagonal, right-diagonal.
- Final answer: First row ke har column se start karke minimum path sum nikal lo.

Time Complexity (TC): O(n^2)
    - Har cell par ek hi baar calculation hota hai (n rows * n columns).
    - Har cell se max 3 recursive calls, but memoization se har cell ek hi baar solve hota hai.
Space Complexity (SC): O(n^2) + O(n)
    - O(n^2) for dp table.
    - O(n) recursion stack (max depth n).

Approach 2: Bottom-Up DP (Tabulation)
-------------------------------------
- DP table ko bottom se top fill karte hain.
- Last row ko matrix ki values se initialize karte hain.
- Har cell par neeche, left-diagonal, right-diagonal se minimum path sum nikalte hain.
- Final answer: First row ke minimum value.

Time Complexity (TC): O(n^2)
    - Har cell par constant time calculation.
Space Complexity (SC): O(n^2)
    - DP table ke liye.

*/

// ----------- Top-Down (Recursion + Memoization) + Bottom-Up (Tabulation) Approach -----------

class Solution {
public:
    // Recursive function with memoization
    // row, col: current cell ka index
    // matrix: input 2D matrix
    // dp: memoization ke liye 2D vector
    int solve(int row, int col, vector<vector<int>>& matrix , vector<vector<int>>&dp) {
        int n = matrix.size();      // rows ka size
        int m = matrix[0].size();   // columns ka size

        // Base case: Agar last row par aa gaye, toh wahi value return karo
        if (row == n - 1) return dp[row][col] = matrix[row][col];

        // Memoization: Agar already calculate kar chuke hain, toh wahi value return karo
        if(dp[row][col] != -1) return dp[row][col];

        // Niche jaane ka option
        int down = matrix[row][col] + solve(row + 1, col, matrix, dp);

        // Diagonal left aur right ke liye INT_MAX se initialize karo
        int leftdig = INT_MAX, rightdig = INT_MAX;

        // Agar left diagonal possible hai toh usko calculate karo
        if (col - 1 >= 0)
            leftdig = matrix[row][col] + solve(row + 1, col - 1, matrix ,dp);

        // Agar right diagonal possible hai toh usko calculate karo
        if (col + 1 < m)
            rightdig = matrix[row][col] + solve(row + 1, col + 1, matrix ,dp);

        // Teenon options mein se minimum value ko store aur return karo
        return dp[row][col] =  min(down, min(leftdig, rightdig));
    }

    // Tabulation (bottom-up DP) approach
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();      // rows ka size
        int m = matrix[0].size();   // columns ka size

        // DP table banate hain, sabko 0 se initialize karte hain
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Last row ko matrix ki values se fill kar do
        for(int j = 0; j < m; j++) {
            dp[n-1][j] = matrix[n-1][j];
        }

        // Baaki rows ko bottom se top ki taraf fill karo
        for(int i = n-2; i >= 0; i--) {
            for(int j = 0; j < m; j++) {
                // Niche jaane ka option
                int down = dp[i+1][j];

                // Left diagonal ka option, agar possible ho toh
                int leftDiag = (j > 0) ? dp[i+1][j-1] : INT_MAX;

                // Right diagonal ka option, agar possible ho toh
                int rightDiag = (j < m-1) ? dp[i+1][j+1] : INT_MAX;

                // Teenon options mein se minimum value le lo
                dp[i][j] = matrix[i][j] + min({down, leftDiag, rightDiag});
            }
        }

        // First row mein se minimum value answer hoga
        int ans = INT_MAX;
        for(int j = 0; j < m; j++) {
            ans = min(ans, dp[0][j]);
        }

        return ans;
    }
};

/*
Summary Table:
-------------------------------------------------
| Approach         | Time Complexity | Space Complexity |
|------------------|----------------|------------------|
| Top-Down (Memo)  |   O(n^2)       |   O(n^2) + O(n)  |
| Bottom-Up (Tab)  |   O(n^2)       |   O(n^2)         |
-------------------------------------------------
n = number of rows/columns in matrix

Tip: Interview mein tabulation approach likhna best hai, kyunki recursion stack ka overhead nahi hota.
*/

// ----------- Sirf Tabulation Approach (Recommended for Interviews) -----------

class Solution {
public:
    // Bottom-Up DP (Tabulation)
    // TC: O(n^2), SC: O(n^2)
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();      // rows ka size
        int m = matrix[0].size();   // columns ka size

        // DP table banate hain, sabko 0 se initialize karte hain
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Last row ko matrix ki values se fill kar do
        for(int j = 0; j < m; j++) {
            dp[n-1][j] = matrix[n-1][j];
        }

        // Baaki rows ko bottom se top ki taraf fill karo
        for(int i = n-2; i >= 0; i--) {
            for(int j = 0; j < m; j++) {
                // Niche jaane ka option
                int down = dp[i+1][j];

                // Left diagonal ka option, agar possible ho toh
                int leftDiag = (j > 0) ? dp[i+1][j-1] : INT_MAX;

                // Right diagonal ka option, agar possible ho toh
                int rightDiag = (j < m-1) ? dp[i+1][j+1] : INT_MAX;

                // Teenon options mein se minimum value le lo
                dp[i][j] = matrix[i][j] + min({down, leftDiag, rightDiag});
            }
        }

        // First row mein se minimum value answer hoga
        int ans = INT_MAX;
        for(int j = 0; j < m; j++) {
            ans = min(ans, dp[0][j]);
        }

        return ans;
    }
};
// Coin Change 2 Problem - Topper Notes Style (Hinglish Explanation)
// Problem: Kitne tareeke hain ek given amount ko coins ke combination se banane ke? (Unlimited supply of coins)

// Approach 1: Recursion + Memoization (Top-Down DP)
class Solution {
public:
    int dp[5001][301]; // DP array: dp[amount][index] - amount banane ke tareeke using coins[0..index]

    // Recursive function
    int solve(int amount, vector<int>& coins , int index){
        // Base Case: Agar amount 0 ho gaya, ek tareeka mil gaya
        if(amount == 0) return 1;

        // Base Case: Coins khatam ho gaye, amount abhi bhi bacha hai
        if(index < 0) return 0;

        // DP check: Pehle se calculate kiya hua hai toh wahi return karo
        if(dp[amount][index] != -1) return dp[amount][index];

        int take = 0;
        // Agar current coin le sakte hain toh le lo (same coin firse le sakte hain)
        if(coins[index] <= amount){
            take = solve(amount-coins[index], coins, index);
        }

        // Ya toh current coin na lo, agle coin pe jao
        int nottake = solve(amount, coins, index - 1);

        // Total ways = take + nottake
        return dp[amount][index] = take + nottake;
    }

    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        memset(dp, -1, sizeof(dp)); // DP ko -1 se initialize karo
        return solve(amount, coins, n - 1); // Last coin se start karo
    }
};


// Approach 2: Tabulation (Bottom-Up DP) - 2D DP Array
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        // DP array: dp[i][j] = coins[0..i] se amount j banane ke tareeke
        vector<vector<unsigned long long>> dp(n, vector<unsigned long long>(amount + 1, 0));

        // Base Case: Amount 0 banane ka ek hi tareeka hai (kuch bhi na lo)
        for(int i = 0; i < n; i++){
            dp[i][0] = 1;
        }

        // First coin se jitne multiples hain, unke liye 1 tareeka hai
        for(int j = 0; j <= amount; j++){
            if(j % coins[0] == 0){
                dp[0][j] = 1;
            }
        }

        // DP fill karna start karo
        for(int i = 1; i < n; i++){
            for(int j = 1; j <= amount; j++){
                unsigned long long take = 0;
                // Agar coin le sakte hain toh le lo
                if(coins[i] <= j){
                    take = dp[i][j - coins[i]];
                }
                // Ya toh coin na lo
                unsigned long long nottake = dp[i - 1][j];
                dp[i][j] = take + nottake;
            }
        }
        return dp[n-1][amount];
    }
};


// Approach 3: Space Optimized 2D DP (Sirf 2 rows ka use)
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        // Sirf 2 arrays: prev (pichla row), curr (current row)
        vector<int> prev(amount + 1, 0), curr(amount + 1, 0);

        prev[0] = 1; // Amount 0 banane ka ek tareeka

        // First coin ke multiples
        for(int j = 0; j <= amount; j++){
            if(j % coins[0] == 0){
                prev[j] = 1;
            }
        }

        // Baaki coins ke liye
        for(int i = 1; i < n; i++){
            curr[0] = 1; // Amount 0 ka case
            for(int j = 1; j <= amount; j++){
                unsigned long long take = 0;
                if(coins[i] <= j){
                    take = curr[j - coins[i]];
                }
                unsigned long long nottake = prev[j];
                curr[j] = take + nottake;
            }
            prev = curr; // Current row ko prev bana do
        }
        return prev[amount];
    }
};


// Approach 4: Space Optimized 1D DP (Ek hi array se kaam)
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // dp[a] = amount 'a' banane ke tareeke
        vector<unsigned long long> dp(amount + 1, 0); 
        dp[0] = 1; // Amount 0 banane ka ek tareeka

        // Har coin ke liye, dp update karo
        for (int c : coins) {
            for (int a = c; a <= amount; a++) {
                dp[a] += dp[a - c];
            }
        }
        return dp[amount];        
    }
};

/*
Summary:
1. Recursion + Memoization: Top-down, easy to understand, but stack overflow ho sakta hai.
2. Tabulation (2D): Bottom-up, sab states calculate, O(n*amount) space.
3. Space Optimized (2D): Sirf 2 rows, space bachao.
4. Space Optimized (1D): Sabse efficient, ek hi array, O(amount) space.
*/

class Solution {
public:

    // ================================================
    // Approach 0: Recursion + Memoization (Top-Down DP)
    // ================================================
    // Time Complexity: O(n*2)
    // Space Complexity: O(n*2 + recursion stack)
    int solve(vector<int>& prices, int fee, int index, int canBuy, vector<vector<int>>& dp) {
        if (index == prices.size()) return 0; // Base case: no days left

        if (dp[index][canBuy] != -1) return dp[index][canBuy];

        int profit = 0;

        if (canBuy) {
            // Option 1: Buy today -> pay prices[index], next day can sell
            int buyProfit = -prices[index] + solve(prices, fee, index + 1, 0, dp);
            // Option 2: Skip today -> still can buy tomorrow
            int skipProfit = solve(prices, fee, index + 1, 1, dp);

            profit = max(buyProfit, skipProfit);
        } else {
            // Option 1: Sell today -> gain prices[index] - fee, next day can buy
            int sellProfit = prices[index] - fee + solve(prices, fee, index + 1, 1, dp);
            // Option 2: Skip today -> still can sell tomorrow
            int skipProfit = solve(prices, fee, index + 1, 0, dp);

            profit = max(sellProfit, skipProfit);
        }

        return dp[index][canBuy] = profit;
    }

    int maxProfit_Recursion(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solve(prices, fee, 0, 1, dp); // start from day 0, canBuy = 1
    }

    // ================================================
    // Approach 1: Tabulation / Bottom-Up DP
    // ================================================
    // Time Complexity: O(n*2)
    // Space Complexity: O(n*2)
    int maxProfit_Tabulation(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0)); // dp[n][*] = 0 base case

        for (int index = n - 1; index >= 0; index--) {
            for (int canBuy = 0; canBuy <= 1; canBuy++) {
                int profit = 0;
                if (canBuy) {
                    profit = max(-prices[index] + dp[index + 1][0], dp[index + 1][1]);
                } else {
                    profit = max(prices[index] - fee + dp[index + 1][1], dp[index + 1][0]);
                }
                dp[index][canBuy] = profit;
            }
        }

        return dp[0][1];
    }

    // ================================================
    // Approach 2: Space Optimized DP (O(1) Space)
    // ================================================
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    int maxProfit_SpaceOptimized(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<int> ahead(2, 0); // dp[i+1]
        vector<int> curr(2, 0);  // dp[i]

        for (int index = n - 1; index >= 0; index--) {
            curr[1] = max(-prices[index] + ahead[0], ahead[1]);       // can buy
            curr[0] = max(prices[index] - fee + ahead[1], ahead[0]);  // can sell
            ahead = curr; // shift for next iteration
        }

        return ahead[1]; // max profit starting from day 0 with buy option
    }

    // ================================================
    // Approach 3: Greedy / Single Pass
    // ================================================
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    // Logic: Track max "buy" and max "sell" as we iterate
    int maxProfit(vector<int>& prices, int fee) {
        int buy = INT_MIN; // max profit if we have bought a stock
        int sell = 0;      // max profit if we have sold a stock

        for (int price : prices) {
            // Either keep previous buy or buy today using previous sell profit
            buy = max(buy, sell - price);

            // Either keep previous sell or sell today using previous buy profit - fee
            sell = max(sell, buy + price - fee);
        }

        return sell; // final profit is when we have sold
    }
};
// ================================================
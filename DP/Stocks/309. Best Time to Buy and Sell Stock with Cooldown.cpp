class Solution {
public:

    // ================================================
    // Approach 0: Recursion (Top-down, no memo)
    // ================================================
    // Time Complexity: Exponential, O(2^n)
    // Space Complexity: O(n) recursion stack
    // Logic: Try all possibilities, buy/sell/skip
    int solveRec(vector<int>& prices, int index, int canBuy) {
        if (index >= prices.size()) return 0; // Base case: no days left

        int profit = 0;

        if (canBuy) {
            // Option 1: Buy today -> pay prices[index] and next day can sell
            int buyProfit = -prices[index] + solveRec(prices, index + 1, 0);
            // Option 2: Skip today -> still can buy tomorrow
            int skipProfit = solveRec(prices, index + 1, 1);

            profit = max(buyProfit, skipProfit);
        } else {
            // Option 1: Sell today -> gain prices[index] and cooldown next day
            int sellProfit = prices[index] + solveRec(prices, index + 2, 1);
            // Option 2: Skip today -> still can sell tomorrow
            int skipProfit = solveRec(prices, index + 1, 0);

            profit = max(sellProfit, skipProfit);
        }

        return profit;
    }

    // ================================================
    // Approach 1: Normal Tabulation (2D DP)
    // ================================================
    // Time Complexity: O(n*2) = O(n)
    // Space Complexity: O(n*2)
    int maxProfit_Tabulation(vector<int>& prices) {
        int n = prices.size();

        // dp[i][canBuy] = max profit starting from day i with canBuy status
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));
        // +2 for cooldown handling (index+2 after sell)

        for (int index = n - 1; index >= 0; index--) {
            for (int canBuy = 0; canBuy <= 1; canBuy++) {
                int profit = 0;

                if (canBuy) {
                    int buyProfit = -prices[index] + dp[index + 1][0];
                    int skipProfit = dp[index + 1][1];
                    profit = max(buyProfit, skipProfit);
                } else {
                    int sellProfit = prices[index] + dp[index + 2][1];
                    int skipProfit = dp[index + 1][0];
                    profit = max(sellProfit, skipProfit);
                }

                dp[index][canBuy] = profit;
            }
        }

        return dp[0][1]; // start with buy option on day 0
    }

    // ================================================
    // Approach 2: Space Optimized (O(1) Space)
    // ================================================
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // front1 = dp[i+1], front2 = dp[i+2], curr = dp[i]
        vector<int> front1(2, 0);
        vector<int> front2(2, 0);
        vector<int> curr(2, 0);

        for (int index = n - 1; index >= 0; index--) {
            // If we can buy today
            curr[1] = max(-prices[index] + front1[0], front1[1]);

            // If we can sell today
            curr[0] = max(prices[index] + front2[1], front1[0]);

            // Shift the days for next iteration
            front2 = front1;
            front1 = curr;
        }

        return curr[1]; // Max profit starting from day 0 with buy option
    }
};

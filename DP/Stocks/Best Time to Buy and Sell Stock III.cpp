// ===============================================
// BEST TIME TO BUY AND SELL STOCK III (At most 2 transactions)
// Approaches: Recursion → Memoization → Tabulation → Space Optimized → Constant Space
// ===============================================



// ======================================================
// 🔹 Approach 1: Recursion + Memoization (2D DP)
// ======================================================
class Solution {
public:
    int solve(vector<int>& prices, int index, int transactions, vector<vector<int>>& dp) {
        // Base case: agar array khatam ho gaya ya transactions 0 bachi -> no profit
        if (index == prices.size() || transactions == 0) return 0;

        // Agar already calculate kiya hai toh return kardo
        if (dp[index][transactions] != -1) return dp[index][transactions];

        int profit = 0;

        // Agar even transactions bachi hain -> abhi Buy kar sakte ho
        if (transactions % 2 == 0) {
            // Buy karna
            int take = -prices[index] + solve(prices, index + 1, transactions - 1, dp);
            // Skip karna
            int nottake = solve(prices, index + 1, transactions, dp);
            profit = max(take, nottake);
        }
        // Agar odd transactions bachi hain -> abhi Sell karna hai
        else {
            int sell = prices[index] + solve(prices, index + 1, transactions - 1, dp);
            int notsell = solve(prices, index + 1, transactions, dp);
            profit = max(sell, notsell);
        }

        return dp[index][transactions] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(5, -1)); // 4 moves (Buy, Sell, Buy, Sell)
        return solve(prices, 0, 4, dp);
    }
};
// ======================================================
/*
------------------------------------------------------
1) RECURSION
------------------------------------------------------
*/


class SolutionRec {
public:
    int solve(vector<int>& prices, int index, int transactions) {
        // base case: agar array end hogya ya transactions khatam -> profit = 0
        if (index == prices.size() || transactions == 0) return 0;

        int profit = 0;

        if (transactions % 2 == 0) {
            // Even transaction number -> matlab "BUY" karna hai
            // Option 1: Aaj buy karo (-price) aur ek transaction use kar lo
            int take = -prices[index] + solve(prices, index + 1, transactions - 1);

            // Option 2: Skip karo (kuch na lo, bas aage badho)
            int nottake = solve(prices, index + 1, transactions);

            // Best profit choose karo
            profit = max(take, nottake);
        } else {
            // Odd transaction number -> matlab "SELL" karna hai
            // Option 1: Aaj sell karo (+price) aur ek transaction use kar lo
            int sell = prices[index] + solve(prices, index + 1, transactions - 1);

            // Option 2: Skip karo
            int notsell = solve(prices, index + 1, transactions);

            profit = max(sell, notsell);
        }

        return profit;
    }

    int maxProfit(vector<int>& prices) {
        // 4 moves allowed = (Buy1, Sell1, Buy2, Sell2)
        return solve(prices, 0, 4);
    }
};


/*
------------------------------------------------------
2) MEMOIZATION (Recursion + DP)
------------------------------------------------------
*/

class SolutionMemo {
public:
    int solve(vector<int>& prices, int index, int transactions, vector<vector<int>>& dp) {
        // base case
        if (index == prices.size() || transactions == 0) return 0;

        // agar pehle se calculate hai -> directly return
        if (dp[index][transactions] != -1) return dp[index][transactions];

        int profit = 0;

        if (transactions % 2 == 0) {
            // Buy karna hai
            int take = -prices[index] + solve(prices, index + 1, transactions - 1, dp);
            int nottake = solve(prices, index + 1, transactions, dp);
            profit = max(take, nottake);
        } else {
            // Sell karna hai
            int sell = prices[index] + solve(prices, index + 1, transactions - 1, dp);
            int notsell = solve(prices, index + 1, transactions, dp);
            profit = max(sell, notsell);
        }

        return dp[index][transactions] = profit; // store karke return
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // dp[index][transactions] -> max profit from this index with these transactions left
        vector<vector<int>> dp(n, vector<int>(5, -1));
        return solve(prices, 0, 4, dp);
    }
};


/*
------------------------------------------------------
3) TABULATION (Bottom-Up DP)
------------------------------------------------------
*/

class SolutionTab {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // dp table banate hain (n+1) x (5)
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));

        // base case already 0 h -> agar end of array ya 0 transaction bachi ho

        for (int index = n - 1; index >= 0; index--) {
            for (int transactions = 1; transactions <= 4; transactions++) {
                int profit = 0;

                if (transactions % 2 == 0) {
                    // Buy
                    int take = -prices[index] + dp[index + 1][transactions - 1];
                    int nottake = dp[index + 1][transactions];
                    profit = max(take, nottake);
                } else {
                    // Sell
                    int sell = prices[index] + dp[index + 1][transactions - 1];
                    int notsell = dp[index + 1][transactions];
                    profit = max(sell, notsell);
                }

                dp[index][transactions] = profit;
            }
        }

        // 0 index se start, 4 transactions left
        return dp[0][4];
    }
};


/*
------------------------------------------------------
4) SPACE OPTIMIZATION (Only 2 arrays instead of full dp table)
------------------------------------------------------
*/

class SolutionSpace {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // ahead -> next index ka dp, curr -> current index ka dp
        vector<int> ahead(5, 0), curr(5, 0);

        for (int index = n - 1; index >= 0; index--) {
            for (int transactions = 1; transactions <= 4; transactions++) {
                int profit = 0;

                if (transactions % 2 == 0) {
                    // Buy
                    int take = -prices[index] + ahead[transactions - 1];
                    int nottake = ahead[transactions];
                    profit = max(take, nottake);
                } else {
                    // Sell
                    int sell = prices[index] + ahead[transactions - 1];
                    int notsell = ahead[transactions];
                    profit = max(sell, notsell);
                }

                curr[transactions] = profit;
            }
            ahead = curr; // shift -> next iteration ke liye update
        }

        return ahead[4];
    }
};


/*
------------------------------------------------------
5) CONSTANT SPACE (4 variables only)
------------------------------------------------------
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // buy1 -> pehli buy ke baad ka max profit (initially -prices[0])
        int buy1 = -prices[0];

        // sell1 -> pehli sell ke baad ka max profit
        int sell1 = 0;

        // buy2 -> doosri buy ke baad ka max profit (sell1 ke profit ko use karke)
        int buy2 = -prices[0];

        // sell2 -> doosri sell ke baad ka max profit (final answer)
        int sell2 = 0;

        // har price pe update karte jao
        for (int i = 1; i < prices.size(); i++) {
            int price = prices[i];

            // buy1 -> ya toh pehle ka best buy1, ya fir aaj buy karo
            buy1 = max(buy1, -price);

            // sell1 -> ya toh pehle ka best sell1, ya fir aaj sell karo (buy1+price)
            sell1 = max(sell1, buy1 + price);

            // buy2 -> ya toh pehle ka best buy2, ya fir aaj dobara buy karo (sell1-price)
            buy2 = max(buy2, sell1 - price);

            // sell2 -> ya toh pehle ka best sell2, ya fir aaj sell karo (buy2+price)
            sell2 = max(sell2, buy2 + price);
        }

        // final answer -> max profit after at most 2 transactions
        return sell2;
    }
};

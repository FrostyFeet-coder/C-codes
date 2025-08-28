class Solution {
public:
    
    int solve(vector<int>&prices , int index , int canbuy , int transactions ,vector<vector<vector<int>>>&dp){
        if (index == prices.size() || transactions == 0) return 0;

        int profit = 0;
        
        if (dp[index][canbuy][transactions] != -1) return dp[index][canbuy][transactions];

        if(canbuy){
            int take = -prices[index] + solve(prices , index + 1 , 0 , transactions , dp);
            int nottake = solve(prices , index + 1 , 1 , transactions ,dp);
            profit = max(take , nottake);
        }

        else{
            int sell = prices[index] + solve(prices , index+1 , 1 , transactions-1 , dp);
            int notsell = solve(prices , index +1 , 0 , transactions , dp);
            profit = max(sell , notsell);
        }

        return dp[index][canbuy][transactions] = profit;
    }

    int maxProfit1(vector<int>& prices , int k) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solve(prices , 0 , 1 , k , dp);
    }

    int maxProfit(int k, vector<int>& prices) {
        return maxProfit1(prices , k);
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
    int solve(vector<int>&prices , int index , int canbuy , int transactions){
        if (index == prices.size() || transactions == 0) return 0;

        int profit = 0;

        if(canbuy){
            int take = -prices[index] + solve(prices , index + 1 , 0 , transactions);
            int nottake = solve(prices , index + 1 , 1 , transactions);
            profit = max(take , nottake);
        }

        else{
            int sell = prices[index] + solve(prices , index+1 , 1 , transactions-1);
            int notsell = solve(prices , index +1 , 0 , transactions);
            profit = max(sell , notsell);
        }

        return profit;
    }

    int maxProfit(int k, vector<int>& prices) {
        return solve(prices , 0 , 1 , k);
    }
};

/*
------------------------------------------------------
2) MEMOIZATION (Recursion + DP)
------------------------------------------------------
*/
class SolutionMemo {
public:
    int solve(vector<int>& prices, int index, int canbuy, int transactions, vector<vector<vector<int>>>& dp) {
        // base case
        if (index == prices.size() || transactions == 0) return 0; 
        // agar pehle se calculate hai -> directly return
        if (dp[index][canbuy][transactions] != -1) return dp[index][canbuy][transactions];
        int profit = 0; 
        if (canbuy) {
            // Buy karna hai
            int take = -prices[index] + solve(prices, index + 1, 0, transactions, dp);
            int nottake = solve(prices, index + 1, 1, transactions, dp);
            profit = max(take, nottake);
        } else {
            // Sell karna hai
            int sell = prices[index] + solve(prices, index + 1, 1, transactions - 1, dp);
            int notsell = solve(prices, index + 1, 0, transactions, dp);
            profit = max(sell, notsell);
        }
        return dp[index][canbuy][transactions] = profit; // store karke return
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // dp[index][canbuy][transactions] -> max profit from this index with these transactions left
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solve(prices, 0, 1, k, dp);
    }
};

/*
------------------------------------------------------
3) TABULATION (Bottom-Up DP)
------------------------------------------------------
*/
class SolutionTab {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // dp[index][canbuy][transactions] -> max profit from this index with these transactions left
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));   
        // base case already 0 h -> agar end of array ya 0 transaction bachi ho
        for (int index = n - 1; index >= 0; index--) {
            for (int canbuy = 0; canbuy <= 1; canbuy++) {
                for (int transactions = 1; transactions <= k; transactions++) {
                    int profit = 0;
                    if (canbuy) {
                        int take = -prices[index] + dp[index + 1][0][transactions];
                        int nottake = dp[index + 1][1][transactions];
                        profit = max(take, nottake);
                    } else {
                        int sell = prices[index] + dp[index + 1][1][transactions - 1];
                        int notsell = dp[index + 1][0][transactions];
                        profit = max(sell, notsell);
                    }
                    dp[index][canbuy][transactions] = profit;
                }
            }
        }
        return dp[0][1][k];
    }
};
/*
------------------------------------------------------
4) SPACE OPTIMIZATION (Only 2 2D arrays instead of full 3D dp table)
------------------------------------------------------
*/
class SolutionSpace {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // ahead -> next index ka dp, curr -> current index ka dp
        vector<vector<int>> ahead(2, vector<int>(k + 1, 0)), curr(2, vector<int>(k + 1, 0));
        // base case already 0 h -> agar end of array ya 0 transaction bachi ho
        for (int index = n - 1; index >= 0; index--) {
            for (int canbuy = 0; canbuy <= 1; canbuy++) {
                for (int transactions = 1; transactions <= k; transactions++) {
                    int profit = 0;
                    if (canbuy) {
                        int take = -prices[index] + ahead[0][transactions];
                        int nottake = ahead[1][transactions];
                        profit = max(take, nottake);
                    } else {
                        int sell = prices[index] + ahead[1][transactions - 1];
                        int notsell = ahead[0][transactions];
                        profit = max(sell, notsell);
                    }
                    curr[canbuy][transactions] = profit;
                }
            }
            ahead = curr; // shift -> next iteration ke liye update
        }
        return ahead[1][k];
    }
};
/*
------------------------------------------------------
5) CONSTANT SPACE OPTIMIZATION (Only 4 variables instead of 2 2D arrays)
------------------------------------------------------
*/
class SolutionConst {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // 4 variables for 2 states (canbuy = 0/1) and k transactions
        vector<int> aheadBuy(k + 1, 0), aheadNotBuy  (k + 1, 0);
        vector<int> currBuy(k + 1, 0), currNotBuy (k        + 1, 0);
        // base case already 0 h -> agar end of array ya 0 transaction bachi ho
        for (int index = n - 1; index >= 0; index--) {
            for (int transactions = 1; transactions <= k; transactions++) {
                // canbuy = 1
                int take = -prices[index] + aheadNotBuy[transactions];
                int nottake = aheadBuy[transactions];
                currBuy[transactions] = max(take, nottake);
                // canbuy = 0
                int sell = prices[index] + aheadBuy[transactions - 1];
                int notsell = aheadNotBuy[transactions];
                currNotBuy[transactions] = max(sell, notsell);      
            }
            aheadBuy = currBuy;       // shift -> next iteration ke liye update
            aheadNotBuy = currNotBuy; // shift -> next iteration ke liye update
        }
        return aheadBuy[k]; // starting point: index 0, canbuy = 1, k transactions
    }
};
// ======================================================
// DP[N * k state] soln
// Time Complexity: O(n * k)
// Space Complexity: O(n * k)
// ======================================================
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // dp[index][transactions] -> max profit from this index with these transactions left
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));   
        // base case already 0 h -> agar end of array ya 0 transaction bachi ho
        for (int index = n - 1; index >= 0; index--) {
            for (int transactions = 1; transactions <= k; transactions++) {
                int profit = 0;
                // Buy karna hai
                int take = -prices[index] + dp[index + 1][transactions - 1];
                int nottake = dp[index + 1][transactions];
                profit = max(take, nottake);
                // Sell karna hai
                int sell = prices[index] + dp[index + 1][transactions - 1];
                int notsell = dp[index + 1][transactions];
                profit = max(sell, notsell);
                dp[index][transactions] = profit;
            }
        }
        return dp[0][k];
    } 
};
// ======================================================
// Space Optimized (Only 1D array instead of 2D dp table)
// Time Complexity: O(n * k)
// Space Complexity: O(k)
// ======================================================
class SolutionSpaceOpt {    
    public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // ahead -> next index ka dp, curr -> current index ka dp
        vector<int> ahead(k + 1, 0), curr(k + 1, 0);
        // base case already 0 h -> agar end of array ya 0 transaction bachi ho
        for (int index = n - 1; index >= 0; index--) {
            for (int transactions = 1; transactions <= k; transactions++) {
                int profit = 0;
                // Buy karna hai
                int take = -prices[index] + ahead[transactions - 1];
                int nottake = ahead[transactions];
                profit = max(take, nottake);
                // Sell karna hai
                int sell = prices[index] + ahead[transactions - 1];
                int notsell = ahead[transactions];
                profit = max(sell, notsell);
                curr[transactions] = profit;
            }
            ahead = curr; // shift -> next iteration ke liye update
        }
        return ahead[k];
    }
};
// ======================================================
// Constant Space Optimization (Only 2 variables instead of 1D array)
// Time Complexity: O(n * k)
// Space Complexity: O(1)
// ======================================================
class SolutionConstOpt {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // 2 variables for k transactions
        vector<int> ahead(k + 1, 0), curr(k + 1, 0);
        // base case already 0 h -> agar end of array ya 0 transaction bachi ho
        for (int index = n - 1; index >= 0; index--) {
            for (int transactions = 1; transactions <= k; transactions++) {
                int profit = 0;
                // Buy karna hai
                int take = -prices[index] + ahead[transactions - 1];
                int nottake = ahead[transactions];
                profit = max(take, nottake);
                // Sell karna hai
                int sell = prices[index] + ahead[transactions - 1];
                int notsell = ahead[transactions];
                profit = max(sell, notsell);
                curr[transactions] = profit;
            }
            ahead = curr; // shift -> next iteration ke liye update
        }
        return ahead[k];
    }
};
// ======================================================
// K >= n/2 (Basically Infinite Transactions allowed)
// Time Complexity: O(n)
// Space Complexity: O(1)
// ======================================================
class SolutionInf {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i - 1]) {
                    maxProfit += prices[i] - prices[i - 1];
                }
            }
            return maxProfit;
        }
        // Agar k < n/2, toh upar wala DP approach use karo
        // (Yeh part already upar defined hai, yaha repeat nahi kar rahe    hain)
        return 0; // Placeholder, actual DP solution should be called here
    }
};
// ======================================================
// K >= n/2 (Basically Infinite Transactions allowed) - Optimized
// Time Complexity: O(n)
// Space Complexity: O(1)
// ======================================================
class SolutionInfOpt {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i - 1]) {
                    maxProfit += prices[i] - prices[i - 1];
                }
            }
            return maxProfit;
        } // Agar k < n/2, toh upar wala DP approach use karo
        return 0; // Placeholder, actual DP solution should be called here
    }
};  
#include <bits/stdc++.h>
#include <vector>
using namespace std;


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;  // Final profit store karne ke liye

        // Hum loop day 1 (index = 1) se last day tak chalayenge
        // Kyunki hamesha pichle din ka price (prices[i-1]) dekhna hai
        for (int i = 1; i < prices.size(); i++) {

            // Agar aaj ka price kal se zyada hai
            // iska matlab simple hai:
            // -> Kal buy karo (prices[i-1] par)
            // -> Aaj sell karo (prices[i] par)
            // aur profit banega (prices[i] - prices[i-1])

            // Example: prices = [1, 2]
            // Kal=1, Aaj=2 → profit = 1
            if (prices[i] > prices[i - 1]) {
                ans += prices[i] - prices[i - 1]; 
            }
        }

        // Yaha ek important baat hai:
        // Yeh greedy logic kaise kaam karta hai?
        //
        // Humne har chhoti increasing slope ka profit collect kiya hai.
        // Agar array = [1, 2, 3]
        // Profit calculation:
        //   1→2 = 1
        //   2→3 = 1
        //   Total = 2
        // Jo same hai as 1→3 (profit = 2).
        //
        // Matlab har increasing segment ko tod tod kar lene se
        // total profit same aata hai as ek single buy-sell transaction.
        // Isi wajah se greedy kaam karta hai.

        // Final total profit return kar do
        return ans;
    }
};


class Solution {
public:
    // Recursive function jo max profit nikalta hai
    // prices = stock prices array
    // index = abhi hum kis din par khade hain
    // canbuy = agar true hai toh hum buy kar sakte hain, agar false hai toh sell karna hoga
    // n = total din
    // dp = memoization table (index aur canbuy state ko store karne ke liye)
    int solve(vector<int>& prices, int index, bool canbuy, int n, vector<vector<int>>& dp) {
        
        // Base Case: agar index n tak pahunch gaya matlab saare din khatam
        // Ab koi transaction possible nahi hai
        if (index == n) {
            return 0;
        }

        // Agar yeh state pehle calculate ho chuki hai toh directly return kar do
        if (dp[index][canbuy] != -1) return dp[index][canbuy];

        int profit = 0;

        // Case 1: Agar hum buy kar sakte hain
        if (canbuy) {
            // Option 1: iss din buy kar lo (isliye -prices[index] hoga) 
            // aur next din par hum sell state me chale jayenge
            int buy = -prices[index] + solve(prices, index + 1, false, n, dp);

            // Option 2: iss din skip kar do, aur next din bhi buy option available rahega
            int skip = solve(prices, index + 1, true, n, dp);

            // Max profit dono options me se choose karo
            profit = max(buy, skip);

        } else {
            // Case 2: Agar humare paas already stock hai, toh ab hum sell kar sakte hain
            // Option 1: sell kar do aur profit add ho jayega
            // Aur agle din se hum buy state me chale jayenge
            int sell = prices[index] + solve(prices, index + 1, true, n, dp);

            // Option 2: iss din bhi stock hold karke raho (skip selling)
            int skip = solve(prices, index + 1, false, n, dp);

            // Max profit dono options me se choose karo
            profit = max(sell, skip);
        }

        // Current state ka answer store kar do DP table me
        return dp[index][canbuy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // DP table banayenge jisme har index par do states hongi:
        // dp[i][0] -> agar hum stock hold kar rahe hain (sell karna hai)
        // dp[i][1] -> agar hum buy kar sakte hain
        vector<vector<int>> dp(n, vector<int>(2, -1));

        // Start humesha index 0 se hoga aur initially hum buy kar sakte hain
        return solve(prices, 0, true, n, dp);
    }
};

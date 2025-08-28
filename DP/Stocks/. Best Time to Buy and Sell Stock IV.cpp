// =====================================================================================
// BEST TIME TO BUY & SELL STOCK — Up to K Transactions
// All key approaches in one file, with Hinglish topper-style comments.
//   A0) Brute Force Recursion (holding-state)             -> for learning
//   A1) Top-Down 3D DP (Memoization: index x buy x cap)   -> clean + fast
//   A2) Bottom-Up 3D DP (Tabulation)                      -> iterative
//   A3) O(n*k) 1D DP (hold/release arrays) + k>=n/2 trick -> my go-to for general k
//   A4) 2*k Parity DP (1D ahead/curr)                     -> different view (buy/sell = parity)
//   A5) Constant-Space for k=2 (buy1/sell1/buy2/sell2)    -> elegant when k==2
//   A6) Unlimited Transactions Greedy (k >= n/2)          -> special fast path
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A0) BRUTE FORCE RECURSION (index, holding, cap)  — EXPLANATION PURPOSE ONLY
      - holding = 1 : humare paas stock hai
      - holding = 0 : humare paas stock nahi hai
      - cap = bache hue sells (transactions), har “sell” cap ko 1 ghataata hai
      - TLE hoga, par thinking clear hoti hai.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A0_BruteForce {
    int rec(int i, int holding, int cap, vector<int>& a) {
        // Base cases
        if (i == (int)a.size() || cap == 0) return 0;          // array khatam ya sells khatam

        // Choice 1: skip (aaj kuch nahi karte)
        int ans = rec(i+1, holding, cap, a);

        if (holding) {
            // Agar stock haath me hai, do options:
            //  - sell karo -> profit add hoga, cap -- (kyunki ek sell complete hua)
            ans = max(ans, a[i] + rec(i+1, 0, cap-1, a));
        } else {
            // Agar stock nahi hai:
            //  - buy karo -> paisa kharch (profit -price), holding=1, cap same (sell pe cap ghatega)
            ans = max(ans, -a[i] + rec(i+1, 1, cap, a));
        }
        return ans;
    }
    int maxProfit(int k, vector<int>& prices) {
        return rec(0, 0, k, prices);
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A1) MEMOIZATION 3D DP (index x buy x cap)
      - buy: 1 matlab buy allowed state (holding==0), 0 matlab sell allowed state (holding==1)
      - cap: remaining sells
      - dp[i][buy][cap] stores best profit from i..end
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A1_Memo {
    int n;
    vector<vector<vector<int>>> dp;
    int solve(int i, int buy, int cap, vector<int>& a) {
        if (i == n || cap == 0) return 0;
        int &res = dp[i][buy][cap];
        if (res != INT_MIN) return res;

        if (buy) {
            // Buy state: ya to buy karo, ya skip karo
            int take    = -a[i] + solve(i+1, 0, cap, a);  // buy: paisa kharch
            int nottake =       solve(i+1, 1, cap, a);    // skip
            res = max(take, nottake);
        } else {
            // Sell state: ya to sell karo, ya skip karo
            int sell    =  a[i] + solve(i+1, 1, cap-1, a); // sell: paisa milta, cap--
            int notsell =       solve(i+1, 0, cap,   a);   // skip
            res = max(sell, notsell);
        }
        return res;
    }
    int maxProfit(int k, vector<int>& prices) {
        n = (int)prices.size();
        if (n == 0 || k == 0) return 0;
        // Optimization: agar k >= n/2 -> unlimited case
        if (k >= n/2) {
            int ans = 0; for (int i=1;i<n;i++) ans += max(0, prices[i]-prices[i-1]); return ans;
        }
        dp.assign(n, vector<vector<int>>(2, vector<int>(k+1, INT_MIN)));
        return solve(0, 1, k, prices);
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A2) TABULATION 3D DP (Bottom-Up)
      - dp[i][buy][cap] -> i se end tak ka best
      - transition i = n-1..0; buy ∈ {0,1}; cap = 1..k
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A2_Tab3D {
    int maxProfit(int k, vector<int>& a) {
        int n = (int)a.size(); if (!n || !k) return 0;
        if (k >= n/2) { int ans=0; for(int i=1;i<n;i++) ans+=max(0,a[i]-a[i-1]); return ans; }

        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(k+1, 0)));
        // Base: dp[n][*][*] = 0 and dp[*][*][0] = 0 already

        for (int i = n-1; i >= 0; --i) {
            for (int buy = 0; buy <= 1; ++buy) {
                for (int cap = 1; cap <= k; ++cap) {
                    if (buy) {
                        // buy ya skip
                        dp[i][buy][cap] = max(-a[i] + dp[i+1][0][cap],
                                               dp[i+1][1][cap]);
                    } else {
                        // sell ya skip
                        dp[i][buy][cap] = max( a[i] + dp[i+1][1][cap-1],
                                               dp[i+1][0][cap]);
                    }
                }
            }
        }
        return dp[0][1][k];
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A3) O(n*k) 1D DP with hold/release arrays  (+ Unlimited shortcut)
      - hold[t]    = t-th buy ke baad max profit (stock in hand)
      - release[t] = t-th sell ke baad max profit (no stock in hand)
      - Update order for t = 1..k each day:
           hold[t]    = max(hold[t],    release[t] - price)
           release[t] = max(release[t], hold[t]    + price)
      - Initial:
           release[0] = 0, hold[0] = -inf (invalid)
           For t>=1: release[t] = 0, hold[t] = -inf
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A3_HoldRelease {
    int maxProfit(int k, vector<int>& a) {
        int n = (int)a.size(); if (!n || !k) return 0;

        // k >= n/2 -> unlimited transactions: sum of positive differences
        if (k >= n/2) {
            int ans = 0; for (int i=1;i<n;i++) ans += max(0, a[i]-a[i-1]); return ans;
        }

        const int NEG_INF = -1e9;
        vector<int> hold(k+1, NEG_INF), release(k+1, 0); // release[0]=0, hold[0] invalid

        for (int price : a) {
            for (int t = 1; t <= k; ++t) {
                // Buy for t-th transaction (use release[t])
                hold[t]    = max(hold[t],    release[t] - price);
                // Sell for t-th transaction (finish it using hold[t])
                release[t] = max(release[t], hold[t]    + price);
            }
        }
        return release[k]; // after at most k sells
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A4) 2*k PARITY DP (1D ahead/curr) — buy/sell ko "parity" se track karte hain
      - transactionsLeft: 2*k (Buy, Sell, Buy, Sell, ...)
      - Even number -> BUY state, Odd -> SELL state  (or vice-versa; bas consistent raho)
      - ahead[t] = next day ke liye dp value (t remaining moves)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A4_Parity1D {
    int maxProfit(int k, vector<int>& a) {
        int n = (int)a.size(); if (!n || !k) return 0;
        // Unlimited shortcut (optional but nice)
        if (k >= n/2) { int ans=0; for(int i=1;i<n;i++) ans+=max(0,a[i]-a[i-1]); return ans; }

        vector<int> ahead(2*k + 1, 0), curr(2*k + 1, 0);

        for (int i = n-1; i >= 0; --i) {
            for (int t = 1; t <= 2*k; ++t) {
                // NOTE: yaha maine "even -> BUY" convention liya hai (same as your code)
                if (t % 2 == 0) {
                    // BUY: ya to lo (-price + ahead[t-1]) ya skip (ahead[t])
                    curr[t] = max(-a[i] + ahead[t-1], ahead[t]);
                } else {
                    // SELL: ya to becho (+price + ahead[t-1]) ya skip
                    curr[t] = max(a[i] + ahead[t-1], ahead[t]);
                }
            }
            ahead = curr; // shift a day left
        }
        return ahead[2*k]; // start with full 2*k moves left
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A5) CONSTANT SPACE for k=2  — 4 variables (buy1, sell1, buy2, sell2)
      - Super elegant for exactly two transactions.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A5_Keq2_Constant {
    int maxProfit(vector<int>& a) {
        if (a.empty()) return 0;

        // buy1:  first buy ke baad best (negative)
        int buy1  = -a[0];
        // sell1: first sell ke baad best
        int sell1 = 0;
        // buy2:  second buy ke baad best (use sell1 profit)
        int buy2  = -a[0];
        // sell2: second sell ke baad best (final)
        int sell2 = 0;

        for (int i = 1; i < (int)a.size(); ++i) {
            int p = a[i];
            buy1  = max(buy1,  -p);         // ya to pehle ka best buy1, ya aaj buy
            sell1 = max(sell1, buy1 + p);   // ya pehle ka best sell1, ya aaj sell
            buy2  = max(buy2,  sell1 - p);  // ya pehle ka best buy2, ya aaj fir buy (sell1 ka profit use)
            sell2 = max(sell2, buy2 + p);   // ya pehle ka best sell2, ya aaj fir sell
        }
        return sell2;
    }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  A6) UNLIMITED TRANSACTIONS GREEDY (k >= n/2)
      - Simple: jitni baar price[i] > price[i-1], utna profit add kar do
      - Intuition: peaks & valleys ko sum karna = local profits ka sum = global optimum
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct A6_UnlimitedGreedy {
    int maxProfit(vector<int>& a) {
        int n=(int)a.size(), ans=0;
        for (int i=1;i<n;i++) if (a[i] > a[i-1]) ans += a[i]-a[i-1];
        return ans;
    }
};

// ------------------------------- DEMO MAIN (optional) -------------------------------
// Comment out if using on judges that expect only one Solution class.
/*
int main(){
    vector<int> prices = {3,3,5,0,0,3,1,4};
    int k = 2;

    cout << "A0 Brute:            " << A0_BruteForce().maxProfit(k, prices) << "\n";
    cout << "A1 Memo 3D:          " << A1_Memo().maxProfit(k, prices) << "\n";
    cout << "A2 Tab 3D:           " << A2_Tab3D().maxProfit(k, prices) << "\n";
    cout << "A3 Hold/Release:     " << A3_HoldRelease().maxProfit(k, prices) << "\n";
    cout << "A4 Parity 1D:        " << A4_Parity1D().maxProfit(k, prices) << "\n";
    cout << "A5 k==2 Constant:    " << A5_Keq2_Constant().maxProfit(prices) << "\n";
    cout << "A6 Unlimited Greedy: " << A6_UnlimitedGreedy().maxProfit(prices) << "\n";
}
*/

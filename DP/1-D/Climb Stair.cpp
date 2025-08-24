// Notes: Climbing Stairs DP Solution

// 1. Problem: Find number of ways to reach the n-th stair, taking 1 or 2 steps at a time.

// 2. Approach: Use Dynamic Programming (DP) to store ways to reach each stair.

// 3. dp[i]: Number of ways to reach the i-th stair.

// 4. Base Case: Only 1 way to stay at ground (0-th stair).

// 5. Transition: 
//    - From (i-1)-th stair: dp[i] += dp[i-1]
//    - From (i-2)-th stair (if i >= 2): dp[i] += dp[i-2]

// 6. Final Answer: dp[n]

class Solution {
public:
    int climbStairs(int n) {
        // dp[i] ka matlab hai: i-th stair tak pahunchne ke kitne tarike hai
        vector<int> dp(n + 1, 0);  

        // Base case: 0-th stair (ground) tak pahunchne ka ek hi tarika hai → kuch mat karo
        dp[0] = 1;  

        // Ab hum har stair ke liye calculate karenge
        for (int i = 1; i <= n; i++) {
            // Step 1: ek step peeche se aana
            // Agar i-1 stair tak pahunchne ke X tarike the,
            // toh i-th stair tak aane ke bhi utne hi tarike honge us path ke liye
            dp[i] += dp[i - 1];

            // Step 2: do step peeche se aana (sirf tab jab i >= 2 ho)
            // Agar i-2 stair tak pahunchne ke Y tarike the,
            // toh i-th stair tak aane ke bhi utne hi tarike honge is path ke liye
            if (i >= 2) {
                dp[i] += dp[i - 2];
            }
        }

        // Answer hamesha dp[n] me hoga, kyunki hume n-th stair tak pahunchna hai
        return dp[n];
    }
};

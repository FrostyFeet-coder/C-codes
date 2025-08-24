/*
    House Robber Problem (Leetcode 198)
    -----------------------------------
    Ek list di hui hai non-negative integers ki, har ek house ka paisa batata hai.
    Aapko maximum paisa churaana hai bina police ko alert kiye (matlab, do consecutive houses nahi loot sakte).

    Approaches:
    1. Pure Recursion
    2. Recursion + Memoization (Top-Down DP)
    3. Tabulation (Bottom-Up DP)
    4. Space Optimized DP
*/

// 1. Pure Recursion
// -----------------
// Time Complexity: O(2^N) (har house ke liye do choices, isliye exponential)
// Space Complexity: O(N) (recursion stack)
class Solution {
public:
    // Recursive helper function jo max paisa calculate karta hai 'index' tak
    int solve(vector<int>& nums, int index) {
        // Base case: Agar index negative ho gaya toh koi house nahi bacha lootne ko
        if (index < 0) return 0;

        // Option 1: Current house loot lo, pichla skip karo
        int take = nums[index] + solve(nums, index - 2);

        // Option 2: Current house skip karo
        int nottake = solve(nums, index - 1);

        // Dono me se jo zyada paisa de, woh return karo
        return max(take, nottake);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        return solve(nums, n - 1); // Last house se start karo
    }
};

/*
    Problem: Is approach me same subproblem baar-baar calculate hoti hai,
    isliye time complexity exponential ho jaati hai.
*/

// 2. Recursion + Memoization (Top-Down DP)
// ----------------------------------------
// Time Complexity: O(N)
// Space Complexity: O(N) (recursion stack + dp array)
class Solution {
public:
    // Helper function jo memoization ke saath kaam karta hai
    int solve(vector<int>& nums, int index, vector<int>& dp) {
        if (index < 0) return 0;

        // Agar pehle se calculate kiya hai toh wahi result return karo
        if (dp[index] != -1) return dp[index];

        // Option 1: Current house loot lo
        int take = nums[index] + solve(nums, index - 2, dp);

        // Option 2: Current house skip karo
        int nottake = solve(nums, index - 1, dp);

        // Result store karo aur return karo
        return dp[index] = max(take, nottake);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1); // Memoization array initialize karo
        return solve(nums, n - 1, dp);
    }
};

/*
    Fayda: Har subproblem sirf ek baar solve hoti hai aur store ho jaati hai.
*/

// 3. Tabulation (Bottom-Up DP)
// ----------------------------
// Time Complexity: O(N)
// Space Complexity: O(N)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        // dp[i] me max paisa store hoga jo house i tak loot sakte ho
        vector<int> dp(n, 0);
        dp[0] = nums[0]; // Sirf ek house hai toh wahi loot lo
        dp[1] = max(nums[0], nums[1]); // Pehla ya dusra, jo zyada paisa de

        // dp array ko iteratively fill karo
        for (int i = 2; i < n; i++) {
            // Option 1: Current house loot lo aur dp[i-2] add karo
            // Option 2: Current house skip karo aur dp[i-1] lo
            dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
        }

        return dp[n - 1]; // Last house tak ka max paisa
    }
};

/*
    Fayda: Recursion nahi hai, sirf dp array fill karna hai.
*/

// 4. Space Optimized DP
// ---------------------
// Time Complexity: O(N)
// Space Complexity: O(1)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        // Sirf last do results yaad rakhne hain
        int prev2 = nums[0]; // dp[i-2]
        int prev = max(nums[0], nums[1]); // dp[i-1]

        for (int i = 2; i < n; i++) {
            int steal = nums[i] + prev2; // Current house loot lo
            int skip = prev;              // Current house skip karo
            int curr = max(steal, skip);  // Jo zyada paisa de, woh lo

            // Next iteration ke liye update karo
            prev2 = prev;
            prev = curr;
        }

        return prev; // Final answer
    }
};

/*
    Fayda: Sirf constant space lagta hai, kyunki sirf last do results yaad rakhne hain.
*/

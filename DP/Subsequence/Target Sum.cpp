// Approach 1: Subset Sum DP
// Idea: +ve aur -ve numbers ka sum nikal ke isko subset sum problem bana do
// Math: S1 - S2 = target, S1 + S2 = totalSum => S1 = (totalSum + target)/2

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = 0;
        // Sare elements ka sum nikal lo
        for (int x : nums) totalSum += x;

        // Agar answer possible hi nahi hai toh 0 return karo
        // (totalSum + target) agar odd hai toh answer possible nahi hai
        // ya phir target ka absolute value totalSum se bada hai toh bhi possible nahi
        if ((totalSum + target) % 2 != 0 || abs(target) > totalSum) return 0;

        // Subset sum ka target nikal lo
        int newTarget = (totalSum + target) / 2;

        // DP array banao, size newTarget+1, sabko 0 se initialize karo
        vector<int> dp(newTarget + 1, 0);

        // 0 sum ek hi tareeke se banta hai (kuch bhi na lo)
        dp[0] = 1;

        // Har number ke liye, possible sums update karo
        for (int num : nums) {
            // Peeche se iterate karo taki ek hi number bar bar na use ho
            for (int j = newTarget; j >= num; j--) {
                // Agar num lete ho toh ways add karo
                dp[j] += dp[j - num];
            }
        }

        // Final answer return karo
        return dp[newTarget];
    }
};


// Approach 2: Recursive DP (Memoization)
// Idea: Har index pe + ya - dono try karo, answer memoize karo

class Solution {
public:
    int dp[21][2001]; // DP array, index aur sum ke liye

    // Helper function: index, abhi tak ka sum, target
    int helper(vector<int>& nums, int index, int currentsum, int target) {
        // Base case: pura array dekh liya, sum match hua toh 1 way
        if (index == nums.size()) {
            return currentsum == target ? 1 : 0;
        }

        // DP check: pehle se answer hai toh wahi return karo
        if (dp[index][currentsum + 1000] != -1) 
            return dp[index][currentsum + 1000];

        // + lagao ya - lagao, dono ka answer add karo
        int add = helper(nums, index + 1, currentsum + nums[index], target);
        int sub = helper(nums, index + 1, currentsum - nums[index], target);

        // DP me store karo aur return karo
        return dp[index][currentsum + 1000] = add + sub;
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        // DP ko -1 se initialize karo
        memset(dp, -1, sizeof(dp));
        // 0 index se start karo, sum 0 se
        return helper(nums, 0, 0, target);
    }
};
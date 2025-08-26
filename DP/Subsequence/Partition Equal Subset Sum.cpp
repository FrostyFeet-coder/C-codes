#include <vector>
using namespace std;
class Solution {
public:
    // Memoization wali helper function
    // isSubsetPossible: kya index tak koi subset sum target bana sakta hai?
    bool isSubsetPossible(int idx, int target, vector<int>& nums, vector<vector<int>>& dp) {
        // Base case: agar target 0 ho gaya toh subset mil gaya
        if (target == 0) return true;
        // Agar index 0 pe ho aur target nums[0] ke barabar ho toh true
        if (idx == 0) return nums[0] == target;
        // Agar pehle se calculate kiya hai toh wahi value return kar do
        if (dp[idx][target] != -1) return dp[idx][target];

        // Option 1: current element nahi lete (nottake)
        bool nottake = isSubsetPossible(idx - 1, target, nums, dp);
        // Option 2: current element lete hain (take), lekin tabhi jab target >= nums[idx]
        bool take = false;
        if (target >= nums[idx]) {
            take = isSubsetPossible(idx - 1, target - nums[idx], nums, dp);
        }
        // Dono me se koi bhi true ho toh answer true
        return dp[idx][target] = take || nottake;
    }

    // Main function
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        // Step 1: Array ka total sum nikal lo
        for (int num : nums) sum += num;
        int n = nums.size();
        // Step 2: Agar sum odd hai toh partition possible nahi
        if (sum % 2 != 0) return false;
        int target = sum / 2;

        // Step 3: DP table bana lo, -1 ka matlab abhi calculate nahi hua
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        // Step 4: Helper function call karo
        return isSubsetPossible(n - 1, target, nums, dp);
    }
};



    // Tabulation wali approach (Bottom-Up DP)
    // isSubsetPossible: kya index tak koi subset sum target bana sakta hai?
bool canPartition(vector<int>& nums) {
        int sum = 0;
        // Step 1: Array ka total sum nikal lo
        for (int num : nums) {
            sum += num;
        }
        int n = nums.size();
        // Step 2: Agar sum odd hai toh partition possible nahi
        if (sum % 2 != 0) return false;

        int target = sum / 2;
        // Step 3: DP table bana lo, dp[i][t] = true agar 0..i tak koi subset t sum bana sakta hai
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // Step 4: Base cases
        // Har row ke liye target 0 ho toh empty subset se possible hai
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;   
        }
        // Sirf pehle element se agar target banta hai toh true
        if (nums[0] <= target) {
            dp[0][nums[0]] = true;
        }

        // Step 5: DP table fill karo
        for (int i = 1; i < n; i++) {
            for (int t = 1; t <= target; t++) {
                // Option 1: current element nahi lete (nottake)
                bool nottake = dp[i-1][t];
                // Option 2: current element lete hain (take), lekin tabhi jab t >= nums[i]
                bool take = false;
                if (t >= nums[i]) {
                    take = dp[i-1][t - nums[i]];
                }
                // Dono me se koi bhi true ho toh answer true
                dp[i][t] = take || nottake;
            }
        }

        // Step 6: Final answer, kya n-1 tak target sum possible hai?
        return dp[n-1][target];
    }
};


// Memoization wali approach (Top-Down DP) with detailed comments in Hinglish
class Solution {
public:
    // DP table: dp[n][sum] = -1 (abhi calculate nahi hua), 0 (false), 1 (true)
    int dp[201][10001];

    // Helper function: kya n elements me se koi subset sum bana sakta hai?
    bool solve(vector<int>& nums, int n, int sum) {
        // Base case: agar sum 0 ho gaya toh subset mil gaya
        if (sum == 0) {
            return true;
        }
        // Agar sum negative ho gaya ya elements khatam ho gaye toh possible nahi
        if (sum < 0 || n == 0) {
            return false;
        }
        // Agar pehle se calculate kiya hai toh wahi value return kar do
        if (dp[n][sum] != -1) {
            return dp[n][sum];
        }

        // Option 1: current element lete hain (agar possible ho)
        bool take = false;
        if (nums[n - 1] <= sum) {
            take = solve(nums, n - 1, sum - nums[n - 1]);
        }
        // Option 2: current element nahi lete
        bool nottake = solve(nums, n - 1, sum);

        // Dono me se koi bhi true ho toh answer true
        return dp[n][sum] = take || nottake;
    }

    // Main function: Partition Equal Subset Sum
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        // Step 1: Array ka total sum nikal lo
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }
        // Step 2: Agar sum odd hai toh partition possible nahi
        if (sum % 2 != 0) {
            return false;
        }
        // Step 3: DP table ko -1 se initialize kar lo (matlab abhi calculate nahi hua)
        memset(dp, -1, sizeof(dp));
        // Step 4: Helper function call karo, target sum = sum/2
        return solve(nums, n, sum / 2);
    }
};

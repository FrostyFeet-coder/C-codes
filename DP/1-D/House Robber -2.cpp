// House Robber II Problem - DP Approaches
// Hinglish Comments ke saath Detailed Notes + Time Complexity

// Approach 1: Simple Recursion (TLE ho sakta hai)
// ------------------------------------------------
// Time Complexity: O(2^n)  // har ghar pe 2 choices, toh exponential calls
// Space Complexity: O(n)   // recursion stack ki wajah se
#include <vector>
using namespace std;


class Solution {
public:
    // yeh function index tak ka max paisa return karega
    int solve(vector<int>& nums, int index) {
        // base case: agar index 0 se chhota ho gaya toh kuch nahi loot sakte
        if (index < 0) return 0;

        // Option 1: is ghar ko looto, aur 2 ghar peeche jao (kyunki adjacent nahi loot sakte)
        int take = nums[index] + solve(nums, index - 2);

        // Option 2: is ghar ko skip karo, pichle wale ghar pe jao
        int skip = solve(nums, index - 1);

        // dono me se jo zyada paisa de, woh return karo
        return max(take, skip);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        // agar sirf 1 ghar hai toh wahi loot lo
        if (n == 1) return nums[0];

        // Circular hai, toh ya toh pehla ghar lo ya last, dono nahi
        // Case 1: pehla ghar nahi loota (1 se n-1 tak)
        vector<int> temp1(nums.begin() + 1, nums.end());
        // Case 2: last ghar nahi loota (0 se n-2 tak)
        vector<int> temp2(nums.begin(), nums.end() - 1);

        // dono cases ka max le lo
        return max(solve(temp1, temp1.size() - 1), solve(temp2, temp2.size() - 1));
    }
};


// Approach 2: Recursion + Memoization (DP Top-Down)
// -------------------------------------------------
// Time Complexity: O(n)  // har index pe sirf ek baar call hoti hai
// Space Complexity: O(n) // dp array + recursion stack
class Solution {
public:
    // yeh function DP ke saath hai, taaki repeated calls na ho
    int solve(vector<int>& nums, int index, vector<int>& dp) {
        if (index < 0) return 0;
        // agar already calculate kar chuke hain toh wahi return karo
        if (dp[index] != -1) return dp[index];

        int take = nums[index] + solve(nums, index - 2, dp);
        int skip = solve(nums, index - 1, dp);

        // result ko dp me store kar lo
        return dp[index] = max(take, skip);
    }

    // yeh helper function hai, jo ek array ke liye max paisa nikalta hai
    int rob1(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1); // -1 ka matlab abhi calculate nahi hua
        return solve(nums, n - 1, dp);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        // pehla ghar exclude karo
        vector<int> temp1(nums.begin() + 1, nums.end());
        // last ghar exclude karo
        vector<int> temp2(nums.begin(), nums.end() - 1);

        // dono cases ka max le lo
        return max(rob1(temp1), rob1(temp2));
    }
};


// Approach 3: Tabulation (DP Bottom-Up)
// -------------------------------------
// Time Complexity: O(n)  // ek hi baar loop chalta hai
// Space Complexity: O(n) // dp array use ho rahi hai
class Solution {
public:
    // yeh function tabulation se solve karta hai (bottom-up)
    int rob1(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0]; // pehla ghar loota
        dp[1] = max(nums[0], nums[1]); // pehla ya dusra, jo zyada paisa de

        // har ghar ke liye check karo, lootna hai ya skip karna hai
        for (int i = 2; i < n; i++) {
            dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
        }

        // last ghar tak ka max paisa return karo
        return dp[n-1];
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        vector<int> temp1(nums.begin() + 1, nums.end());
        vector<int> temp2(nums.begin(), nums.end() - 1);

        return max(rob1(temp1), rob1(temp2));
    }
};


// Approach 4: Space Optimized DP (Only 2 variables)
// -------------------------------------------------
// Time Complexity: O(n)  // ek hi baar loop chalta hai
// Space Complexity: O(1) // sirf 2 variables use ho rahe hain, koi extra array nahi
class Solution {
public:
    // yeh function sirf 2 variables me kaam karta hai (space optimized)
    int rob1(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int prev2 = nums[0]; // i-2 wala ghar
        int prev = max(nums[0], nums[1]); // i-1 wala ghar

        // har ghar ke liye check karo
        for (int i = 2; i < n; i++) {
            int steal = nums[i] + prev2;  // is ghar ko loot ke prev2 add karo
            int skip = prev;              // is ghar ko skip karo
            int curr = max(steal, skip);  // dono me se max

            // variables update karo aage ke liye
            prev2 = prev;
            prev = curr;
        }

        // last ghar tak ka max paisa
        return prev;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        vector<int> temp1(nums.begin() + 1, nums.end());
        vector<int> temp2(nums.begin(), nums.end() - 1);

        return max(rob1(temp1), rob1(temp2));
    }
};

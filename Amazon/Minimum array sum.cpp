#include <vector>
#include <algorithm>
using namespace std;    

class Solution {
public:
    int n;
    vector<vector<vector<int>>> dp; 

    // Recursive function jo har index par decide karega ki konsa operation lagana hai
    int solve(vector<int>& nums, int index, int k, int op1, int op2) {
        // Base Case: agar saare elements process ho gaye
        if (index == n) return 0;

        // Agar dp me answer pehle se pada hai toh wahi return kar do (memoization)
        if (dp[index][op1][op2] != -1) return dp[index][op1][op2];

        // STEP 1: Koi operation na lagao, seedha value add karo
        int ans = nums[index] + solve(nums, index + 1, k, op1, op2);

        // STEP 2: Operation 1 lagao (divide by 2)
        if (op1 > 0) {
            // ceil(nums[index]/2) ka formula -> (nums[index] + 1) / 2
            int newVal = (nums[index] + 1) / 2;
            ans = min(ans, newVal + solve(nums, index + 1, k, op1 - 1, op2));
        }

        // STEP 3: Operation 2 lagao (subtract k)
        if (op2 > 0 && nums[index] >= k) {
            int newVal = nums[index] - k;
            ans = min(ans, newVal + solve(nums, index + 1, k, op1, op2 - 1));
        }

        // STEP 4: Dono operations lagao (op1 + op2)
        if (op1 > 0 && op2 > 0) {
            // Case A: Pehle divide fir subtract
            int newVal1 = (nums[index] + 1) / 2;  // pehle divide kiya
            if (newVal1 >= k) { 
                ans = min(ans, (newVal1 - k) + solve(nums, index + 1, k, op1 - 1, op2 - 1));
            }

            // Case B: Pehle subtract fir divide
            if (nums[index] >= k) {
                // Pehle subtract kiya, fir us result ko divide by 2 kiya
                int newVal2 = (nums[index] - k + 1) / 2;  // ceil lagane ke liye +1
                ans = min(ans, newVal2 + solve(nums, index + 1, k, op1 - 1, op2 - 1));
            }
        }

        // Answer ko dp me store kar ke return karo
        return dp[index][op1][op2] = ans;
    }

    // Main function jo user call karega
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        n = nums.size();
        // DP ko initialise karo -1 se
        dp.assign(n, vector<vector<int>>(op1 + 1, vector<int>(op2 + 1, -1)));
        return solve(nums, 0, k, op1, op2);
    }
};

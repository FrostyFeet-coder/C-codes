class Solution {
public:
    int solve(vector<int>&nums , int idx , int previdx ,vector<vector<int>>&dp){
        if(idx == nums.size())return 0;

        if(dp[idx][previdx + 1] != - 1) return dp[idx][previdx + 1];

        int take = 0;

        int nottake = solve(nums , idx  + 1 , previdx ,dp);

        if(previdx == -1 || nums[idx] > nums[previdx]){
            take = 1 + solve(nums , idx + 1 , idx , dp);
        }

        return dp[idx][previdx + 1] = max(take , nottake);
    }

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>dp( n + 1 , vector<int>(n + 2 , -1));
        return solve(nums , 0 , -1 , dp);
    }
};
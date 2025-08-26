// Partition Array Into Two Arrays to Minimize Sum Difference
// Topper Notes Style

// Problem: Ek array diya hai, usko do subsets me baantna hai taki dono ke sums ka absolute difference minimum ho.

// Approach 1: DP (Subset Sum) - O(n * sum) time/space
// Jab array ke elements ka sum chhota ho (jaise ≤ 1e5), tab use karo.

class Solution {
public:
    // Do subsets ke sums ka minimum possible difference return karta hai
    int minSubsetSumDifference(vector<int>& arr, int n) {
        int totSum = accumulate(arr.begin(), arr.end(), 0); // Pura array ka sum nikal lo

        // dp[i] = kya sum 'i' kisi subset se ban sakta hai
        vector<bool> dp(totSum + 1, false);
        dp[0] = true; // sum 0 to hamesha possible hai, kyunki empty subset le sakte hain

        // Har element ke liye check karo ki kaunse sums possible ho sakte hain
        for (int num : arr) {
            // Backwards traverse karo taki ek hi element do baar na le lein
            for (int j = totSum; j >= num; --j) {
                // Agar j-num pehle se possible hai to j bhi ab possible ho jayega
                dp[j] = dp[j] || dp[j - num];
            }
        }

        // totSum/2 ke sabse kareeb wala subset sum dhoondo
        // Kyunki difference minimum tabhi hoga jab dono subsets ka sum aas paas ho
        int mini = INT_MAX;
        for (int s1 = 0; s1 <= totSum / 2; ++s1) {
            if (dp[s1]) { // Agar s1 possible hai
                int s2 = totSum - s1; // Dusre subset ka sum
                mini = min(mini, abs(s2 - s1)); // Minimum difference update karo
            }
        }
        return mini;
    }

    int minimumDifference(vector<int>& nums) {
        return minSubsetSumDifference(nums, nums.size());
    }
};

// Notes:
// - DP[i][j]: Kya sum 'j' pehle 'i' elements se possible hai?
// - Sirf 1D DP chahiye (space optimized).
// - Sirf tab feasible jab total sum chhota ho (warna memory/time error).

// Approach 2: Meet in the Middle - O(2^(n/2) * log(2^(n/2)))
// Jab n chhota ho (≤ 30), lekin sum bada ho, tab use karo.

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size(), sum = accumulate(nums.begin(), nums.end(), 0); // Total sum nikal lo
        int N = n / 2; // Array ko do equal halves me baant do
        vector<vector<int>> left(N + 1), right(N + 1);

        // Dono halves ke liye saare subset sums banao
        // Mask se har possible subset ka sum nikal rahe hain
        for (int mask = 0; mask < (1 << N); ++mask) {
            int l_sum = 0, r_sum = 0, cnt = 0;
            for (int i = 0; i < N; ++i) {
                if (mask & (1 << i)) { // Agar i-th element subset me hai
                    l_sum += nums[i]; // Left half ka sum
                    r_sum += nums[i + N]; // Right half ka sum
                    cnt++; // Kitne elements liye hain
                }
            }
            left[cnt].push_back(l_sum); // cnt elements ka sum left me
            right[cnt].push_back(r_sum); // cnt elements ka sum right me
        }

        // Right half ke sums ko sort karo taki binary search kar sakein
        for (int i = 0; i <= N; ++i) sort(right[i].begin(), right[i].end());

        // Sabse pehle, pura left ya pura right lene par difference check karo
        int res = abs(sum - 2 * left[N][0]);
        res = min(res, abs(sum - 2 * right[N][0]));

        // Sab possible splits try karo (k elements left me, N-k right me)
        for (int k = 1; k < N; ++k) {
            for (int a : left[k]) { // Left half ke k elements ka sum
                int b_target = (sum - 2 * a) / 2; // Right half me kaunsa sum lena chahiye taki difference minimum ho
                auto& v = right[N - k];
                auto it = lower_bound(v.begin(), v.end(), b_target); // Binary search se closest sum dhoondo

                // Closest value >= b_target check karo
                if (it != v.end())
                    res = min(res, abs(sum - 2 * (a + *it)));
                // Closest value < b_target bhi check karo
                if (it != v.begin()) {
                    --it;
                    res = min(res, abs(sum - 2 * (a + *it)));
                }
            }
        }
        return res;
    }
};

// Notes:
// - Array ko do halves me baanto.
// - Dono halves ke saare subset sums banao (masking se).
// - Har split ke liye best match binary search se dhoondo taki difference minimum ho.
// - Badi sum ke liye fast hai, feasible jab n ≤ 30 ho.

// Summary:
// - Chhota sum ho to DP use karo, warna Meet in the Middle jab n chhota ho aur sum bada ho.

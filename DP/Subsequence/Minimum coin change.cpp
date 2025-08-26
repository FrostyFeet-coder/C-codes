// -----------------------------------------------------------------------------
// Solution 1: Recursive + Memoization
// Time Complexity: O(n * amount)
// Space Complexity: O(n * amount) (for dp table + recursion stack)
// -----------------------------------------------------------------------------
class Solution {
public:
    // Recursive + Memoization function
    int solve(vector<int>& coins, int amount , int index , vector<vector<int>>& dp) {
        // ✅ base case 1: agar amount 0 ho gaya toh iska matlab solution mil gaya
        if (amount == 0) return 0;

        // ✅ base case 2: agar index < 0 (matlab koi coins bache hi nahi)
        // aur amount abhi bhi > 0 hai, toh solution possible nahi hai
        // is case me hum ek bada number (1e9) return karte hain to denote "impossible"
        if (index < 0) return 1e9; 

        // ✅ agar dp me already answer pada hai toh wahi return kar do (memoization)
        if (dp[index][amount] != -1) return dp[index][amount];

        // 🚫 option 1: current coin ko **nahi lena**
        int notTake = solve(coins , amount , index - 1 , dp);

        // ✅ option 2: current coin lena (lekin tabhi agar coin ki value <= remaining amount)
        int take = 1e9; // initially assume impossible
        if (coins[index] <= amount) {
            // agar lete hain toh 1 coin use kiya + remaining amount solve karna h same index se
            take = 1 + solve(coins , amount - coins[index] , index , dp);
        }

        // dono me se minimum answer lena hai (coin kam se kam use karne hain)
        return dp[index][amount] = min(take , notTake);
    }

    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();

        // ✅ dp array banaya jaha dp[index][amount] store karega 
        // minimum coins chahiye "amount" banane ke liye using coins[0..index]
        vector<vector<int>> dp(n , vector<int>(amount + 1, -1));

        // recursion start karenge last index se (n-1)
        int ans = solve(coins , amount , n - 1 , dp);

        // agar ans abhi bhi 1e9 ke barabar hai toh iska matlab solution possible nahi hai
        return (ans >= 1e9) ? -1 : ans;
    }
};


// -----------------------------------------------------------------------------
// Solution 2: 1D DP (Tabulation)
// Time Complexity: O(n * amount)
// Space Complexity: O(amount)
// -----------------------------------------------------------------------------
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        const int INF = 1e9;
        vector<int> dp(amount + 1, INF);
        dp[0] = 0; // 0 amount = 0 coins

        // Har coin ke liye, uske multiples update karo
        for (int c : coins) {
            for (int j = c; j <= amount; j++) {
                if (dp[j - c] < INF) {
                    dp[j] = min(dp[j], 1 + dp[j - c]);
                }
            }
        }

        return (dp[amount] >= INF) ? -1 : dp[amount];
    }
};


// -----------------------------------------------------------------------------
// Solution 3: Space Optimized 2D DP (Tabulation)
// Time Complexity: O(n * amount)
// Space Complexity: O(amount)
// -----------------------------------------------------------------------------
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();  
        // n = total coin denominations

        // ✅ Hum dp[i][j] ko represent karenge ek row ke form me
        // prev[j] -> pehle wale coin tak ka result
        // curr[j] -> current coin tak ka result
        // Initialize INF = 1e9 (matlab initially impossible)
        vector<int> prev(amount + 1, 1e9), curr(amount + 1, 1e9);

        // ✅ Base Case 1:
        // Agar amount = 0 hai → hamesha 0 coins chahiye
        // isliye 0th column me har row pe value = 0 hogi
        prev[0] = 0;  

        // ✅ Base Case 2:
        // Sirf first coin (coins[0]) use karke kaise banega
        // Agar j divisible by coins[0], toh ban sakta hai
        // Example: coins[0] = 2, amount = 6 → 3 coins lagenge
        for (int j = 0; j <= amount; j++) {
            if (j % coins[0] == 0) 
                prev[j] = j / coins[0];
        }

        // ✅ Transition (Baki coins ke liye)
        // Har coin index = 1...n-1 check karenge
        for (int i = 1; i < n; i++) {
            curr[0] = 0; // 0 amount ke liye hamesha 0 coins
            for (int j = 1; j <= amount; j++) {

                // Option 1: NOT TAKE → current coin ko ignore karo
                // upar wali row ka answer lelo
                int nottake = prev[j];

                // Option 2: TAKE → agar coins[i] <= j
                // toh ek coin use karo + bachi hui amount ka answer lo
                // Yaha dhyaan: same row "curr" se (j - coins[i]) lenge
                // kyunki coin unlimited use ho sakta hai
                int take = 1e9;
                if (coins[i] <= j) {
                    take = 1 + curr[j - coins[i]];
                }

                // Final: dono me se min lena hai
                curr[j] = min(take, nottake);
            }

            // ✅ Row shift:
            // Ab prev = curr ho jayega, next iteration ke liye
            prev = curr;
        }

        // ✅ Final Answer:
        // Agar answer abhi bhi INF hai → not possible
        // warna prev[amount] return karo
        return prev[amount] >= 1e9 ? -1 : prev[amount];
    }
};


// -----------------------------------------------------------------------------
// Solution 4: 1D DP (Tabulation, concise)
// Time Complexity: O(n * amount)
// Space Complexity: O(amount)
// -----------------------------------------------------------------------------
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] = minimum coins needed for amount i
        vector<int> dp(amount + 1, 1e9);  
        dp[0] = 0; // base case: 0 coins to make 0

        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }

        return dp[amount] == 1e9 ? -1 : dp[amount];
    }
};


// -----------------------------------------------------------------------------
// Solution 5: 1D DP (Tabulation, alternate style)
// Time Complexity: O(n * amount)
// Space Complexity: O(amount)
// -----------------------------------------------------------------------------
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] = minimum coins chahiye to make 'i' amount
        // initially sabko INF (bahut bada number) set kar dete h 
        // taki min() karte time galat answer na aaye
        vector<int> dp(amount + 1, 1e9);  

        dp[0] = 0;  
        // base case: agar amount = 0 h, toh 0 coins lagte h (kuch bhi nhi chahiye)

        // har coin ke liye loop chalayenge
        for (int coin : coins) {
            // ab dekho, iss coin ko use karke 
            // 'coin' se lekar 'amount' tak ke dp update karenge
            for (int i = coin; i <= amount; i++) {
                // option1: pehle ka dp[i] (jo ab tak ka best h)
                // option2: dp[i - coin] + 1 (yani agar i-banane k liye ek coin aur add kar du)
                // dono me se min lenge
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }

        // agar dp[amount] abhi bhi INF h matlab koi solution hi nhi h
        return dp[amount] == 1e9 ? -1 : dp[amount];
    }
};

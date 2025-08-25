class Solution {
public:
    // dp[row][col1][col2] -> max cherries dono robots is state se collect karenge
    // row -> abhi kaunsa row par hai
    // col1 -> robot1 ka column
    // col2 -> robot2 ka column
    int dp[71][71][71]; // constraints me max row/col = 70 hi hai

    int solve(vector<vector<int>>& grid, int row, int col1, int col2){
        int n = grid.size();
        int m = grid[0].size();

        // 1️⃣ Out of bounds check → agar koi robot grid ke bahar chala gaya toh invalid
        if(col1 < 0 || col2 < 0 || col1 >= m || col2 >= m) 
            return -1e8; // -infinity return karenge taki ye path kabhi choose na ho

        // 2️⃣ Base case → agar last row pe aa gaye
        if(row == n-1){
            if(col1 == col2) 
                return grid[row][col1]; // dono ek hi cell par hai toh ek hi baar count
            return grid[row][col1] + grid[row][col2]; // dono alag cells pe hai toh dono ka add
        }

        // 3️⃣ Memoization check → agar dp already filled hai toh wahi answer use karlo
        if(dp[row][col1][col2] != -1) 
            return dp[row][col1][col2];

        // 4️⃣ Current row ka contribution calculate karo
        // agar dono same cell par hai toh ek hi baar add
        // warna dono ka sum le lo
        int cherries = 0;
        if(col1 == col2) cherries = grid[row][col1];
        else cherries = grid[row][col1] + grid[row][col2];

        // 5️⃣ Next row ke liye 9 moves possible hai (robot1 ke liye -1,0,+1 aur robot2 ke liye -1,0,+1)
        int maxi = 0;
        for(int d1=-1; d1<=1; d1++){          // robot1 ki move
            for(int d2=-1; d2<=1; d2++){      // robot2 ki move
                // recursive call next row pe dono ko bhej do
                int next = solve(grid, row+1, col1+d1, col2+d2);
                maxi = max(maxi, cherries + next); 
            }
        }

        // 6️⃣ Save answer in dp table aur return
        return dp[row][col1][col2] = maxi;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        // dp ko -1 se initialize karna zaruri hai taki memoization work kare
        memset(dp, -1, sizeof(dp)); 
        int n = grid.size();
        int m = grid[0].size();
        // Start state: row=0, robot1=col0, robot2=col(m-1)
        return solve(grid, 0, 0, m-1);
    }
};

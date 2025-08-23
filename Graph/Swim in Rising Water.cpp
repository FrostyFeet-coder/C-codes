class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int t = grid.size();

        // Min-heap (priority_queue with greater) use kar rahe hain
        // Pair ka format: {time_taken_tak, {row, col}}
        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> q;
                        
        // Visited matrix taaki same cell dobara na jaaye
        vector<vector<bool>> visi(t, vector<bool>(t, false));  

        // Starting cell se start karte hain (0,0) aur time = grid[0][0]
        q.push({grid[0][0], {0, 0}});
        visi[0][0] = true;

        // Direction arrays (Right, Down, Left, Up)
        int drow[] = {0, 1, 0, -1};
        int dcol[] = {1, 0, -1, 0};

        while (!q.empty()) {
            // Heap me se minimum time waala cell nikaalo
            auto [time, pos] = q.top();             
            int row = pos.first, col = pos.second;
            q.pop();

            // Agar destination (t-1, t-1) mil gaya toh yehi answer hai
            if (row == t - 1 && col == t - 1) {
                return time;
            }
           
            // 4 directions me move karte hain
            for (int i = 0; i < 4; i++) {       
                int nrow = row + drow[i];
                int ncol = col + dcol[i];

                // Valid boundary check + not visited
                if (nrow >= 0 && ncol >= 0 && nrow < t && ncol < t && !visi[nrow][ncol]) {
                    visi[nrow][ncol] = true;

                    // max(time, grid[nrow][ncol]) ka matlab:
                    // - Ab tak ka max water level ya cell value jitna bhi ho, utna wait karna padega
                    // - Ye ensure karta hai ki hum lowest possible "maximum" time choose karte rahein
                    q.push({max(time, grid[nrow][ncol]), {nrow, ncol}});
                }
            }
        }

        return -1;  // theoretically kabhi nahi aayega, kyunki destination reachable hai
    }
};

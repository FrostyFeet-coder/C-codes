class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();        // total rows ki count nikal li
        int m = grid[0].size();     // total columns ki count nikal li

        // BFS ke liye ek queue banayi jisme hum store karenge:
        //   -> {row, col}, time
        queue<pair<pair<int,int>,int>> q;

        // Visited matrix banayi jo track karegi ki kaunsa cell already rotten ho gaya
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // Step 1: sare rotten oranges (2) ko queue me daal do starting time = 0 ke sath
        for(int i = 0 ; i < n; i++){
            for(int j = 0 ; j < m ; j++){
                if(grid[i][j] == 2){  
                    q.push({{i ,j}, 0});   // rotten orange ko queue me daal diya
                    vis[i][j] = 2;         // isko visited (rotten) mark kar diya
                }
            }
        }
        
        // Direction arrays -> upar, right, niche, left
        int dirx[4] = {-1 , 0 , 1 ,0};
        int diry[4] = { 0 , 1,  0,-1};

        int time = 0;  // max time store karne ke liye

        // Step 2: BFS chalao
        while(!q.empty()){
            int r = q.front().first.first;    // current row
            int c = q.front().first.second;   // current col
            int t = q.front().second;         // current time
            q.pop();

            time = max(time , t);  // ab tak ka maximum time update kar lo

            // Step 3: 4 directions me check karo
            for(int k = 0 ; k < 4 ; k++){
                int newr = dirx[k] + r;   // new row
                int newc = c + diry[k];   // new col

                // boundary check + fresh orange (1) check
                if(newr >= 0 && newr < n && newc >=0 && newc < m && 
                grid[newr][newc] == 1 && vis[newr][newc] != 2){
                    
                    // agar fresh orange mila to usko rotten bana do aur queue me daal do
                    q.push({{newr , newc} , t + 1});
                    vis[newr][newc] = 2;  // mark as rotten
                }
            }
        }

        // (Optional) Debug ke liye vis print kara
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j ++){
                cout<<vis[i][j] << " ";
            }
        }

        // Step 4: agar koi fresh orange bacha hai jo visited (rotted) nahi hua -> return -1
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j ++){
                if(grid[i][j] == 1 && vis[i][j] != 2) 
                    return -1;
            }
        }

        // warna jitna max time laga wahi ans hoga
        return time;
    }
};

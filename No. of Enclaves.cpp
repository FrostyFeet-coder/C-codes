#include <vector>
#include <queue>
using namespace std;    

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();   // rows ka size nikal liya
        int m = grid[0].size(); // cols ka size nikal liya

        // visited array banaya taaki pata chale konsa cell visit ho chuka hai
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // BFS ke liye queue
        queue<pair<int,int>> q;

        // left aur right boundary check kar rahe hai
        for(int i = 0 ; i < n ; i++){
            if(grid[i][0] == 1){   // agar left boundary pe land mila
                q.push({i , 0});
                vis[i][0] = 1;     // mark visited
            }
            if(grid[i][m -1] == 1){ // agar right boundary pe land mila
                q.push({i , m-1});
                vis[i][m-1] = 1;   // mark visited
            }
        }

        // top aur bottom boundary check kar rahe hai
        for(int j = 0 ; j < m ; j++){
            if(grid[0][j] == 1){   // agar top boundary pe land mila
                q.push({0 , j});
                vis[0][j] = 1;
            }
            if(grid[n-1][j] == 1){ // agar bottom boundary pe land mila
                q.push({n-1 , j});
                vis[n-1][j] = 1;
            }
        }   

        // 4 direction ke liye arrays
        int dirx[4] = {0 , -1 , 0 , 1};  
        int diry[4] = {1 , 0 , -1 , 0};
        
        // BFS chalayenge taaki boundary se connected land ko mark kar saken
        while(!q.empty()){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for(int k = 0 ; k < 4 ; k++){
                int newr = r + dirx[k];
                int newc = c + diry[k];

                // agar naya cell grid ke andar hai, visited nhi hai aur land hai
                if(newr >= 0 && newr < n && newc >= 0 && newc < m && !vis[newr][newc]
                && grid[newr][newc] == 1){
                    vis[newr][newc] = 1;      // mark visited
                    q.push({newr , newc});    // queue me daal do
                }
            }
        }

        // ab count karenge kitna land aisa bacha hai jo boundary se connected nhi tha
        int count = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(grid[i][j] == 1 && vis[i][j] == 0){
                    count ++;
                }
            }
        }

        return count; // enclaves ki total ginti
    }
};

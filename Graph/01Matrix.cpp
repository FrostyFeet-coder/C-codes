#include <vector>
#include <queue>
using namespace std;    

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        // distance matrix bana li initially INT_MAX se fill
        vector<vector<int>> dist(n , vector<int>(m, INT_MAX));

        // BFS ke liye queue
        queue<pair<int,int>> q;

        // Step 1: Saare 0 ko queue me daal do aur unka dist = 0
        // (kyunki wo already 0 hai unke liye distance 0 hi hoga)
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(mat[i][j] == 0){
                    q.push({i , j});
                    dist[i][j] = 0;
                }
            }
        }

        // 4 directions ke liye arrays
        int dirx[4] = {0 , -1 , 0 , 1};
        int diry[4] = {-1 , 0 , 1 , 0};

        // Step 2: BFS start
        while(!q.empty()){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            // 4 directions check karo
            for(int k = 0 ; k < 4 ; k++){
                int newr = r + dirx[k];
                int newc = c + diry[k];

                // Valid index check
                if(newr >= 0 && newr < n && newc >= 0 && newc < m){
                    // Agar abhi tak visited nahi hai (dist == INT_MAX)
                    if(dist[newr][newc] == INT_MAX){
                        // Update karo distance: parent cell + 1
                        dist[newr][newc] = dist[r][c] + 1;

                        // Push into queue
                        q.push({newr , newc});
                    }
                }
            }
        }

        // Final distance matrix return
        return dist;
    }
};

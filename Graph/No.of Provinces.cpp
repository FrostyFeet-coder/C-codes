#include <vector>
#include <queue>
using namespace std;

class Solution {
public:

    // BFS function ek node se start karke uske pure connected component ko visit karega
    void bfs(int node , vector<vector<int>>& adj , vector<bool>& vis) {
        queue<int> q;
        q.push(node);       // starting node ko queue me daala
        vis[node] = true;   // aur visited mark kar diya

        while(!q.empty()){
            int front = q.front();  
            q.pop();        

            // ab uske saare neighbours check karenge
            for(auto &neigh : adj[front]){
                if(!vis[neigh]){       // agar neighbour abhi tak visit nahi hua
                    q.push(neigh);     // queue me daal do
                    vis[neigh] = true; // aur visited mark kar do
                }
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<vector<int>> adj(n);  // adjacency list banayenge

        // adjacency matrix -> adjacency list conversion
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isConnected[i][j] == 1 && i != j) {
                    adj[i].push_back(j); // agar connection hai aur self-loop nahi hai to list me daal do
                }
            }
        }

        int count = 0; 
        vector<bool> vis(n, false); // visited array banaya

        // har node ke liye check karenge
        for(int i = 0; i < n; i++){
            if(!vis[i]){                // agar ye node abhi tak visit nahi hua
                bfs(i, adj, vis);       // to bfs chalao (poore component visit ho jayenge)
                count++;                // ek naya province mil gaya
            }
        }

        return count;   // total provinces return karenge
    }
};

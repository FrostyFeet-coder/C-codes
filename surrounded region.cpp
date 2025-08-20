#include <vector>
#include <queue>
using namespace std;    

class Solution {
public:

    // DFS function -> connected 'O' ko explore karega aur unhe temporary '#' se mark karega
    void dfs(vector<vector<char>>& board , int r , int c , int n , int m){
        // Agar index bahar chala gaya ya cell 'O' nahi hai toh return
        if (r < 0 || c < 0 || r >= n || c >= m || board[r][c] != 'O') return;

        // Current cell ko '#' mark kar diya (taaki border-connected 'O' yaad rahe)
        board[r][c] = '#';

        // 4 directions me DFS call
        dfs(board , r + 1 , c , n , m);  // neeche
        dfs(board , r - 1, c , n , m);   // upar
        dfs(board , r , c - 1, n , m);   // left
        dfs(board , r , c + 1, n , m);   // right
    }

    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        // Step 1: Border wali 'O' cells ko pakad ke DFS chalao
        for(int i = 0 ; i < n ; i++){
            if (board[i][0] == 'O') dfs(board, i, 0, n, m);       // left border
            if (board[i][m-1] == 'O') dfs(board, i, m-1, n, m);   // right border
        }

        for(int j = 0 ; j < m ; j++){
            if (board[0][j] == 'O') dfs(board, 0, j, n, m);       // top border
            if (board[n-1][j] == 'O') dfs(board, n-1, j, n, m);   // bottom border
        }

        // Step 2: Pure board ko traverse karo
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m; j++){
                // Agar koi 'O' bacha hua hai toh wo surrounded hai -> usse 'X' banado
                if(board[i][j] == 'O') board[i][j] = 'X';

                // Aur jo '#' se mark kiya tha unhe wapas 'O' banado (border connected wale the)
                if(board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
};

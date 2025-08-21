class Solution {
public:
    // DFS function jo recursively connected cells ko fill karega
    void dfs(vector<vector<int>>& image, int sr, int sc, int oldcolor , int color , int n ,int m){
        // Step 1: Boundary check -> agar row/col bahar chala gaya to return
        if(sr < 0 || sr >= n || sc < 0 || sc >= m ) return;

        // Step 2: Agar cell ka color oldcolor se match nahi karta
        // ya cell already new color ban chuka hai -> return
        if(image[sr][sc] != oldcolor || image[sr][sc] == color) return;

        // Step 3: Current cell ko new color assign kar do
        image[sr][sc] = color;

        // Step 4: 4 direction ke arrays (left, up, right, down)
        int dirx[4]= {0, -1 , 0 , 1};
        int diry[4]= {-1 , 0 , 1, 0};

        // Step 5: 4 direction me DFS call karo
        for(int k = 0 ; k < 4 ; k++){
            int newr = sr + dirx[k];   // next row
            int newc = sc + diry[k];   // next col
            
            // recursive call
            dfs(image , newr , newc , oldcolor , color , n ,m);
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int n = image.size();     // total rows
        int m = image[0].size();  // total columns

        // Agar starting pixel already new color ka hai -> kuch change nahi karna
        if(image[sr][sc] == color) return image;

        // DFS call karo starting pixel se
        dfs(image , sr , sc , image[sr][sc] , color , n ,m);

        // updated image return kar do
        return image;
    }
};

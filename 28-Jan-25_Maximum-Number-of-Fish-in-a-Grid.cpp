// Leetcode link   https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/description/

//DFS

class Solution {
public:
    int m,n;
    vector<vector<int>> dir = {{0,1}, { 0,-1}, {1,0}, {-1,0}};

    int dfs(int x, int y, vector<vector<int>>& grid)
    {
        if(x < 0 || x >=m || y < 0 || y >= n || grid[x][y] == 0)
            return 0;
        
        int fishCount = grid[x][y];
        grid[x][y] = 0;

        for(auto & d: dir)
        {
            int x_ = x + d[0];
            int y_ = y + d[1];

            fishCount += dfs(x_, y_, grid);
        }

        return fishCount;

    };
    
    int findMaxFish(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int r = 0;

        for(int i = 0; i< m; i++) {
            for(int j = 0; j<n ;j++) {
                if(grid[i][j] > 0)
                    r = max(r, dfs(i,j, grid));
            }
        }

        return r;
    };
};

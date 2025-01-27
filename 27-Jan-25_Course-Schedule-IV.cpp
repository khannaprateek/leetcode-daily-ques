//  Leetcode Link               : https://leetcode.com/problems/course-schedule-iv/description/

// Brute Force DFS
class Solution {
public:
    bool dfs(unordered_map<int, vector<int>> &adj, int src, int dest, vector<bool> &visited)
    {
        visited[src] = true;

        if(src == dest)
            return true;

        bool canReached = false;
        for(auto &node : adj[src])
        {
            if(!visited[node])
            {
                canReached = canReached || dfs(adj, node, dest, visited);
            }
        }

        return canReached;

    }

    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        unordered_map<int, vector<int>>  adj;

        for(auto p: prerequisites)
        {
            int u = p[0];
            int v = p[1];

            adj[u].push_back(v);
        }

        int Q = queries.size();
        vector<bool> res(Q);


        for(int i=0 ; i<Q ; i++)
        {
            vector<bool> visited(numCourses, false);

            int u = queries[i][0];
            int v = queries[i][1];

            res[i] =  dfs(adj, u, v, visited);
        }

        return res;
    }
};


//Another approach (Kan's algorithm topological sort)
class Solution {
public:
    bool dfs(unordered_map<int, vector<int>> &adj, int src, int dest, vector<bool> &visited)
    {
        visited[src] = true;

        if(src == dest)
            return true;

        bool canReached = false;
        for(auto &node : adj[src])
        {
            if(!visited[node])
            {
                canReached = canReached || dfs(adj, node, dest, visited);
            }
        }

        return canReached;

    }

    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        unordered_map<int, vector<int>>  adj;
        vector<int> inDeg(numCourses, 0);

        for(auto p: prerequisites)
        {
            int u = p[0];
            int v = p[1];

            adj[u].push_back(v);
            inDeg[v]++;
        }

        queue<int> que;
        for(int i=0 ; i<numCourses; i++)
        {
            if (inDeg[i] == 0)
                que.push(i);

        }
        
        unordered_map<int, unordered_set<int>> mp;

        while(!que.empty())
        {
            int node = que.front();
            que.pop();

            for(auto& nei: adj[node])
            {
                inDeg[nei]--;
                if(inDeg[nei] == 0)
                    que.push(nei);

                mp[nei].insert(node);

                for(auto& p: mp[node])
                    mp[nei].insert(p);
            }
        }
        
        

        int Q = queries.size();
        vector<bool> res(Q);
        for(int i=0 ; i<Q ; i++)
        {
            vector<bool> visited(numCourses, false);

            int u = queries[i][0];
            int v = queries[i][1];

            res[i] = mp[v].contains(u);
        }

        return res;
    }
};
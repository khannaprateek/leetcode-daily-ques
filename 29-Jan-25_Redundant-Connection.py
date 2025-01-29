# Leetcode link         https://leetcode.com/problems/redundant-connection/description


# DFS

class Solution:
    def dfs(self, adj: dict[int, List[int]], src: int,  dest: int, visited: List[bool] ) -> bool:
            visited[src] = True
            if src == dest:
                return True

            for nei in adj[src]:
                if visited[nei]:
                    continue
                
                if self.dfs(adj, nei, dest, visited):
                    return True
            return False

    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)

        adj = { i:[] for i in range(1,n+1)}
        
        for edge in edges:
            visited = [False for _ in range(n+1)]

            x = edge[0]
            y = edge[1]
            if x in adj and y in adj and self.dfs(adj, x, y, visited):
                return edge
            adj[x].append(y)
            adj[y].append(x)
        return []

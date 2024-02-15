#include<bits/stdc++.h>
using namespace std;

//01. NUMBER OF PROVINCES                                       {T.C = O(N^2), S.C = O(N+M)}
/*
Actually We are finding the components(islands) in this , we use simple dfs and take for loop for handling disconnected
components and in dfs Call we checks for index(for(int i = 0 ; i < n ; i++)) not for value(auto it : isConnected[node])
*/
class Solution {
public:
    void dfs(vector<vector<int>>&isConnected, vector<bool>&vis, int node){
        int n = isConnected.size();
        vis[node] = 1;
        for(int i = 0 ; i < n ; i++){                           //checks for index not value(auto it : isConnected[node])
            if(!vis[i] && isConnected[node][i] == 1){           //checks there is direct connnection.
                dfs(isConnected, vis, i);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int uniqueNodes = 0;
        vector<bool>vis(n, 0);
        for(int i = 0 ; i < n ; i++){                       //for disconnected components
            if(!vis[i]){
                dfs(isConnected, vis, i);                           //0 = nodeIndex
                uniqueNodes++;
            }
        }
        return uniqueNodes;
    }
};
/*
Example 1:
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Example 2:
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
*/


//02. FIND EVNETUAL SAFE STATES                                  {T.C = O(V+E), S.C = O(V)}
/*
Simply check the cycle , if the element is not present in cycle push that node in ans vector and return it.
*/
class Solution {
public:
    bool isCyclicDfs(vector<vector<int>>&adj, vector<bool>&vis, vector<bool>&dfsVis, int node){
        vis[node] = 1;
        dfsVis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(isCyclicDfs(adj, vis, dfsVis, it)){
                    return true;
                }
            }else if(dfsVis[it]){
                return true;
            }
        }
        dfsVis[node] = false;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {  //graph => adj
        int n = graph.size();
        vector<int>ans;
        vector<bool>vis(n, false);
        vector<bool>dfsVis(n, false);
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                isCyclicDfs(graph, vis, dfsVis, i);           
            }
        }
        for(int i = 0 ; i < n ; i++){
            if(dfsVis[i] == false){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
/*
Example 1:
Illustration of graph
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.
*/


//03. KEYS AND ROOMS                                          {T.C = O(V+E), S.C = O(V)}
/*
Simply do dfs and mark vis if any node is not visited then room cant open or ans is not possible.
*/
class Solution {
public:
    void dfs(vector<vector<int>>&rooms, vector<bool>&vis, int node){
        vis[node] = true;
        for(auto it : rooms[node]){
            if(!vis[it]){
                dfs(rooms, vis, it);
            }
        }
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool>vis(n, false);
        dfs(rooms, vis, 0);                      //0 = nodeindex
        for(auto it : vis){                      //if any room is not visited then ans not possible
            if(it ==  false){
                return false;
            }
        }
        return true;
    }
};
/*
Example 1:
Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation: 
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.

Example 2:
Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.
*/
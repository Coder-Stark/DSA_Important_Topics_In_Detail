//GRAPH
#include<bits/stdc++.h>
using namespace  std;

/*------------------------------------------------------- GRAPHS GENERAL ------------------------------------------------*/
//GRAPH
/*
//MINIMUM DISTANCE FINDING ALGORITHM
1. DIJKSTRA'S ALGO                  {not work for -ve Undirected weighted graph} //DAG
2. BELLMANFORD ALGO                 {work for -ve weighted graph}
3. FLOYD WARSHALL ALGO              {brute force algo}

//MINIMUM SPANNING TREE ALGORITHM
1. KRUSKAL'S ALGO          {intermediate result may be or may be not connected}
2. PRIM'S ALGO             {intermediate result always connected} 

DISJOINT SET = Intersection of all sets(components is null)                 {T.C = O(V+E), S.C = O(V)}  
//2 Functions = find and Union
1. COMBINE TWO GIVEN SETS.          {union find}
2. TELLS IF TWO MEMBERS BELONG TO SAME SETS OR NOT

DIJKSTRA ALGORITM                                                           {T.C = O(V^2) or O(V+ELOGV), S.C = O(V^2)}
//NOT APPLICABLE FOR NEGATIVE WEIGHT CYCLE (similar to BFS)
1. Create minHeap.
2. find shortest distance of each node from current node.

BELLMON FORD
APPLICABLE FOR NEGATIVE WEIGHT CYCLE
WORK ONLY FOR DIRECTED GRAPH (DAG) SO FOR UNDIRECTED GRAPH FIRST WE HAVE TO CONVERT IT INTO DIRECTED(make edges both side)

FLOYD WARSHALL 
1. Brute force algo
2. Three loops (k , i , j) take mindis = min(mindis[i][j], minDis[i][k]+minDis[k][j])

PRIM'S ALGORITHM                                                                {T.C = O(E*LOGV), S.C = O(V^2)}
//required adjacency list
//vertex based
//Data Structures = key(n, INT_MAX), mst(n, false), parent(n, -1)
ALGORITHM
1. Choose any vertex
2. Take minimum weight path.
3. Take care of previous paths as well.
4. Cycle should not be created.
5. Intermediate result is always connected

//KRUSKAL ALGORITHM
//require vector<vector<int>>vec               //{u, v, w}
ALGORITHM
1. Take a vector or map and store {u, v, w}
2. sort the vector on the basis of its weight.
3. then take sum, and iterate on vec
4. if the parent of u and v not same then take Union and sum+= w
5. finally return sum(minsum spanning tree)

//STRONGLY CONNECTED COMPONENTS (SCC)
ALGORITHM
1. sort the adjacency list using topological sort
2. create a transpose graph
3. dfs call on basis of above ordering (stack ordering)

//EULERIAN PATH
1. A Path of edges that visits all the edges in a graph exactly once.
2. Not all graphs have eulerian path.
3. All node have even degree except (2 nodes {starting & ending})
4. If any node degree > 2 then it is not having Eulerian Path.
//EULERIAN CIRCUIT
1. An eulerian path which starts and ends on the same node.
2. If the path is eulerian circuit then we can start any node(it will always ends on same node).
3. All vertices with non zero degree node need to belong to a single connected component. 
    (non zero degree nodes must be connected via a single component {one dfs only})
4. If all vertices have even degrees then it always a Eulerian Circuit.
//SEMI EULERIAN GRAPH
1. Eulerian Path Only (starting and ending node degree is always odd and other nodes have even degree)
2. Not Eulerian circuit.


TIPS
1. given a string change to required string with minium (value) is always a bfs Question.
2. for finding cycle is present or not in DAG we required vis && dfsVis both.
/*---------------------------------------------------------------------------------------------------------------------*/


//01. MINIMUM GENETIC MUTATION (change 1 string to another with minimum value)           {T.C = O(N*M*C{CHOICES}), S.C = O(N)}
//USING BFS
/*
First insert bank strings into set (easy access), take another set (visited) then return bfs, in bfs mark vis {vis.insert(start)}, take a queue
push start in q, and while q not empty , while(n--{size of queue}) base chech if frontNode == end directly return count, else check the 
options {ACGT}, iterate each ch of frontNode. and checks if not vis and present in set then mark vis.insert(nbr) and push q, and other 
the while(n--) increase count++.
*/
class Solution {
public:
    int bfs(string &start, string &end, unordered_set<string>&st, unordered_set<string>&vis, int count){
        vis.insert(start);
        queue<string>q;
        q.push(start);
        while(!q.empty()){
            int n = q.size();
            while(n--){
                auto frontNode = q.front();
                q.pop();
                if(frontNode == end){            //required ans found
                    return count;
                }

                for(auto it : "ACGT"){                  //choices
                    for(int i = 0 ; i  < frontNode.size(); i++){     //check with each choice replacement
                        string nbr = frontNode;
                        nbr[i] = it;

                        if(vis.find(nbr) == vis.end() && st.find(nbr) != st.end()){
                            vis.insert(nbr);
                            q.push(nbr);
                        }
                    }
                }
            }
            count++;
        }
        return -1;
    }
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string>st(bank.begin(), bank.end());    //bank element => set
        unordered_set<string>vis;
        int count = 0;
        return bfs(start, end, st, vis, count);           //0 = count
    }
};
/*
Example 1:
Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1

Example 2:
Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2
*/


//02. MOST STONES REMOVED WITH SAME ROW OR COLUMN (Finding total Components)      {T.C = O(N^2), S.C = O(N)}
//DFS
/*
First find the groups by dfs (!vis and row == currRow || col == currCol), then simply return 
n-group(smost stones removed {stones - group{at last 1 left from each grp}})
*/
class Solution {
public:
    void dfs(vector<vector<int>>&stones, vector<bool>&vis, int node){
        vis[node] = 1;
        for(int i = 0 ; i  < stones.size() ; i++){
            int sameRow = stones[node][0];                      //{x, y}
            int sameCol = stones[node][1];
            if(!vis[i] && (sameRow == stones[i][0] || sameCol == stones[i][1])){ //dfs only when stones are in same row or col
                dfs(stones, vis, i);
            }
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<bool>vis(n, false);
        int group = 0;
        for(int i = 0 ; i  < n ; i++){       //disconnected components
            if(!vis[i]){
                dfs(stones, vis, i);
                group++;
            }
        }
        return n-group;                //most stones removed {stones - group{at last 1 left from each grp}}
    }
};
/*
Example 1:
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.

Example 2:
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.

Example 3:
Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.
*/


//03. NEAREST EXIT FROM ENTRANCE IN MAZE (Findiing  mini steps to exit)     {T.C = O(N*M), S.C = O(N*M)}
//BFS
/*
Simply apply bfs on grid (in place of vis[node] = 1 = > maze[0][1] = '+') , check if  node is not intial node and  boundary(exit)
return steps else apply bfs on all 4 directions. 
*/
class Solution {
public:
    vector<vector<int>>directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size();
        int m = maze[0].size();
        
        int miniStep = 0;

        maze[entrance[0]][entrance[1]] = '+';              //vis[node] = 1
        
        queue<pair<int,int>>q;
        q.push({entrance[0], entrance[1]});

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto frontNode = q.front();
                q.pop();
                int i = frontNode.first;
                int j = frontNode.second;

                //check if not intial node and not on boundary
                if(!(i == entrance[0] && j == entrance[1]) && (i == 0 || j == 0 || i == n-1 || j == m-1)){
                    return miniStep;
                }
                for(auto it : directions){
                    int new_i = i + it[0];
                    int new_j = j + it[1];

                    if(new_i >= 0 && new_i < n && new_j >= 0 && new_j < m && maze[new_i][new_j] != '+'){
                        maze[new_i][new_j] = '+';                    //vis[node] = 1
                        q.push({new_i, new_j});
                    }
                }
            }
            miniStep++;
        }
        return -1;
    }
};
/*
Example 1:
Input: maze = [["+","+",".","+"],
               [".",".",".","+"],
               ["+","+","+","."]], 
            entrance = [1,2]
Output: 1
Explanation: There are 3 exits in this maze at [1,0], [0,2], and [2,3].
Initially, you are at the entrance cell [1,2].
- You can reach [1,0] by moving 2 steps left.
- You can reach [0,2] by moving 1 step up.
It is impossible to reach [2,3] from the entrance.
Thus, the nearest exit is [0,2], which is 1 step away.

Example 2:
Input: maze = [["+","+","+"],
               [".",".","."],
               ["+","+","+"]], 
            entrance = [1,0]
Output: 2
Explanation: There is 1 exit in this maze at [1,2].
[1,0] does not count as an exit since it is the entrance cell.
Initially, you are at the entrance cell [1,0].
- You can reach [1,2] by moving 2 steps right.
Thus, the nearest exit is [1,2], which is 2 steps away.

Example 3:
Input: maze = [[".","+"]], entrance = [0,0]
Output: -1
Explanation: There are no exits in this maze.
*/


//04. FIND IF PATH EXISTS IN GRAPH                                         {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Apply simple dfs, then check if(!vis[dest]) return false else true.
*/
class Solution {
public:
    void dfs(vector<vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    bool validPath(int n, vector<vector<int>>&edges, int source, int destination) {
        vector<vector<int>>adj(n);
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool>vis(n, false);

        dfs(adj, vis, source);
        if(!vis[destination]){
            return false;
        }
        return true;
    }
};
/*
Example 1:
Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

Example 2:
Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: There is no path from vertex 0 to vertex 5.
*/


//05. KEYS AND ROOMS                                                 {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Apply simple dfs, and iterate on vis(vector) , if all not vis then false else true.
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


//06a. IS GRAPH BIPARTITE                                                   {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Simple DFS vis(n, 0) ==> clr(n, -1), check if not dfsBipartite return false else return true, in dfs func mark clr[node] = currClr(1 or 0)
traverse on adj chech if(clr[it] == -1){not vis}  newClr = 1-currclr(changing color) and call dfs again else if adjacent clr is same
return false else return true.
*/
class Solution {
public:
    bool dfsBipartite(vector<vector<int>>&adj, vector<int>&clr, int node, int currClr){
        clr[node] = currClr;                     //vis[node] = 1;
        for(auto it : adj[node]){
            if(clr[it] == -1){                    //not visited
                int newClr = 1-currClr;           //1 to 0 or 0 to 1 (changing color)
                if(!dfsBipartite(adj, clr, it, newClr)){
                    return false;
                }
            }else if(clr[it] == clr[node]){         //adjacent color cant same
                return false;
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {       //graph = adjacencylist
        int n = graph.size();
        vector<int>clr(n, -1);                        //eg = red = 1, green = 0
        for(int i = 0 ;i < n ; i++){
            if(clr[i] == -1){                          //not visited
                if(!dfsBipartite(graph, clr, i, 1)){     //i = initial index, 1 = curr color(red)
                    return false;
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: graph = [[1,2,3],
                [0,2],
                [0,1,3],
                [0,2]]
Output: false
Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.

Example 2:
Input: graph = [[1,3],
                [0,2],
                [1,3],
                [0,2]]
Output: true
Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.
*/


//06b. POSSIBLE BIPARTITION                                                    {T.C = O(V+E), S.C = O(V)}
//DFS
/*
same as above
*/
class Solution {
public:
    bool dfsBipartite(vector<vector<int>>&adj, vector<int>&clr, int node, int currClr){
        clr[node] = currClr;                     //vis[node] = 1;
        for(auto it : adj[node]){
            if(clr[it] == -1){                    //not visited
                int newClr = 1-currClr;           //1 to 0 or 0 to 1 (changing color)
                if(!dfsBipartite(adj, clr, it, newClr)){
                    return false;
                }
            }else if(clr[it] == clr[node]){         //adjacent color cant same
                return false;
            }
        }
        return true;
    }
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {      //dislikes == edges
        vector<vector<int>>adj(n+1);                //1 based index
        for(auto it : dislikes){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int>clr(n+1, -1);                        //eg = red = 1, green = 0
        for(int i = 1 ;i <= n ; i++){
            if(clr[i] == -1){                          //not visited
                if(!dfsBipartite(adj, clr, i, 1)){     //i = initial index, 1 = curr color(red)
                    return false;
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: The first group has [1,4], and the second group has [2,3].

Example 2:
Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Explanation: We need at least 3 groups to divide them. We cannot put them in two groups.
*/


//07. SUM OF DISTANCES IN TREE   
//07a. BRUTE FORCE (DFS)                                                        {T.C = O(N^2), S.C = O(N)}
//DFS
//ERROR
/*
*/
class Solution {
public:
    int dfs(vector<vector<int>>& adj, vector<bool>& vis, int node, int parent) {
        int sum = 0;
        vis[node] = true;
        for(auto it : adj[node]) {
            if(!vis[it] && it != parent) {
                sum += dfs(adj, vis, it, node) + 1; // Increment sum by 1 for each recursive call
            }
        }
        return sum;
    }

    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for(auto it : edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            vector<bool> vis(n, false);
            ans[i] = dfs(adj, vis, i, -1); // -1 represents parent of the root node
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.

Example 2:
Input: n = 1, edges = []
Output: [0]

Example 3:
Input: n = 2, edges = [[1,0]]
Output: [1,1]
*/


//07b. OPTIMISED APPROACH DFS                                                   {T.C = O(N), S.C = O(N)}
//DFS
/*
Using 2 dfs first dfsRoot( gives first sum and count{stores children nodes}) another dfsAns( use formula) and find final vector ans.
Using formula
child_ans = parent_ans + X{no. of child's node(child included)} - remaining node({n-X})
*/
class Solution {
public:
    long long sum = 0;
    int N;
    int dfsRoot(vector<vector<int>>&adj, vector<int>&count, int node, int parent, int currDepth){
        int totalNodeCount = 1;                                    //1 = include that node
        sum += currDepth;
        for(auto it : adj[node]){
            if(it != parent){
                totalNodeCount += dfsRoot(adj, count, it, node, currDepth+1);       //parent => node , depth++
            }
        }
        count[node] = totalNodeCount;
        return totalNodeCount;
    }
    void dfsAns(vector<vector<int>>&adj, vector<int>&count, int node, int parent, vector<int>&ans){
        for(auto it : adj[node]){
            if(it != parent){
                //childAns = parentNode-no. of child + remaining
                ans[it] = ans[node] - count[it] + N-count[it];  
                dfsAns(adj, count, it, node, ans);                  //currNode=> it, parent => Node 
            }
        }
    }
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        N = n;
        vector<vector<int>>adj(n);
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int>count(n, 0);                             //store count of child(including that node)
        dfsRoot(adj, count, 0, -1, 0);                             //0 = node, -1 = parent or prevNode, 0 = currDepth

        vector<int>ans(n, 0);
        ans[0] = sum;                                      //first is already found
        dfsAns(adj, count, 0, -1, ans);                    //0 = node, -1 = parent or prevNode
        
        return ans;
    }
};
/*
Example 1:
Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.

Example 2:
Input: n = 1, edges = []
Output: [0]

Example 3:
Input: n = 2, edges = [[1,0]]
Output: [1,1]
*/


//08. ALL PATHS FROM SOURCE TO TARGET                                           {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Simple dfs (adj, src, tar, temp, ans), first push src to target check for base case if (src == target) push temp in ans vector else call dfs
for another node and after that pop back for backtrack.
*/
class Solution {
public:
    void dfs(vector<vector<int>>&adj, int src, int targ, vector<int>&temp, vector<vector<int>>&ans){
        temp.push_back(src);
        //base case
        if(src == targ){
            ans.push_back(temp);
        }else{
            for(auto it  : adj[src]){
                dfs(adj, it, targ , temp, ans);
            }
        }
        temp.pop_back();                           //backtrack
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) { //graph => adjacency list
        int n = graph.size();
        int source = 0;
        int target = n-1;
        vector<vector<int>>ans;
        vector<int>temp;
        dfs(graph, source, target, temp, ans);

        return ans;
    }
};
/*
Example 1:
Input: graph = [[1,2],[3],[3],[]]
Output: [[0,1,3],[0,2,3]]
Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

Example 2:
Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
*/


//09. MINIMUM TIME TO COLLECT ALL APPLES IN A TREE                                   {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Apply dfs(adj, hasApple, -1, 0) , not required vis cause it have no cycle(tree) {require parent}, now in dfs take time =  0 and iterate on adj
if(it != parent) then timeFromChild = dfs call if timefromchild > 0 or haveapple count it(time += timefromchild + 2{include inout edges})
finally return time.
*/
class Solution {
public:
    int dfs(vector<vector<int>>&adj, vector<bool>&hasApple, int parent, int node){
        int time = 0;
        //base case
        for(auto it : adj[node]){
            if(it != parent){
                int timeFromChild = dfs(adj, hasApple, node, it);                      //parent = > node, node-> it
                if(timeFromChild > 0 || hasApple[it]){        //below child have apple  or child have apple
                    time += timeFromChild + 2;            //2 = include (inOut edges)  
                }
            }
        }
        return time;
    }
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>>adj(n);
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return dfs(adj, hasApple, -1, 0);                     //-1 = parent, 0 = initial node
    }
};
/*
Example 1:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
Output: 8 
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.  

Example 2:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,false,true,false]
Output: 6
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.  

Example 3:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,false,false,false,false,false]
Output: 0
*/


//10. NUMBER OF NODES IN THE SUBTREE WITH THE SAME LABEL               {T.C = O(V+E), S.C = O(V)}
//DFS
/*
First create a graph(adjacency list) , then take an result and count (26) vector then make dfs call . In dfs
first extract the label of node, then find before count(0 for node) increase move to next count node and explore 
if node != parent then dfs(node => it , parent = > node) , then after varialbe store count[mylabel-'a'] 
finally in result[node] = after-before.
*/
class Solution {
public:
    void dfs(vector<vector<int>>&adj, int node, int parent, vector<int>& result, string &labels, vector<int>& count) {
        char mylabel = labels[node];
        int before = count[mylabel-'a'];           //before variable

        count[mylabel-'a']++;
        for(int &v : adj[node]) {                               //explore my subtree children
            if(v != parent){
                dfs(adj, v, node, result, labels, count);
            }
        }
        
        //after variable 
        int after = count[mylabel-'a'];
        result[node] = after - before;
    }
    
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>>adj(n);
        
        for(auto &vec : edges) {
            int u = vec[0];
            int v = vec[1];
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> result(n, 0);
        vector<int> count(26, 0);         //small letters
        
        dfs(adj, 0, -1, result, labels, count);
        
        return result;
        
    }
};
/*
Example 1:
Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], labels = "abaedcd"
Output: [2,1,1,1,1,1,1]
Explanation: Node 0 has label 'a' and its sub-tree has node 2 with label 'a' as well, thus the answer is 2. Notice that any node is part of its sub-tree.
Node 1 has a label 'b'. The sub-tree of node 1 contains nodes 1,4 and 5, as nodes 4 and 5 have different labels than node 1, the answer is just 1 (the node itself).

Example 2:
Input: n = 4, edges = [[0,1],[1,2],[0,3]], labels = "bbbb"
Output: [4,2,1,1]
Explanation: The sub-tree of node 2 contains only node 2, so the answer is 1.
The sub-tree of node 3 contains only node 3, so the answer is 1.
The sub-tree of node 1 contains nodes 1 and 2, both have label 'b', thus the answer is 2.
The sub-tree of node 0 contains nodes 0, 1, 2 and 3, all with label 'b', thus the answer is 4.

Example 3:
Input: n = 5, edges = [[0,1],[0,2],[1,3],[0,4]], labels = "aabab"
Output: [3,2,1,1,1]
*/


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//11a. BINARY TREE MAXIMUM PATH SUM                            
//DFS
/*
call solve(dfs function) in this base case if there is no root return zero, else make left and right call
now extract answer from 3 condition(anyonepath{all path have ans tak max ans path}, onlynode{with includeing path the
current sum is decrease down so exclude it and take node only}, only path {if the path is only max path }), important
for returning we call max of anyonepath and onlynode cause onlypath cant transfer upward.
*/
class Solution {
public:
    int solve(TreeNode* root, int &maxi){
        //base case
        if(!root){
            return 0;
        }

        int left = solve(root->left, maxi);
        int right = solve(root->right, maxi);
        
        int anyOnePath = max(left, right) + root->val;       //root->val == 1
        int onlyNode = root->val;
        int onlyPath = left + right + root->val;

        maxi = max({maxi, anyOnePath, onlyNode, onlyPath});
        
        return max(anyOnePath, onlyNode);                //onlyPath cant call for parent(its already ans)
    }
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;
        solve(root, maxi);
        return maxi;
    }
};
/*
*/
//11b. LONGEST PATH WITH DIFFERENT ADJACENT CHARACTERS            {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Just make graph first and longest1(left), longest2(right) then iterate on node and extrach childlongest path(dfs())
if current node have same char to node then skip else find l1 and l2 and then apply above 3 condition (root->val => 1)
*/
class Solution {
public:
    int dfs(vector<vector<int>>&adj, string &s, int node, int parnt, int &ans){
        int longest1 = 0;
        int longest2 = 0;

        for(auto it : adj[node]){
            if(it != parnt){
                int childLongestPath = dfs(adj, s, it, node, ans);

                if(s[it] == s[node]){                  //adjacent node same
                    continue;
                }

                //finding longest1 and longest2
                if(childLongestPath > longest2){
                    longest2 = childLongestPath;
                }
                if(longest1 < longest2){
                    swap(longest1, longest2);
                }
            }
        }

        //choose answer from 3 conditions(valid = anyonepath, onlynode, onlypath)
        int anyOnePath = max(longest1, longest2) + 1;        //1 = including current node
        int onlyNode = 1;                                    //1 = only curr node is valid
        int onlyPath = longest1 + longest2 + 1;

        ans = max({ans, anyOnePath, onlyNode, onlyPath});

        return max(anyOnePath, onlyNode);                      //onlyPath cant call for parent(its already ans)
    }
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>>adj(n);
        for(int i = 1; i < n ; i++){              //0 = -1 (no parent)
            int u = i;
            int v = parent[i];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int ans = 0;

        dfs(adj, s, 0, -1, ans);

        return ans;
    }
};
/*
Example 1:
Input: parent = [-1,0,0,1,1,2], s = "abacbe"
Output: 3
Explanation: The longest path where each two adjacent nodes have different characters in the tree is the path: 0 -> 1 -> 3. The length of this path is 3, so 3 is returned.
It can be proven that there is no longer path that satisfies the conditions. 

Example 2:
Input: parent = [-1,0,0,0], s = "aabc"
Output: 3
Explanation: The longest path where each two adjacent nodes have different characters is the path: 2 -> 0 -> 3. The length of this path is 3, so 3 is returned.
*/


//13. LEXICOGRAPHICALLY SMALLEST EQUIVALENT STRING                     {T.C = O(M*(V+E)), S.C = O(V)}
//DFS
/*
First make adj list using s1 and s2 then iterate on baseStr with the iteration call dfs and store ans in minChar which
will further push to ans string.In dfs function, mark minChar = node(current node) , mark vis, iterate on adj list
and if not vis then find minChar = min(minChar, dfs) and return minChar.
*/
class Solution {
public:
    char dfs(unordered_map<char, vector<char>>&adj, vector<bool>&vis , char node){
        char minChar = node;

        vis[node-'a'] = 1;
        for(auto it : adj[node]){
            if(!vis[it-'a']){
                minChar = min(minChar, dfs(adj, vis, it));
            }
        }
        return minChar;
    }
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.length();                    //s1.length() == s2.length()
        int m = baseStr.length();
        // vector<vector<char>>adj(n);         //run time error
        unordered_map<char, vector<char>>adj;
        for(int i = 0 ; i < n ; i++){
            char u = s1[i];
            char v = s2[i];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        string ans;
        for(int i = 0 ; i < m ; i++){
            char ch = baseStr[i];
            vector<bool>vis(26, 0);                 //small letters
            char minChar = dfs(adj, vis, ch);
            ans.push_back(minChar);
        }
        return ans;
    }
};
/*
Example 1:
Input: s1 = "parker", s2 = "morris", baseStr = "parser"
Output: "makkek"
Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [m,p], [a,o], [k,r,s], [e,i].
The characters in each group are equivalent and sorted in lexicographical order.
So the answer is "makkek".

Example 2:
Input: s1 = "hello", s2 = "world", baseStr = "hold"
Output: "hdld"
Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [h,w], [d,e,o], [l,r].
So only the second letter 'o' in baseStr is changed to 'd', the answer is "hdld".

Example 3:
Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
Output: "aauaaaaada"
Explanation: We group the equivalent characters in s1 and s2 as [a,o,e,r,s,c], [l,p], [g,t] and [d,m], thus all letters in baseStr except 'u' and 'd' are transformed to 'a', the answer is "aauaaaaada".
*/


//14. FIND CLOSEST NODE TO GIVEN TWO NODES                        {T.C = O(V+E), S.C = O(V)}
/*
*/
class Solution {
public:
    void dfs(vector<int>&edges, vector<int>&minDist, vector<bool>&vis, int node){
        vis[node] = true;
        int it = edges[node];                //for(auto it : adj[node])
        if(it != -1 && !vis[it]){            //node != -1 and not vis
            vis[it] = true;
            minDist[it] = minDist[node] + 1;
            dfs(edges, minDist, vis, it);
        }
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<int>minDist1(n, INT_MAX);
        vector<int>minDist2(n, INT_MAX);
        vector<bool>vis1(n, false);
        vector<bool>vis2(n, false);

        minDist1[node1] = 0;                 //self distance is 0
        minDist2[node2] = 0;

        dfs(edges, minDist1, vis1, node1);
        dfs(edges, minDist2, vis2, node2);

        int minDistNode = -1;
        int minDistCurr = INT_MAX;

        for(int i = 0 ; i < n ; i++){
            int maxDist = max(minDist1[i], minDist2[i]);
            if(minDistCurr > maxDist){
                minDistCurr = maxDist;
                minDistNode = i;
            }
        }

        return minDistNode;                             //we have to write node not dist
    }
};
/*
Example 1:
Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
Output: 2
Explanation: The distance from node 0 to node 2 is 1, and the distance from node 1 to node 2 is 1.
The maximum of those two distances is 1. It can be proven that we cannot get a node with a smaller maximum distance than 1, so we return node 2.

Example 2:
Input: edges = [1,2,-1], node1 = 0, node2 = 2
Output: 2
Explanation: The distance from node 0 to node 2 is 2, and the distance from node 2 to itself is 0.
The maximum of those two distances is 2. It can be proven that we cannot get a node with a smaller maximum distance than 2, so we return node 2.
*/


//15. CHEAPEST FLIGHTS WITHIN K STOPS                             {T.C = O(E*LOGV), S.C = O(E)}
//BFS(DIJKSTRA ALGO)
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // vector<vector<pair<int,int>>>adj(n); 
        //or
        unordered_map<int, vector<pair<int,int>>>adj;           //u->{v, w}

        for(auto it : flights){
            int u = it[0];
            pair<int, int>v = {it[1], it[2]};

            adj[u].push_back(v);
        }

        //BFS/DIJKSTRA'S on basis of stop without priorityqueue
        queue<pair<int, pair<int,int>>>q;
        q.push({0, {src, 0}});                      //stops, node, price/cost
        vector<int>minPrice(n, INT_MAX);            //minPrice = minDisWt
        minPrice[src] = 0;

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int stops = frontNode.first;
            int node = frontNode.second.first;
            // int cost = frontNode.second.second;
            int dW = frontNode.second.second;

            if(stops > k){
                continue;
            }
            for(auto it : adj[node]){         //node(source) not frontNode
                int u = it.first;
                int w = it.second;

                if(dW + w < minPrice[u]  && stops <= k){
                    minPrice[u] = dW + w;
                    q.push({stops + 1, {u, minPrice[u]}});
                }
            }
        }
        return minPrice[dst] == INT_MAX ? -1 : minPrice[dst];
    }
};
/*
Example 1:
Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.

Example 2:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.

Example 3:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation:
The graph is shown above.
The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.
*/


//16. MINIMUM SCORE OF A PATH BETWEEN TWO CITIES
//BFS(DIJKSTRA ALGO)
class Solution {
public:
    typedef pair<int, int>P;
    int minScore(int n, vector<vector<int>>& roads) {
        unordered_map<int, vector<pair<int, int>>>adj;
        for(auto it : roads){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});             //undirected graph
        }
        vector<int>minDisWt(n+1, INT_MAX);         //1 based indexing
        priority_queue<P, vector<P>,greater<P>>pq;
        pq.push({1, minDisWt[1]});                    //src = 1, dest = n

        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int node = topNode.first;
            int dW = topNode.second;
            for(auto it : adj[node]){                    //srcnode(it) => {destnode(u), dist(w)}
                int u = it.first;
                int w = min(dW, it.second);            
                if(w < minDisWt[u]){
                    minDisWt[u] = w;
                    pq.push({u, minDisWt[u]});
                }
            }
        }
        return minDisWt[n];
    }
};
/*
Example 1:
Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
Output: 5
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
It can be shown that no other path has less score.

Example 2:
Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
Output: 2
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4. The score of this path is min(2,2,4,7) = 2.
*/


//17. REORDER ROUTES TO MAKE ALL PATHS LEAD TO THE CITY ZERO         {T.C = O(V+E), S.C = O(V)}
//DFS
/*
*/
class Solution {
public:
    void dfs(unordered_map<int, vector<pair<int, int>>>&adj, vector<bool>&vis, int node, int &count){
        vis[node] = true;
        for(auto it : adj[node]){
            int v = it.first;
            int w = it.second;
            if(!vis[v]){                        //v = > it.first
                if(w == 1){                     //we have to reverse the edge
                    count++;
                }
                dfs(adj, vis, v, count);
            }
        }
    }
    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<pair<int,int>>>adj;
        for(auto it : connections){
            int u = it[0];
            int v = it[1];

            adj[u].push_back({v, 1});                 //w = 1, edge goes far from 0
            adj[v].push_back({u, 0});                 //w = 0, edge come to 0 (required)
        }
        vector<bool>vis(n, false);
        int count = 0;
        dfs(adj, vis, 0, count);                             //0 = initial index

        return count;
    }
};
/*
Example 1:
Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
Output: 3
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 2:
Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
Output: 2
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 3:
Input: n = 3, connections = [[1,0],[2,0]]
Output: 0
*/


//18. COUNT UNREACHABLE PAIRS OF NODES IN AN UNDIRECTED GRAPH  {formula = ans = size*(remaining-size)}
//18a. USING DFS                                               {T.C = O(V+E), S.C = O(V)}
/*
Iterate through each node, and countNode++ then  make dfs call(coun included) then in ans += countNode*(remainingnode-countnode)
{remaining node -= countNode}, finally return ans.
*/
class Solution {
public:
    void dfs(vector<int>adj[], vector<bool>&vis, long long &countNodes, int node){
        vis[node] = 1;
        countNodes++;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, countNodes, it);
            }
        }
    }
    long long countPairs(int n, vector<vector<int>>& edges) {
        
        vector<int>adj[n];
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        long long ans = 0;
        vector<bool>vis(n, 0);
        long long currRemaining = n;
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                long long countNodes = 0;
                dfs(adj, vis, countNodes, i);                       //i = initial node
                ans += countNodes*(currRemaining-countNodes);       //ans += sizeOfComponents*(currRemaining-sizeOfComponents)
                currRemaining -= countNodes;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 3, edges = [[0,1],[0,2],[1,2]]
Output: 0
Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.

Example 2:
Input: n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
Output: 14
Explanation: There are 14 pairs of nodes that are unreachable from each other:
[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]].
Therefore, we return 14.
*/


//18. COUNT UNREACHABLE PAIRS OF NODES IN AN UNDIRECTED GRAPH  {formula = ans = size*(remaining-size)}
//18b. USING DSU                                               {T.C = O(V+E), S.C = O(V)}
/*
First make components by traversing edges and union of edges then take a map {component/parent, size of component}
then iterate on map and apply formula ans = size*(remaining-size)
*/
class Solution {
public:
    vector<int>parent;
    vector<int>rank;
    int find(int i){
        if(i == parent[i]){
            return i;
        }
        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int x_parent = find(x);
        int y_parent = find(y);

        if(x_parent == y_parent){
            return;
        }
        if(rank[x_parent] > rank[y_parent]){
            parent[y_parent] = x_parent;
        }else if(rank[x_parent] < rank[y_parent]){
            parent[x_parent] = y_parent;
        }else{ //rank[x_parent] == rank[y_parent]
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }
    long long countPairs(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        rank.resize(n, 0);

        for(int i = 0 ; i < n ; i++){
            parent[i] = i;
        }

        for(auto it : edges){                   //making components in DSU
            int u = it[0];
            int v = it[1];

            Union(u, v); 
        }

        unordered_map<int, int>mp;              //{parentNode / component, size of component}
        for(int i = 0 ; i < n ; i++){  
            int parentNodes = find(i);
            mp[parentNodes]++;
        }

        long long ans = 0;
        long long currRemaining = n;
        for(auto it : mp){
            int countNodes = it.second;
            ans += countNodes*(currRemaining - countNodes);
            currRemaining -= countNodes;
        }

        return ans;
    }
};
/*
Example 1:
Input: n = 3, edges = [[0,1],[0,2],[1,2]]
Output: 0
Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.

Example 2:
Input: n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
Output: 14
Explanation: There are 14 pairs of nodes that are unreachable from each other:
[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]].
Therefore, we return 14.
*/


//19. LONGEST CYCLE IN A GRAPH                                            {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Simple use of Cycle detection in directed graph using dfs with extra of count and ans, count(n, 1{initial count of each node}) if(node != -1)
and not vis then count[v{edges[node]}] = count[node]+1 else if(dfsVis[v]== true{cycle}) maxi = max(maxi, v-u+1) backtrack(dfsVis[node] = false)
*/
class Solution {
public:
    void isCyclicDfs(vector<int>&edges, vector<bool>&vis, vector<bool>&dfsVis, vector<int>&count, int &maxi, int node){
        if(node != -1){
            vis[node] = true;
            dfsVis[node] = true;

            int v = edges[node];
            if(v != -1 && !vis[v]){
                count[v] = count[node]+1;                           //v-u+1 = length of cycle
                isCyclicDfs(edges, vis, dfsVis, count, maxi, v);
            }else if(v != -1 && dfsVis[v]){
                maxi = max(maxi, count[node]-count[v]+1);
            }
            dfsVis[node] = false;
        }
    }
    int longestCycle(vector<int>& edges) {   //not required adjacency list
        int n = edges.size();
        vector<bool>vis(n, false);
        vector<bool>dfsVis(n, false);
        vector<int>count(n, 1);                          //count of current node = 1
        int maxi = -1;
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){ 
                isCyclicDfs(edges, vis, dfsVis, count, maxi, i);
            }
        }
        return maxi;
    }
};
/*
Example 1:
Input: edges = [3,3,4,2,3]
Output: 3
Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
The length of this cycle is 3, so 3 is returned.

Example 2:
Input: edges = [2,-1,3,1]
Output: -1
Explanation: There are no cycles in this graph.
*/


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
//20. CLONE GRAPH                                                        {T.C = O(V+E), S.C = O(V)}
//DFS
/*
Check base case(!root) return null , then create a root clone = node {root->val}, take vis(Node*)vector(1000, NULL), call dfs(root, vis, node)
in dfs() mark vis[node->val] = node then iterate on root->neighbor, take new node (for copy it) push new node on node->neighbour(copy nodes nbr)
call dfs, else clone node already formed = > node->nbr(vis[it->val]), finally return node(copy).
*/

class Solution {
public:
    void dfs(Node* root, vector<Node*>&vis, Node*node){
        vis[node->val] = node;
        for(auto it : root->neighbors){
            if(!vis[it->val]){
                Node* newNode = new Node(it->val);
                node->neighbors.push_back(newNode);
                dfs(it, vis, newNode);
            }else{
                node->neighbors.push_back(vis[it->val]);                       //if clone node is already form
            }
        }
    }
    Node* cloneGraph(Node* root) {
        //base case
        if(!root){
            return NULL;
        }
        Node* node = new Node(root->val);
        vector<Node*>vis(1000, NULL);
        dfs(root, vis, node);

        return node;
    }
};
/*
Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:
Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3:
Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.
*/


//21. LARGEST COLOR VALUE IN A DIRECTED GRAPH                          {T.C = O(V+E), S.C = O(V)}
//BFS(TOPOLOGICAL SORT)
/*
Use Toplogical sort with some modification(addition) first create adj list with indegree update value , take 2D vector [row{n}][col{colors}]
now take for loop if(indegree == 0) push element in q and also initialze color matrix color(t[i][color-'a'] = 1), take count(check cycle)
and ans (finall answer) apply bfs update ans = max(ans, current color) then iterate on neigbor, and iterate on 26 char update current
color matrix(if color same add to u), then same bfs and finally return ans.
*/
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<int>inDegree(n, 0);                  //initial indegree of node is 0
        unordered_map<int, vector<int>>adj;
        for(auto it : edges){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            inDegree[v]++;
        }
        // for(int i = 0 ; i < n ; i++){              //we can use like above with adj update indegree [v]++ (incomming edges)
        //     for(auto it : adj[i]){
        //         inDegree[it]++;
        //     }
        // }
        queue<int>q;
        vector<vector<int>>t(n, vector<int>(26, 0));   //row = n, col = 26(colors)
        for(int i = 0 ; i < n ; i++){
            if(inDegree[i] == 0){
                q.push(i);
                t[i][colors[i]-'a'] = 1;           //t[i][color] {initially = 1}
            }
        }
        int countNodes = 0;                             //for cycle
        int ans = 0;
        while(!q.empty()){
            auto u = q.front();
            q.pop();
            countNodes++;                               //count increase with each bfs
            ans = max(ans, t[u][colors[u]-'a']);
            for(auto it : adj[u]){
                for(int i = 0 ; i < 26 ; i++){      //populate colors
                    t[it][i] = max(t[it][i], t[u][i] + (colors[it]-'a' ==  i));  //if same color then add to u
                }
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        if(countNodes != n){                          //have cycle(not valid topolical sort)
            return -1;
        }
        return ans;
    }
};
/*
Example 1:
Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
Output: 3
Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).

Example 2:
Input: colors = "a", edges = [[0,0]]
Output: -1
Explanation: There is a cycle from 0 to 0.
*/


//22a. SIMILAR STRING GROUPS                                          {T.C = O(V+E), S.C = O(V)}
//DFS & BFS
/*
first find the count of not similar position of strings if count is 2 or 0 then isSimilar and move to 1 component(via traversal)
else components++, finally return components count.
*/
class Solution {
public:
    bool isSimilar(string &a, string &b){
        int n = a.length();
        int count = 0;                         //count of disimilar char (2 or 0)
        for(int i = 0 ; i < n ; i++){
            if(a[i] != b[i]){
                count++;
            }
        }
        return count == 2 || count == 0;
    }
    /*
    void dfs(unordered_map<int, vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    */
    void bfs(unordered_map<int, vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = true;
        queue<int>q;
        q.push(node);
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = 1;
                    // bfs(adj, vis, it);               //similar (above iterative)
                }
            }
        }
    }
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        unordered_map<int, vector<int>>adj;
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                if(isSimilar(strs[i], strs[j])){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        int components = 0;
        vector<bool>vis(n, false);
        /*
        for(int i = 0 ; i < n ; i++){
            if(!vis[i]){
                dfs(adj, vis, i);
                components++;
            }
        }
        */
        for(int i = 0 ; i< n ; i++){
            if(!vis[i]){
                components++;
                bfs(adj, vis, i);
            }
        }
        return components;
    }
};
/*
Example 1:
Input: strs = ["tars","rats","arts","star"]
Output: 2

Example 2:
Input: strs = ["omv","ovm"]
Output: 1
*/


//22b. SIMILAR STRING GROUPS                                          {T.C = O(V+E), S.C = O(V)}
//DSU
/*
Use simple find and union function and find components , if is similar but not is sam components(not same parent)
decrease the count of compoents(initially n),finally return components.
*/
class Solution {
public:
    vector<int>parent;
    vector<int>rank;
    int find(int i){
        if(i == parent[i]){
            return i;
        }
        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int x_parent = find(x);
        int y_parent = find(y);

        if(x_parent == y_parent){
            return;
        }
        if(rank[x_parent] > rank[y_parent]){
            parent[y_parent] = x_parent;
        }else if(rank[x_parent] < rank[y_parent]){
            parent[x_parent] = y_parent;
        }else{ //rank[x_parent] == rank[y_parent]
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }
    bool isSimilar(string &a, string &b){
        int n = a.length();
        int count = 0;
        for(int i = 0; i < n ; i++){
            if(a[i] != b[i]){
                count++;
            }
        }
        return count == 2 || count == 0;
    }
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        parent.resize(n);
        rank.resize(n,1);
        for(int i = 0 ; i < n ; i++){
            parent[i] = i;
        }

        int components = n;
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                if(isSimilar(strs[i], strs[j]) && find(i) != find(j)){  //smililar but not in same compoents(not same parent)
                    Union(i, j);
                    components--;
                }
            }
        }
        return components;
    }
};
/*
Example 1:
Input: strs = ["tars","rats","arts","star"]
Output: 2

Example 2:
Input: strs = ["omv","ovm"]
Output: 1
*/


//23. CHECKING EXISTANCE OF EDGE LENGTH LIMITED PATHS                      {T.C = O(N*LOGN), S.C = O(N)}
//DSU
/*
First push i to queries (after sorting we can find correct idx)sort edgesList and queries both on the basis of 
dist/weight(last index) then check in queries if find(v) == find(v) return true else false.
*/
class Solution {
public:
    vector<int>parent;
    vector<int>rank;
    int find(int i){
        if(i == parent[i]){
            return i;
        }
        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int x_parent = find(x);
        int y_parent = find(y);

        if(x_parent == y_parent){
            return;
        }
        if(rank[x_parent] > rank[y_parent]){
            parent[y_parent] = x_parent;
        }else if(rank[x_parent] < rank[y_parent]){
            parent[x_parent] = y_parent;
        }else{ //rank[x_parent] == ran[y_parent]
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0 ; i < n ; i++){
            parent[i] = i;
        }

        int m = queries.size();
        for(int i = 0 ; i  < m ; i++){
            queries[i].push_back(i);
        }
        auto lambda = [&](auto &a, auto &b){      //increasing sort based on dis(2)
            return a[2] < b[2];
        };
        sort(edgeList.begin(), edgeList.end(), lambda);
        sort(queries.begin(), queries.end(), lambda);

        int j = 0;
        vector<bool>ans(m);
        for(auto it : queries){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            int idx = it[3];

            while(j < edgeList.size() && edgeList[j][2] < w){   //n = number of nodes (throws error)
                Union(edgeList[j][0], edgeList[j][1]);
                j++;
            }
            if(find(u) == find(v)){
                ans[idx] = true;
            }else{
                ans[idx] = false;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
Output: [false,true]
Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.

Example 2:
Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
Output: [true,false]
Explanation: The above figu
*/


//24. REMOVE MAX NUBMER OF EDGES TO KEEP GRAPH FULLY TRAVERSABLE                {T.C = O(N*LOGN), S.C = O(N)}
//DSU
/*
1. Make individual dsu for both alice and bob
2. sort(decreasing) on the basis of type
3. Edge process (edgecount, component--)
4. if in single component both(alice and bob) return edge.size()-edgecount.
*/
class DSU{
public:
    vector<int>parent;
    vector<int>rank;
    int components;

    DSU(int n){
        parent.resize(n+1);                   //graph starting from 1 not 0
        for(int i = 1 ; i < n ; i++){
            parent[i] = i;
        }
        rank.resize(n+1);
        components = n;
    }

    int find(int i){
        if(i == parent[i]){
            return i;
        }
        return parent[i] = find(parent[i]);
    }
    void Union(int x, int y){
        int x_parent = find(x);
        int y_parent = find(y);

        if(x_parent == y_parent){
            return;
        }
        if(rank[x_parent] > rank[y_parent]){
            parent[y_parent] = x_parent;
        }else if(rank[x_parent] < rank[y_parent]){
            parent[x_parent] = y_parent;
        }else{   //rank[x_parent] == rank[y_parent]
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
        components--;
    }
    bool isSingleComponent(){
        return components == 1;
    }
};
class Solution {
public:

    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        //seperate dsu for both alice and bob
        DSU alice(n);
        DSU bob(n);

        //sort descending on basis of type(0)
        auto lambda = [&](auto &a, auto &b){            //auto = vector
            return a[0] > b[0];
        };
        sort(edges.begin(), edges.end(), lambda);

        int edgeCount = 0;
        for(auto it : edges){
            int type = it[0];
            int u = it[1];
            int v = it[2];

            if(type == 3){
                bool edgeAdded = false;

                //alice
                if(alice.find(u) != alice.find(v)){
                    alice.Union(u, v);
                    edgeAdded = true;
                }
                //bob
                if(bob.find(u) != bob.find(v)){
                    bob.Union(u, v);
                    edgeAdded = true;
                }

                if(edgeAdded == true){
                    edgeCount++;
                }
            }else if(type == 2){
                //bob
                if(bob.find(u) != bob.find(v)){
                    bob.Union(u, v);
                    edgeCount++;
                }
            }else if(type == 1){
                //alice
                if(alice.find(u) != alice.find(v)){
                    alice.Union(u, v);
                    edgeCount++;
                }
            }
        }

        if(alice.isSingleComponent() && bob.isSingleComponent()){
            return edges.size()-edgeCount;
        }

        return -1;
    }
};
/*
Example 1:
Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
Output: 2
Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.

Example 2:
Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
Output: 0
Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.

Example 3:
Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
Output: -1
Explanation: In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.
*/


//25. MINIMUM NUBMER OF VERTICES TO REACH ALL NODES                           {T.C = O(N), S.C = O(N)}
//INDEGREE
/*
Simply find indegree of all nodes , check indegree of nodes is false (no incoming edge) then push in ans, and return ans.
*/
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int>inDegree(n, false);
        for(auto it : edges){
            int v = it[1];
            inDegree[v] = true;                    //increase indegree of node(to) {going edge}
        }
        vector<int>ans;
        for(int i = 0 ; i < n; i++){
            if(inDegree[i] == false){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
Output: [0,3]
Explanation: It's not possible to reach all the nodes from a single vertex. From 0 we can reach [0,1,2,5]. From 3 we can reach [3,4,2,5]. So we output [0,3].

Example 2:
Input: n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
Output: [0,2,3]
Explanation: Notice that vertices 0, 3 and 2 are not reachable from any other node, so we must include them. Also any of these vertices can reach nodes 1 and 4.
*/


//26. EVALUATE DIVISION                                      {T.C = O(V+E), S.C = O(N)}
//DFS
/*
1. Create adjlist , a/b => a->(b, 2) , b->(a, 1/2)...
2. Apply dfs (prod = 1), find a/c , src = a, dest = c.
3. Edge case if not present in adj(e, f) then return {-1.0}.
*/
class Solution {
public:
    void dfs(unordered_map<string, vector<pair<string, double>>> &adj, string src, string dst, double &ans, double prod, unordered_set<string>&vis){
        if(vis.find(src) != vis.end()){
            return;
        }
        vis.insert(src);       //mark visited
        if(src == dst){
            ans = prod;
            return;
        }
        for(auto it : adj[src]){
            string v = it.first;
            double val = it.second;
            dfs(adj, v, dst, ans, prod*val, vis);
        }
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        //similar question to graph with with weight or graph traversal
        int n = equations.size();

        //create adjacency list
        // unordered_map<int, int>mp;
        unordered_map<string, vector<pair<string, double>>>adj;
        for(int i = 0 ; i < n ; i++){
            string u = equations[i][0];       //"a"
            string v = equations[i][1];       //"b"
            double val = values[i];            //2

            adj[u].push_back({v, val});     //a/b          a->(b, 2)
            adj[v].push_back({u, 1.0/val}); //b/a          b->(a, 1/2)
        }

        vector<double>result;

        for(auto it : queries){
            string src = it[0];
            string dst = it[1];

            double ans = -1.0;
            double prod = 1.0;


            if(adj.find(src) != adj.end()){
                unordered_set<string>vis;                 //vis set created each time 
                dfs(adj, src, dst, ans, prod, vis);
            }
            result.push_back(ans);
        }
        return result;
    }
};
/*
Example 1:
Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0

Example 2:
Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]

Example 3:
Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
*/


//27. SHORTEST PATH IN BINARY MATRIX
//27a. Using BFS                                                       {T.C = O(N^2), S.C = O(N^2)}
/*
Use simle dfs and in place of vis vector use grid[0][0] = 1, then take directions vector and iterate on it and check
if it is safe then move further with new coordinates and push into the q. after then return steps.
*/
class Solution {
public:
    vector<vector<int>>directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; //8 directions
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int steps = 1;                   //count initial zero
        int n = grid.size();             //m == n

        //base case
        if(n == 0 || grid[0][0] != 0){
            return -1;
        }

        auto isSafe = [&](int x, int y){                 //check for boundary condition
            if(x >= 0 && x < n && y >= 0 && y < n){
                return true;
            }
            return false;
        };
        //BFS
        queue<pair<int, int>>q;
        grid[0][0] = 1;                          //vis[node] = 1 {same as}
        q.push({0, 0});                       //q.push(node) == q.push{coordinates}
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto frontNode = q.front();
                q.pop();
                int x = frontNode.first;
                int y = frontNode.second;

                if(x == n-1 && y == n-1){
                    return steps;            //+1 for count of zeroes
                }

                for(auto dir : directions){
                    int newX = x + dir[0];
                    int newY = y + dir[1];

                    if(isSafe(newX, newY) && grid[newX][newY] == 0){
                        q.push({newX, newY});                         //q.push(it)
                        grid[newX][newY] = 1;                            //vis[it] = 1
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
/*
Example 1:
Input: grid = [[0,1],
               [1,0]]
Output: 2

Example 2:
Input: grid = [[0,0,0],
               [1,1,0],
               [1,1,0]]
Output: 4

Example 3:
Input: grid = [[1,0,0],
               [1,1,0],
               [1,1,0]]
Output: -1
*/


//27b. Using DIJKSTRA IN 2D MATRIX                                       {T.C = O(N^2), S.C = O(N^2)}
//DIJAKSTRA
/*
In 2D matrix take minDisWt also 2D , other than same and apply dijakstra algo and iterate on all directions(8) and check
if isSafe(under boundary && w + newW < minDisWt) then update minDisWt and return minDisWt[n-1][n-1].
*/
class Solution {
public:
    typedef pair<pair<int, int>, int> P;
    vector<vector<int>>directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; //8 directions

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size(); // n == m

        // Base case
        if (n == 0 || grid[0][0] != 0) {
            return -1;
        }

        auto isSafe = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < n;
        };

        // Dijkstra
        priority_queue<P, vector<P>, greater<P>> pq; // minHeap
        vector<vector<int>> minDisWt(n, vector<int>(n, INT_MAX));
        minDisWt[0][0] = 0; // initialize
        pq.push({{0, 0}, 0});

        while (!pq.empty()) {
            auto frontNode = pq.top();
            pq.pop();
            int x = frontNode.first.first;
            int y = frontNode.first.second;
            int w = frontNode.second;

            for (auto dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                int newW = 1;
                if (isSafe(newX, newY) && grid[newX][newY] == 0 && w + newW < minDisWt[newX][newY]) {
                    pq.push({{newX, newY}, w + newW});
                    minDisWt[newX][newY] = w + newW;
                }
            }
        }

        if (minDisWt[n - 1][n - 1] == INT_MAX) {
            return -1;
        }
        return minDisWt[n - 1][n - 1] + 1; // +1 for counting zeros
    }
};
/*
Example 1:
Input: grid = [[0,1],
               [1,0]]
Output: 2

Example 2:
Input: grid = [[0,0,0],
               [1,1,0],
               [1,1,0]]
Output: 4

Example 3:
Input: grid = [[1,0,0],
               [1,1,0],
               [1,1,0]]
Output: -1
*/


//28. DETONATE THE MAXIMUM BOMBS                                       {T.C = O(N^2), S.C = O(N^2)}
//DFS
/*
1. finde the distance between the center (Eucledian distance  = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))).
2. if r1 >= dist then adj[i].push(j) {make graph undirected}
3. simply traverse graph using dfs (make vis vector for each iteration)
4. take max vis(true) and return max.
*/ 
class Solution {
public:
    typedef long long ll;
    void dfs(unordered_map<int, vector<int>>&adj, vector<bool>&vis, int &count, int node){
        vis[node] = true;
        count++;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, count, it);
            }
        }
    }
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        //create adjacency list
        unordered_map<int, vector<int>>adj;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                ll x1 = bombs[i][0];
                ll y1 = bombs[i][1];
                ll r1 = bombs[i][2];

                ll x2 = bombs[j][0];
                ll y2 = bombs[j][1];
                ll r2 = bombs[j][2];

                // ll distance = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));    //gives wrong answer
                ll distance = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
                if(ll(r1*r1) >= distance){
                    adj[i].push_back(j);
                }
            }
        }

        //now check max visited count (bomb detonate{distroy})
        int maxi = INT_MIN;
        for(int i = 0 ; i < n ; i++){
            vector<bool>vis(n, false);                      //vis is reset for each traversal node
            int count = 0;                              
            dfs(adj, vis, count, i);
            maxi = max(maxi, count);
        }
        return maxi;
    }
};
/*
Example 1:
Input: bombs = [[2,1,3],[6,1,4]]
Output: 2
Explanation:
The above figure shows the positions and ranges of the 2 bombs.
If we detonate the left bomb, the right bomb will not be affected.
But if we detonate the right bomb, both bombs will be detonated.
So the maximum bombs that can be detonated is max(1, 2) = 2.

Example 2:
Input: bombs = [[1,1,5],[10,10,5]]
Output: 1
Explanation:
Detonating either bomb will not detonate the other bomb, so the maximum number of bombs that can be detonated is 1.

Example 3:
Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
Output: 5
Explanation:
The best bomb to detonate is bomb 0 because:
- Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb 0.
- Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
- Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.
Thus all 5 bombs are detonated.
*/


//29. PATH WITH MAXIMUM PROBABIBLITY                                  {T.C = O(E*LOGV), S.C = O(E)}
//DIJKSTRA
class Solution {
public:
    typedef pair<double, int> P;
    double dijkstra(unordered_map<int, vector<pair<int,double>>>& adj, int n, int s, int e) {
        vector<double> maxDisWt(n, 0.0);
        priority_queue<P> pq;                    // max Heap
        // maxDisWt[s] = 1;
        pq.push({1.0, s});                        // curr probability (dw) = 1, s = start
        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            double dw = topNode.first;           //dw = currProb or curr wt
            int node = topNode.second;
            for (auto it : adj[node]) {
                int u = it.first;                 
                double w = it.second;              
                if (maxDisWt[u] < dw * w) {
                    maxDisWt[u] = dw * w;
                    pq.push({maxDisWt[u], u}); 
                }
            }
        }
        return maxDisWt[e];
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        unordered_map<int, vector<pair<int,double>>>adj;       //{u, v, w}
        for(int i  = 0 ; i < edges.size() ; i++){
            int u = edges[i][0];
            int v = edges[i][1];
            double w = succProb[i];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        return dijkstra(adj, n, start_node, end_node);
    }
};
/*
Example 1:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.

Example 2:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000

Example 3:
Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.
*/


//30. FIND EVENTUAL SAFE STATES                                     {T.C = O(V+E), S.C = O(V)}
//DFS
/*
1. If node is part of any cycle then it will not safe not.
2. if dfsVis[i] == false(not cylcic node) push i in ans. this will be our safe nodes
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


//31. MAXIMAL NETWORK RANK                                       {T.C = O(N^2), S.C = O(N)}
//ADJACENCY LIST AND TRAVERSAL
/*
1. create adj list using unordered_set(reduce TC).
2. take 2 nested loos i = 0, and j = i+1 (remove redundacy).
3. find iRank and jRank  then add both (rank) if both self connected reduce 1
4. finally return maxRank.
*/
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        unordered_map<int, unordered_set<int>>adj;
        for(auto it : roads){
            int u = it[0];
            int v = it[1];

            adj[u].insert(v);                           //not push_back (unordered_set)
            adj[v].insert(u);
        }
        int maxRank = 0;
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                int iRank = adj[i].size();
                int jRank = adj[j].size();

                int rank = iRank + jRank;
                if(adj[i].find(j) != adj[i].end()){
                    rank -= 1;                              //decrease 1 rank if both self connected
                }
                maxRank = max(maxRank, rank);
            }
        }
        return maxRank;
    }
};
/*
Example 1:
Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
Output: 4
Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.

Example 2:
Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
Output: 5
Explanation: There are 5 roads that are connected to cities 1 or 2.

Example 3:
Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
Output: 5
Explanation: The network rank of 2 and 5 is 5. Notice that all the cities do not have to be connected.
*/


//32. FIND CRITICAL AND PSEUDO-CRITICAL EDGES IN MINIMUM SPANNING TREE
//KRUSKAL ALGO
/*
1. Push original index also.
2. Sort based on weight
3. find mst_weight.
4. Check each edge
    skip = skipWeight > mstWeight (critical edge)
    add = addedWeight == mstWeight (pseudo critical edge)
*/
class Solution {
public:
    int N;
    class UnionFind {
        public:
            vector<int> parent;
            vector<int> rank;

            UnionFind(int n) {
                parent.resize(n);
                rank.resize(n, 0);
                for (int i = 0; i < n; i++) {
                    parent[i] = i;
                }
            }    
        
            int find (int x) {
                if (x == parent[x]) 
                    return x;

                return parent[x] = find(parent[x]);
            }

            bool Union (int x, int y) {
                int x_parent = find(x);
                int y_parent = find(y);

                if (x_parent == y_parent) 
                    return false;

                if(rank[x_parent] > rank[y_parent]) {
                    parent[y_parent] = x_parent;
                } else if(rank[x_parent] < rank[y_parent]) {
                    parent[x_parent] = y_parent;
                } else {
                    parent[x_parent] = y_parent;
                    rank[y_parent]++;
                }
                return true;
            }
    };
    
    int Kruskal(vector<vector<int>> &vec, int skip_edge, int add_edge) {

        int sum = 0;
        
        UnionFind uf(N);
        int edgesConnected = 0;
        
        if(add_edge != -1) {
            uf.Union(vec[add_edge][0], vec[add_edge][1]);
            sum += vec[add_edge][2];
            edgesConnected++;
        }
        
        //E
        
        for(int i = 0; i<vec.size(); i++) {
            
            if(i == skip_edge)
                continue;
            
            int u  = vec[i][0];
            int v  = vec[i][1];
            int wt = vec[i][2];
            //O(@)
            int parent_u = uf.find(u);
            int parent_v = uf.find(v);
            
            if(parent_u != parent_v) {
                uf.Union(u, v);
                edgesConnected++;
                sum += wt;
            }
            
        }

        if(edgesConnected != N-1)
            return INT_MAX;
        
        return sum;
    }
    
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        N = n;
        for(int i = 0; i<edges.size(); i++) {
            edges[i].push_back(i);  
        }
        
        auto lambda = [&](vector<int>& vec1, vector<int>& vec2) {
            return vec1[2] < vec2[2];
        };
        //ElogE
        sort(begin(edges), end(edges), lambda);
        
        
        int MST_WEIGHT = Kruskal(edges, -1, -1);

        vector<int> critical;
        vector<int> pseudo_critical;
        
        
        //E*E*@
        for(int i = 0; i<edges.size(); i++) {
            
            if(Kruskal(edges, i, -1) > MST_WEIGHT) { //skipping ith edge
                critical.push_back(edges[i][3]);
            }
            
            else if(Kruskal(edges, -1, i) == MST_WEIGHT) { //Force add this ith edge
                pseudo_critical.push_back(edges[i][3]);
            }
            
        }
        return {critical, pseudo_critical};
    }
};
/*
Example 1:
Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
Output: [[0,1],[2,3,4,5]]
Explanation: The figure above describes the graph.
The following figure shows all the possible MSTs:

Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.

Example 2:
Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
Output: [[],[0,1,2,3]]
Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield an MST. Therefore all 4 edges are pseudo-critical.
*/


//33. SORT ITEMS BY GROUPS RESPECTING DEPENDENCIES                                  {T.C = O(N), S.C = O(N)}
//COPIED
//TOPOLOGICAL SORT
/*
1a. Assign extra groups to group[i].
1. Make itemgraph , itemindegree
2. Make groupGraph, groupIndegree
3. Apply topsort both to get itemOrder and groupOrder
4. Iterate on itemOrder and append in order.
*/
class Solution {
public:
    vector<int> topoSort(unordered_map<int, vector<int>>& adj, vector<int>& indegree)  {
	    queue<int> que;

	    //1. Fill que, indegree with 0
	    for(int i = 0; i < adj.size(); i++) {
	        if(indegree[i] == 0) {
	            que.push(i);
	        }
	    }
	    
	    //2. Simple BFS
	    vector<int> result;
	    while(!que.empty()) {
	        int u = que.front();
	        result.push_back(u);
	        que.pop();
	        
	        for(int &v : adj[u]) {
	            indegree[v]--;
	            
	            if(indegree[v] == 0) {
	                que.push(v);
	            }
	            
	        }
	    }
	    
	    return result.size() == adj.size() ? result : vector<int>();
	}
    
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {

        //Step-1 (assign group numbers to all)
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) {
                group[i] = m++;
            }
        }
        
        //Step-2 (Make itemGraph and itemIndegree) - For Topological Sorting
        unordered_map<int, vector<int>> itemGraph;
        vector<int> itemIndegree(n, 0);
        for (int i = 0; i < n; ++i) {
            itemGraph[i] = vector<int>();
        }
        
        //Step-3 (Make groupGraph and groupIndegree) - For Topological Sorting
        unordered_map<int, vector<int>> groupGraph;
        vector<int> groupIndegree(m, 0);
        for (int i = 0; i < m; ++i) {
            groupGraph[i] = vector<int>();
        }
        
        //Step-4 (Fill itemGraph, itemIndegree, groupGraph, groupIndegree)
        
        for (int i = 0; i < n; i++) {
            
            for (int prev : beforeItems[i]) {
                
                itemGraph[prev].push_back(i);
                itemIndegree[i]++;
                
                if (group[i] != group[prev]) {
                    int prevItemGroup = group[prev];
                    int currItemGroup = group[i];
                    
                    groupGraph[prevItemGroup].push_back(currItemGroup);
                    groupIndegree[currItemGroup]++;
                }
            }
        }
        
        //Step-5 (Call TopoSort for both Graphs)
        vector<int> itemOrder  = topoSort(itemGraph, itemIndegree);
        vector<int> groupOrder = topoSort(groupGraph, groupIndegree);
        
        if (itemOrder.empty() || groupOrder.empty()) {
            return vector<int>();
        }
        
        unordered_map<int, vector<int>> groupToItemsInOrder;
        for (int item : itemOrder) {
            int itemGroup = group[item];
            groupToItemsInOrder[itemGroup].push_back(item);
        }
        
        vector<int> result;
        for (int group : groupOrder) {
            result.insert(result.end(), groupToItemsInOrder[group].begin(), groupToItemsInOrder[group].end());
        }
        
        return result;
    }
};
/*
Example 1:
Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
Output: [6,3,4,1,5,2,0,7]

Example 2:
Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
Output: []
Explanation: This is the same as example 1 except that 4 needs to be before 6 in the sorted list.
*/


//34. RECONSTRUCT ITINERARY
//TRAVERSAL (DFS OR BFS) //TLE
/*
1. Create adjacency list (unordered_map<string , vector<string>>adj)
2. Sort adj neighbour(for lexical order)
3. Call DFS(from City, vector<string>path)
*/
class Solution {
public:
    unordered_map<string, vector<string>> adj;
    vector<string> ans;
    int numTickets = 0;
    
    vector<string> findItinerary(vector<vector<string>>& tickets) {
		numTickets = tickets.size();
        
		for (auto it : tickets) {
            string u = it[0];
            string v = it[1];
            
			adj[u].push_back(v);
		}
        
        // Sort vertices in the adjacency list by lexical order
        for (auto &edges : adj) {
            sort(begin(edges.second), end(edges.second));
        }
        
        vector<string> path;
        DFS("JFK", path);
        return ans;
    }
    
    bool DFS(string fromAirport, vector<string>& path) {
        path.push_back(fromAirport);
        
        // we have used all tickets, this is a valid path return the result
        if (path.size() == numTickets+1) {
            ans = path;
            return true;
        }
        
        //You have already found the ans (first valid lexicographically path)

        
        vector<string>& nbr = adj[fromAirport];
        
        // at the current layer, try its nbr in the sorted order
        for(int i = 0; i < nbr.size(); i++) {
            
            string toAirport = nbr[i];
            
            // remove ticket(ans) from graph so that it won't be reused 
            nbr.erase(nbr.begin()+i);
            
            if(DFS(toAirport, path))
                return true;
            
            // if the current path is invalid, restore the current ticket
            nbr.insert(nbr.begin()+i, toAirport);            
        }
        
        path.pop_back();
        return false;
    }
};

//OPTIMIZED (USING MINHEAP)
class Solution {
public:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj;
    vector<string> result;
    void dfs(string u) {
        auto & edges = adj[u];
        
        while (!edges.empty())
        {
            string v = edges.top();
            edges.pop();
            dfs(v);
        }
        result.push_back(u);
    }
    
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto e : tickets)
            adj[e[0]].push(e[1]);
        
        dfs("JFK");
        reverse(result.begin(), result.end());
        return result;
    }
};
/*
Example 1:
Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]

Example 2:
Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.
*/


//35. VALIDATE BINARY TREE NODES                                    {T.C = O(N), S.C = O(N)}
//DSU (MODIFIED)
class Solution {
public:
    vector<int>parent;
    int components;

    int find(int x){
        if(parent[x] == x){
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    bool Union(int p, int c){
        if(find(c) != c){
            return false;
        }
        if(find(p) == c){
            return false;
        }
        
        parent[c] = p;
        components--;

        return true;
    }
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        components = n;                              //initially all node individual
        parent.resize(n);
        for(int i = 0 ; i < n ; i++){
            parent[i] = i;
        }

        for(int i = 0 ; i < n ; i++){
            int node = i;
            int lc = leftChild[i];
            int rc = rightChild[i];

            if(lc != -1 && Union(node, lc) == false){
                return false;
            }
            if(rc != -1 && Union(node, rc) == false){
                return false;
            }
        }

        return components == 1;                     //if single component (valid BT)
    }
};
/*
Example 1:
Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
Output: true

Example 2:
Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
Output: false

Example 3:
Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
Output: false
*/


//36. PARALLEL COURSES III                                              {T.C = O(V+E), S.C = O(V)}
//TOPOLOGICAL SORT
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        unordered_map<int,vector<int>>adj;
        for(auto it : relations){
            int u = it[0]-1;                  //for indexing 1 to 0
            int v = it[1]-1;

            adj[u].push_back(v);
        }

        vector<int>inDegree(n, 0);
        for(int i = 0 ; i < n ; i++){            //calculate indegree of all
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        queue<int>q;
        vector<int>maxTime(n, 0);                      //just add this on basic Topological sort all same
        for(int i = 0 ; i < n ; i++){            //first push indegree 0 nodes in queue
            if(inDegree[i] == 0){
                q.push(i);
                maxTime[i] = time[i];               //add
            }
        }

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                maxTime[it] = max(maxTime[it], maxTime[frontNode]+time[it]); //add
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }

        return *max_element(maxTime.begin(), maxTime.end());        //add
    }
};
/*
Example 1:
Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
Output: 8
Explanation: The figure above represents the given graph and the time required to complete each course. 
We start course 1 and course 2 simultaneously at month 0.
Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.

Example 2:
Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
Output: 12
Explanation: The figure above represents the given graph and the time required to complete each course.
You can start courses 1, 2, and 3 at month 0.
You can complete them after 1, 2, and 3 months respectively.
Course 4 can be taken only after course 3 is completed, i.e., after 3 months. It is completed after 3 + 4 = 7 months.
Course 5 can be taken only after courses 1, 2, 3, and 4 have been completed, i.e., after max(1,2,3,7) = 7 months.
Thus, the minimum time needed to complete all the courses is 7 + 5 = 12 months.
*/


//37. DESIGN GRAPH WITH SORTEST PATH CALCULATOR                         {T.C = O((V+E)*LOGV), S.C = O(V)}
//DIJAKSTRA (SIMPLE)
class Graph {
public:     
    typedef pair<int, int> P;
    unordered_map<int, vector<pair<int,int>>>adj;
    // priority_queue<int, vector<int>, greater<int>>minHeap;
    priority_queue<P, vector<P>, greater<P>>pq;
    int N;
    Graph(int n, vector<vector<int>>& edges) {
        N = n;

        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            int w = it[2];

            adj[u].push_back({v, w});
        }
    }
    
    void addEdge(vector<int> edge) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];

        adj[u].push_back({v, w});
    }
    
    int shortestPath(int node1, int node2) {
        vector<int>minDisWt(N, INT_MAX);
        minDisWt[node1] = 0;                   //initial node dis from itself is 0
        pq.push({node1, 0});                   //{source, weight}
        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int node = topNode.first;
            int dW = topNode.second;
            for(auto it : adj[node]){
                int u = it.first;
                int w = it.second;

                if(dW + w < minDisWt[u]){
                    minDisWt[u] = dW + w;
                    pq.push({u, minDisWt[u]});
                }
            }
        }
        return minDisWt[node2] == INT_MAX ? -1 : minDisWt[node2] ;                            //min distance from source(node1) to dest(node2)
    }
};
/*
Example 1:
Input
["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
Output
[null, 6, -1, null, 6]
Explanation
Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
g.shortestPath(3, 2); // return 6. The shortest path from 3 to 2 in the first diagram above is 3 -> 0 -> 1 -> 2 with a total cost of 3 + 2 + 1 = 6.
g.shortestPath(0, 3); // return -1. There is no path from 0 to 3.
g.addEdge([1, 3, 4]); // We add an edge from node 1 to node 3, and we get the second diagram above.
g.shortestPath(0, 3); // return 6. The shortest path from 0 to 3 now is 0 -> 1 -> 3 with a total cost of 2 + 4 = 6.
*/


//38. NUMBER OF POSSIBLE SETS OF CLOSING BRANCH                            {T.C = O(2^n * n^3), S.C = O(N^2)}
//FLOYD WARSHELL (SHORTEST DIS FOR EACH NODE )
class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        int ans = 0;
        //O(2^n * (n^3))
        for(int set = 0; set < (1 << n); set++) { //trying all possible subsets   //1<<n == pow(2, n)
            vector<vector<int>> grid(n, vector<int>(n, 1e9)); //updated graph
            //Update the Graph based on the selected nodes - present in set
            for(auto &it : roads) {
                int u  = it[0];
                int v  = it[1];
                int wt = it[2];

                //[[1,0,11],[1,0,16],[0,2,13]]
                if((set >> u & 1) && (set >> v & 1)) {
                    grid[u][v] = min(grid[u][v], wt);
                    grid[v][u] = min(grid[v][u], wt);
                }
            }

            for(int i = 0; i<n; i++) {
                grid[i][i] = 0;
            }

            //Floyd Warshall to find shortest distance from any node to any other node
            for(int k = 0; k < n; k++) {
                for(int i = 0; i<n; i++) {
                    for(int j = 0; j<n; j++) {

                       grid[i][j] = min(grid[i][j], grid[i][k] + grid[k][j]);

                    }
                }
            }

            //Check if all shortest paths <= maxDistance
            bool ok = true;
            for(int i = 0; i<n; i++) {
                for(int j = 0; j<n; j++) {
                    if(i == j){
                        continue;
                    } 
                    if((set >> i & 1) && (set >> j & 1)) {
                        if(grid[i][j] > maxDistance) {
                            ok = false;
                            break;
                        }
                    }
                }
            }
            if(ok == true) {
                ans++;
            }
        }
        return ans;
    }
};

//USING DIJAKSTRA
class Solution {
public:
    bool checkSubset(int mask, const vector<vector<pair<int, int>>>& graph, int n, int maxDistance) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) continue; // Skip closed branches in this subset
            for (int j = i + 1; j < n; ++j) {
                if (mask & (1 << j)) continue; // Skip closed branches in this subset
                // Check if branches i and j are reachable within maxDistance
                if (!isReachable(i, j, graph, maxDistance, mask)) {
                    return false;
                }
            }
        }
        return true;
    }

    // Function to check if two branches are reachable within maxDistance
    bool isReachable(int src, int dest, const vector<vector<pair<int, int>>>& graph, int maxDistance, int mask) {
        vector<int> minDistance(graph.size(), INT_MAX);
        minDistance[src] = 0;

        // Use a priority queue for Dijkstra's algorithm
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int distance = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (distance > minDistance[u]) continue;
            if (u == dest) return distance <= maxDistance;

            for (const auto& edge : graph[u]) {
                if (mask & (1 << edge.first)) continue; // Skip closed branches
                int v = edge.first;
                int w = edge.second;
                if (minDistance[u] + w < minDistance[v]) {
                    minDistance[v] = minDistance[u] + w;
                    pq.push({minDistance[v], v});
                }
            }
        }

        return false;
    }
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        // Step 1: Graph creation
        // Create a graph represented as an adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& road : roads) {
            // Add edges to the graph. Each edge is a pair (destination, weight)
            graph[road[0]].emplace_back(road[1], road[2]);
            graph[road[1]].emplace_back(road[0], road[2]);
        }

        int count = 0;
        // Step 2: Iterating over subsets
        // Iterate over all subsets of branches
        for (int mask = 0; mask < (1 << n); ++mask) {
            // Check if the subset satisfies the maxDistance constraint
            if (checkSubset(mask, graph, n, maxDistance)) {
                ++count;
            }
        }
        return count;
    }
};
/*
Example 1:
Input: n = 3, maxDistance = 5, roads = [[0,1,2],[1,2,10],[0,2,10]]
Output: 5
Explanation: The possible sets of closing branches are:
- The set [2], after closing, active branches are [0,1] and they are reachable to each other within distance 2.
- The set [0,1], after closing, the active branch is [2].
- The set [1,2], after closing, the active branch is [0].
- The set [0,2], after closing, the active branch is [1].
- The set [0,1,2], after closing, there are no active branches.
It can be proven, that there are only 5 possible sets of closing branches.

Example 2:
Input: n = 3, maxDistance = 5, roads = [[0,1,20],[0,1,10],[1,2,2],[0,2,2]]
Output: 7
Explanation: The possible sets of closing branches are:
- The set [], after closing, active branches are [0,1,2] and they are reachable to each other within distance 4.
- The set [0], after closing, active branches are [1,2] and they are reachable to each other within distance 2.
- The set [1], after closing, active branches are [0,2] and they are reachable to each other within distance 2.
- The set [0,1], after closing, the active branch is [2].
- The set [1,2], after closing, the active branch is [0].
- The set [0,2], after closing, the active branch is [1].
- The set [0,1,2], after closing, there are no active branches.
It can be proven, that there are only 7 possible sets of closing branches.

Example 3:
Input: n = 1, maxDistance = 10, roads = []
Output: 2
Explanation: The possible sets of closing branches are:
- The set [], after closing, the active branch is [0].
- The set [0], after closing, there are no active branches.
It can be proven, that there are only 2 possible sets of closing branches.
*/


//39. MINIMUM COST TO CONVERT STRING I                             {T.C = O(N), S.C = O(1)} {CONSTANT 26(a-z)}
//FLOYD WARSHALL
class Solution {
public:
    void floydWarshall(vector<vector<long  long>>&adjMatrix, vector<char>&original, vector<char>&changed, vector<int>&cost){
        for(int i = 0 ; i < original.size() ; i++){                               //fill matrix
            int s = original[i]-'a';
            int t = changed[i]-'a';

            adjMatrix[s][t] = min(adjMatrix[s][t], (long long)cost[i]);
        }

        //simple floyd 
        for(int k = 0 ; k < 26 ; k++){
            for(int i = 0 ; i < 26; i++){
                for(int j = 0 ; j < 26 ; j++){
                    adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
                }
            }
        }
    }
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        vector<vector<long  long>>adjMatrix(26, vector<long long>(26, INT_MAX));
        floydWarshall(adjMatrix, original, changed, cost);      //update matrix

        long long ans = 0;
        for(int i = 0 ; i < source.length() ; i++){
            if(source[i] == target[i]){
                continue;
            }
            if(adjMatrix[source[i]-'a'][target[i]-'a'] == INT_MAX){
                return -1;
            }
            ans += adjMatrix[source[i]-'a'][target[i]-'a'];
        }
        return ans;
    }
};
/*
Example 1:
Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert the string "abcd" to string "acbe":
- Change value at index 1 from 'b' to 'c' at a cost of 5.
- Change value at index 2 from 'c' to 'e' at a cost of 1.
- Change value at index 2 from 'e' to 'b' at a cost of 2.
- Change value at index 3 from 'd' to 'e' at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28.
It can be shown that this is the minimum possible cost.

Example 2:
Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
Output: 12
Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.

Example 3:
Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
Output: -1
Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.
*/

/*
Example 1:
Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert the string "abcd" to string "acbe":
- Change value at index 1 from 'b' to 'c' at a cost of 5.
- Change value at index 2 from 'c' to 'e' at a cost of 1.
- Change value at index 2 from 'e' to 'b' at a cost of 2.
- Change value at index 3 from 'd' to 'e' at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28.
It can be shown that this is the minimum possible cost.

Example 2:
Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
Output: 12
Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.

Example 3:
Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
Output: -1
Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.
*/


//40. COUNT THE NUMBER OF HOUSES AT A CERTAIN DISTANCE I              {T.C = O(N^3), S.C = O(N^2)}
//FLOYD WARSHELL
class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        vector<int>ans(n);

        vector<vector<int>>miniDisMat(n+1, vector<int>(n+1, 1e9));
        //initialize the grid
        for(int i = 1 ; i < n ; i++){
            int j = i+1;
            miniDisMat[i][i] = 0;                                  //own node distance is 0
            miniDisMat[j][j] = 0;
            miniDisMat[i][j] = 1;                                  //one node to another node distance is 1
            miniDisMat[j][i] = 1; 
        }
        if(x != y){                                                //x == y case handled above(miniDisMat[i][i] = 0)
            miniDisMat[x][y] = 1;
            miniDisMat[y][x] = 1;
        }
        
        //floyd warshell algo
        for(int k = 1; k <= n ; k++){
            for(int i = 1; i <= n ; i++){
                for(int j = 1 ; j <= n ; j++){
                    miniDisMat[i][j] = min(miniDisMat[i][j], miniDisMat[i][k] + miniDisMat[k][j]);
                }
            }
        }

        //count pairs at each node
        for(int i = 1 ; i <= n; i++){
            for(int j = 1; j <= n ; j++){
                if(i != j){
                    int val = miniDisMat[i][j];
                    ans[val-1]++;                          //ans index starts from 0 not 1
                }
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 3, x = 1, y = 3
Output: [6,0,0]
Explanation: Let's look at each pair of houses:
- For the pair (1, 2), we can go from house 1 to house 2 directly.
- For the pair (2, 1), we can go from house 2 to house 1 directly.
- For the pair (1, 3), we can go from house 1 to house 3 directly.
- For the pair (3, 1), we can go from house 3 to house 1 directly.
- For the pair (2, 3), we can go from house 2 to house 3 directly.
- For the pair (3, 2), we can go from house 3 to house 2 directly.

Example 2:
Input: n = 5, x = 2, y = 4
Output: [10,8,2,0,0]
Explanation: For each distance k the pairs are:
- For k == 1, the pairs are (1, 2), (2, 1), (2, 3), (3, 2), (2, 4), (4, 2), (3, 4), (4, 3), (4, 5), and (5, 4).
- For k == 2, the pairs are (1, 3), (3, 1), (1, 4), (4, 1), (2, 5), (5, 2), (3, 5), and (5, 3).
- For k == 3, the pairs are (1, 5), and (5, 1).
- For k == 4 and k == 5, there are no pairs.

Example 3:
Input: n = 4, x = 1, y = 1
Output: [6,4,2,0]
Explanation: For each distance k the pairs are:
- For k == 1, the pairs are (1, 2), (2, 1), (2, 3), (3, 2), (3, 4), and (4, 3).
- For k == 2, the pairs are (1, 3), (3, 1), (2, 4), and (4, 2).
- For k == 3, the pairs are (1, 4), and (4, 1).
- For k == 4, there are no pairs.
*/


//41. FIND ALL PEOPLE WITH SECRET                                   {T.C = O(V+E*LOGV), S.C = O(V+E)}
//DIJKSTRA
class Solution {
public:
    typedef pair<int,int>P;
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        unordered_map<int, vector<pair<int, int>>>adj;
        for(auto it : meetings){
            int u = it[0];
            int v = it[1];
            int w = it[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        // vector<int>minDisWt(n, INT_MAX);
        vector<bool>vis(n, false);
        priority_queue<P, vector<P>, greater<P>>pq;      //{time, person},   //minimum time reach on top of pq
        pq.push({0, 0});                         //2 person
        pq.push({0, firstPerson});

        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();
            int dW = topNode.first;             //dw = > time
            int node = topNode.second;            //node => person

            if(!vis[node]){
                vis[node] = true;
                for(auto it : adj[node]){         //{node(person), wt(time)}
                    if(!vis[it.first] && it.second >= dW){
                        pq.push({it.second, it.first});
                    }
                }
            }
        }
        vector<int>ans;
        for(int i = 0 ; i < n ; i++){
            if(vis[i]== true){
                ans.push_back(i);
            }
        }

        return ans;
    }
};
/*
Example 1:
Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
Output: [0,1,2,3,5]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 5, person 1 shares the secret with person 2.
At time 8, person 2 shares the secret with person 3.
At time 10, person 1 shares the secret with person 5.​​​​
Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.

Example 2:
Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
Output: [0,1,3]
Explanation:
At time 0, person 0 shares the secret with person 3.
At time 2, neither person 1 nor person 2 know the secret.
At time 3, person 3 shares the secret with person 0 and person 1.
Thus, people 0, 1, and 3 know the secret after all the meetings.

Example 3:
Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
Output: [0,1,2,3,4]
Explanation:
At time 0, person 0 shares the secret with person 1.
At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
Note that person 2 can share the secret at the same time as receiving it.
At time 2, person 3 shares the secret with person 4.
Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.
*/


//42. REMOVE METHODS FROM PROJECT                                      {T.C = O(V+E), S.C = O(V+E)}
//DFS
class Solution {
public:
    void dfs(unordered_map<int, vector<int>>&adj, vector<bool>&vis, int node){
        vis[node] = true;
        for(auto it : adj[node]){
            if(!vis[it]) dfs(adj, vis, it);
        }
    }
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        unordered_map<int,vector<int>>adj;
        for(auto it : invocations){
            adj[it[0]].push_back(it[1]);
        }

        vector<bool>vis(n, false);
        dfs(adj, vis, k);                          //k = src node

        bool suspicious = true;
        for(int i = 0 ;  i < n; i++){
            if(!vis[i]){
                for(auto it : adj[i]){             //outside node invoke within grp, mark false (we cant remove)
                    if(vis[it]) suspicious = false;
                }
            }
        }

        vector<int>ans;
        if(suspicious){
            for(int i = 0 ; i < n; i++){
                if(!vis[i]) ans.push_back(i);
            }
        }else{   //no suspious push all
            for(int i = 0 ; i < n ;i++){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
Output: [0,1,2,3]
Explanation:
Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.

Example 2:
Input: n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
Output: [3,4]
Explanation:
Methods 0, 1, and 2 are suspicious and they are not directly invoked by any other method. We can remove them.

Example 3:
Input: n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
Output: []
Explanation:
All methods are suspicious. We can remove them.
*/


//43. FIND MINIMUM TIME TO REACH LAST ROOM I                      {T.C = O(NM*LOGNM), S.C = O(NM)}
//DIJKSTRA
class Solution {
public:
    typedef pair<int, pair<int, int>> P;                  // time, {row, col}
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    bool isValid(int i, int j, int n, int m) {
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size(), m = moveTime[0].size();
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, {0, 0}});                          // initial time = 0, start from (0, 0)

        vector<vector<int>> minDis(n, vector<int>(m, INT_MAX));
        minDis[0][0] = 0;                              // time to reach start is 0

        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            int t = topNode.first;
            int r = topNode.second.first;
            int c = topNode.second.second;

            if (r == n - 1 && c == m - 1){              // reached destination
                return t;
            }

            for (auto it : directions) {
                int newR = r + it[0];
                int newC = c + it[1];

                if (isValid(newR, newC, n, m)) {
                    int newTime = 1 + max(t, moveTime[newR][newC]);      //1(path) + max(curr, next)
                    
                    if (newTime < minDis[newR][newC]) {
                        minDis[newR][newC] = newTime;
                        pq.push({newTime, {newR, newC}});
                    }
                }
            }
        }
        
        return -1; // If destination is unreachable
    }
};
/*
Example 1:
Input: moveTime = [[0,4],[4,4]]
Output: 6
Explanation:
The minimum time required is 6 seconds.
At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in one second.

Example 2:
Input: moveTime = [[0,0,0],[0,0,0]]
Output: 3
Explanation:
The minimum time required is 3 seconds.
At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in one second.
At time t == 2, move from room (1, 1) to room (1, 2) in one second.

Example 3:
Input: moveTime = [[0,1],[1,2]]
Output: 3
*/


//44. FIND MINIMUM TIME TO REACH LAST ROOM II                      {T.C = O(NM*LOGNM), S.C = O(NM)}
//DIJKSTRA
class Solution {
const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        //Djikstra
        int n = moveTime.size();
        int m = moveTime[0].size();
        //distance from 0,0 to i,j
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;
        
        //Priority Queue to maintain closest room we have not visited yet
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.push({0, 0, 0});
        while (!pq.empty()) {
            auto [currentDist, row, col] = pq.top();
            pq.pop();
            
            if (row == n - 1 && col == m - 1) {
                return currentDist;  
            }
            
            for (const auto& [dx, dy] : directions) {
                int newRow = row + dx;
                int newCol = col + dy;
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m) {
                    int travelTime = 2-(newRow+newCol)%2; // =(newRow+newCol)%2? 1:2;
                    
                    int newDist = max(currentDist, moveTime[newRow][newCol])+travelTime;
                    
                    if (newDist < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newDist;
                        pq.push({newDist, newRow, newCol});
                    }
                }
            }
        }    
        return dist[n-1][m-1];
    }
};
/*
Example 1:
Input: moveTime = [[0,4],[4,4]]
Output: 7
Explanation:
The minimum time required is 7 seconds.
At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.

Example 2:
Input: moveTime = [[0,0,0,0],[0,0,0,0]]
Output: 6
Explanation:
The minimum time required is 6 seconds.
At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in two seconds.
At time t == 3, move from room (1, 1) to room (1, 2) in one second.
At time t == 4, move from room (1, 2) to room (1, 3) in two seconds.

Example 3:
Input: moveTime = [[0,1],[1,2]]
Output: 4
*/


//45. MINIMUM COST OF A PATH WITH SPECIAL ROADS                    {T.C = O(N^2*LOGN), S.C = O(N^2)}
//DIJKSTRA
class Solution {
public:
    typedef pair<int,pair<int,int>>P;
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        int n = specialRoads.size(), m = specialRoads[0].size();
        priority_queue<P, vector<P>, greater<P>>pq;
        pq.push({0, {start[0], start[1]}});             //cost, r, c

        map<pair<int, int>, int>minDis;                //store min cost to reach each pos
        minDis[{start[0], start[1]}] = 0;                             //initial cost

        while(!pq.empty()){
            auto topNode = pq.top();
            pq.pop();

            int cost = topNode.first;
            int r    = topNode.second.first;
            int c    = topNode.second.second;

            if(r == target[0] && c == target[1]) return cost;   //target reached

            //regular move without special road
            int directCost = cost + abs(target[0]-r) + abs(target[1]-c);
            if(!minDis.count({target[0], target[1]}) || directCost < minDis[{target[0], target[1]}]){
                minDis[{target[0], target[1]}] = directCost;
                pq.push({directCost, {target[0], target[1]}});
            }

            //check move via special path
            for(auto it : specialRoads){
                int x1 = it[0], y1 = it[1];
                int x2 = it[2], y2 = it[3];
                int roadCost = it[4];

                //move from (x, y) to (x1, y1) then take special road to (x2, y2)
                int specialCost = cost + abs(x1 - r) + abs(y1 - c) + roadCost;
                if(!minDis.count({x2, y2}) || specialCost < minDis[{x2, y2}]){
                    minDis[{x2, y2}] = specialCost;
                    pq.push({specialCost, {x2, y2}});
                }
            }
        }
        return -1;                                  //no path found
    }
};
/*
Example 1:
Input: start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]]
Output: 5
Explanation:
(1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
(1,2) to (3,3). Use specialRoads[0] with the cost 2.
(3,3) to (3,4) with a cost of |3 - 3| + |4 - 3| = 1.
(3,4) to (4,5). Use specialRoads[1] with the cost 1.
So the total cost is 1 + 2 + 1 + 1 = 5.

Example 2:
Input: start = [3,2], target = [5,7], specialRoads = [[5,7,3,2,1],[3,2,3,4,4],[3,3,5,5,5],[3,4,5,6,6]]
Output: 7
Explanation:
It is optimal not to use any special edges and go directly from the starting to the ending position with a cost |5 - 3| + |7 - 2| = 7.
Note that the specialRoads[0] is directed from (5,7) to (3,2).
*/


//46. NUMBER OF WAYS TO ARRIVE AT DESTINATION                  {T.C = O((E+V)LOGV), S.C = O(E+V)}
//DIJKSTRA (ON GRAPH)
class Solution {
public:
    typedef long long ll;
    typedef pair<ll, int> P;
    int mod = 1e9 + 7;

    int countPaths(int n, vector<vector<int>>& roads) {
        unordered_map<int, vector<P>> adj;
        
        for (auto it : roads) {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]}); 
        }
        
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, 0});                                   // {distance, node}
        
        vector<ll> minDis(n, LLONG_MAX);
        vector<int> count(n, 0);
        
        minDis[0] = 0;
        count[0] = 1;                       // Initial count is 1 for the starting node
        
        while (!pq.empty()) {
            auto topNode = pq.top();
            pq.pop();
            
            ll dis = topNode.first;
            int u = topNode.second;

            if(dis > minDis[u]) continue;                   //skip if dis is not minimum

            for (auto it : adj[u]) {
                int v = it.first; // Neighbor node
                ll d = it.second; // Distance to neighbor
                
                if (minDis[u] + d < minDis[v]) {
                    minDis[v] = minDis[u] + d;
                    pq.push({minDis[v], v});
                    count[v] = count[u];                      //we found new path (count node of this path only)
                } else if (minDis[v] == minDis[u] + d) {
                    count[v] = (count[v] + count[u]) % mod;   //same nodes count so count++
                }
            }
        }
        
        return count[n - 1];
    }
};
/*
Example 1:
Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
Output: 4
Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
The four ways to get there in 7 minutes are:
- 0 ➝ 6
- 0 ➝ 4 ➝ 6
- 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
- 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6

Example 2:
Input: n = 2, roads = [[1,0,10]]
Output: 1
Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.
*/


//47. FIND A SAFE WALK THROUGH A GRID                               {T.C = O(N*M), S.C = O(N*M)}
//BFS ON GRID
class Solution {
public:
    typedef pair<int, pair<int,int>>P;
    vector<vector<int>>directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size(), m = grid[0].size();

        queue<P>q;
        q.push({health - grid[0][0], {0, 0}});                            //remaining health, row , col

        vector<vector<int>>maxHel(n, vector<int>(m, 0));
        maxHel[0][0] = health - grid[0][0];

        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            int h = frontNode.first;
            int r = frontNode.second.first;
            int c = frontNode.second.second;

            if(r == n-1 && c == m-1 && h > 0) return true;

            for(auto it : directions){
                int newR = r + it[0];
                int newC = c + it[1];

                if(isValid(newR, newC, n, m)){
                    int newHealth = h - grid[newR][newC];

                    if(newHealth > 0 && newHealth > maxHel[newR][newC]){
                        maxHel[newR][newC] = newHealth;
                        q.push({newHealth, {newR, newC}});
                    }
                }
            }
        }
        return false;  
    }
};
/*
Example 1:
Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.

Example 2:
Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3
Output: false
Explanation:
A minimum of 4 health points is needed to reach the final cell safely.

Example 3:
Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.
Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.*/


//48. NUMBER OF RESTRICTED PATHS FROM FIRST TO LAST NODE          {T.C = O((V+E)LOG(V+E)), S.C = O(V+E)}
//DIJKSTRA + DP        (ON GRAPH)
class Solution {
public:
    int mod = 1e9 + 7;
    typedef pair<int, int> P;

    vector<int> dijkstra(const vector<vector<P>>& adj, int src, int n) {
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, src});
        vector<int> minDis(n + 1, INT_MAX);
        minDis[src] = 0;

        while (!pq.empty()) {
            auto [dis, u] = pq.top();
            pq.pop();
            if (dis > minDis[u]) continue;  // Skip if this is an outdated distance
            
            for (auto [v, d] : adj[u]) {
                if (minDis[u] + d < minDis[v]) {
                    minDis[v] = minDis[u] + d;
                    pq.push({minDis[v], v});
                }
            }
        }
        return minDis;
    }

    int dfs(const vector<vector<P>>& adj, const vector<int>& minDisFromN, vector<int>& dp, int node) {
        if (node == 1) return 1;
        if (dp[node] != -1) return dp[node];

        int ways = 0;
        for (auto [v, d] : adj[node]) {
            if (minDisFromN[node] < minDisFromN[v]) {
                ways = (ways + dfs(adj, minDisFromN, dp, v)) % mod;
            }
        }
        dp[node] = ways;
        return dp[node];
    }

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vector<vector<P>> adj(n + 1);                   //unordered_map gives MLE
        for (auto& edge : edges) {
            adj[edge[0]].emplace_back(edge[1], edge[2]);
            adj[edge[1]].emplace_back(edge[0], edge[2]);
        }

        vector<int> minDisFromN = dijkstra(adj, n, n);
        vector<int> dp(n + 1, -1);
        return dfs(adj, minDisFromN, dp, n);
    }
};
/*
Example 1:
Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
Output: 3
Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
1) 1 --> 2 --> 5
2) 1 --> 2 --> 3 --> 5
3) 1 --> 3 --> 5

Example 2:
Input: n = 7, edges = [[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]]
Output: 1
Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The only restricted path is 1 --> 3 --> 7.
*/
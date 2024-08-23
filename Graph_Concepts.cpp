#include<bits/stdc++.h>
using namespace std;


/*------------------------------------------------------- GRAPHS GENERAL ------------------------------------------------*/
//GRAPH
/*
//MINIMUM DISTANCE FINDING ALGORITHM
1. DIJKSTRA'S ALGO                  {not work for -ve Undirected weighted graph}
2. BELLMAN FORD ALGO                 {work for -ve weighted graph}
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

BELLMAN FORD
APPLICABLE FOR NEGATIVE WEIGHT CYCLE
WORK ONLY FOR DIRECTED GRAPH SO FOR UNDIRECTED GRAPH FIRST WE HAVE TO CONVERT IT INTO DIRECTED(make edges both side)

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
1. Take a vector and store {u, v, w}
2. sort the vector on the basis of its weight.
3. then take sum, and iterate on vec
4. if the parent of u and v not same then take Union and sum+= w
5. finally return sum(minsum spanning tree)

//TOPOLOGICAL SORT                                                  {T.C = O(V+E), S.C = O(V)}
In DFS (using Stack)
1. Use Simple dfs and take stack for (topsort order), 
2. call dfs and push parent node atlast, 
3. finally pop elment from stack and push into ans and return it.

In BFS (indegree {kahn's algo})
1. Take indegree vector which stores indegree of each node , 
2. put indegree = 0 value in queue then , do simple bfs and reduce indegree , 
3. if indegree == 0 push node in queue.


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
/*---------------------------------------------------------------------------------------------------------------------*/


//01. DFS OF GRAPH                                              {T.C = O(N+M / V+E), S.C = O(N+M / V+E)}
/*
We required 2 DS (ans, vis(bool)) and also initialize nodeindex = 0,  mark vis[node] = 1 and push node in ans,  now traverse adj[node],
if (!vis[it]) then push it and mark vis[it]=1 and make recursive call to DFS.
*/
class Solution {
  public:
    void DFS(vector<int>adj[], vector<int>&ans, vector<bool>&vis, int node){
        vis[node] = 1;
        ans.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]){
                DFS(adj, ans, vis, it);
            }
        }
    }
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int>ans;
        vector<bool>vis(V, 0);
        DFS(adj, ans, vis, 0);                       //0 = nodeindex
        return ans;

        /*
        //handle disconnected components
        for(int i = 0 ; i < V ; i++){
            dfs(0, adj, ans, vis);                                  //0 = starting index or node
        }
        */
    }
};
/*
Example 1:
Input: V = 5 , adj = [[2,3,1] , [0], [0,4], [0], [2]]
Output: 0 2 4 3 1
Explanation: 
0 is connected to 2, 3, 1.
1 is connected to 0.
2 is connected to 0 and 4.
3 is connected to 0.
4 is connected to 2.
so starting from 0, it will go to 2 then 4,
and then 3 and 1.
Thus dfs will be 0 2 4 3 1.

Example 2:
Input: V = 4, adj = [[1,3], [2,0], [1], [0]]
Output: 0 1 2 3
Explanation:
0 is connected to 1 , 3.
1 is connected to 0, 2. 
2 is connected to 1.
3 is connected to 0. 
so starting from 0, it will go to 1 then 2
then back to 0 then 0 to 3
thus dfs will be 0 1 2 3. 
*/


//02. BFS OF GRAPH                                 {T.C = O(N+M/ V+E), S.C = O(N+M / V+E)}   //N = nodes, E = edges
/*
We required 3 DS (ans, vis(bool), queue) and also initialize nodeindex = 0, push node in queue and mark vis[node] = 1 and push node in ans
now traverse queue, take out frontNode and push in ans, after that traverse adj[frontNode] , if (!vis[it]) then push it and mark vis[it]=1.
*/
class Solution {
  public:
    void BFS(vector<int>adj[], vector<int>&ans, vector<bool>&vis, int node){
        vis[node] = 1;
        queue<int>q;
        q.push(node);
        while(!q.empty()){
            auto frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = 1;
                }
            }
        }
    }
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        vector<int>ans;
        vector<bool>vis(V, 0);
        BFS(adj, ans, vis, 0);                        //node index = 0
        return ans;
    }
};
/*
Example 1:
Input:
V = 5, E = 4
adj = {{1,2,3},{},{4},{},{}}
Output: 
0 1 2 3 4
Explanation: 
0 is connected to 1 , 2 , 3.
2 is connected to 4.
so starting from 0, it will go to 1 then 2
then 3. After this 2 to 4, thus bfs will be
0 1 2 3 4.

Example 2:
Input:
V = 3, E = 2
adj = {{1,2},{},{}}
Output: 
0 1 2
Explanation:
0 is connected to 1 , 2.
so starting from 0, it will go to 1 then 2,
thus bfs will be 0 1 2. 
*/


//03. DETECT CYCLE IN UNDIRECTED GRAPH
//03a. USING DFS                                                                      {T.C = O(V+E), S.C = O(V)}
/*
Firstly the graph can be disconnected so we have to use a loop for disconnected graph, the call dfs function , in which 
use simple dfs and check for if !vis[it] and isCyclic return true, else outer check if vis but not parent then also true
else return false(cycle is not present).
*/
class Solution {
  public:
    // using dfs
    bool isCyclicDFS(vector<int>adj[], vector<bool>&vis, int node , int parent){
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                if (isCyclicDFS(adj, vis, it, node)) {
                    return true;
                }
            }else if (it != parent) {           //vis is true but not parent then cycle present
                return true;
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V, 0);
        for(int i = 0 ; i < V ; i++){                        //for disconnected components
            if(!vis[i] && isCyclicDFS(adj, vis, i, -1)){       //i = nodeIndex, -1 = parent
                return true;
            }
        }
        return false;
    }
};
/*
Example 1:
Input:  
V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 
Output: 1
Explanation: 
1->2->3->4->1 is a cycle.

Example 2:
Input: 
V = 4, E = 2
adj = {{}, {2}, {1, 3}, {2}}
Output: 0
Explanation: 
No cycle in the graph.
*/


//03b. USING BFS                                                                      {T.C = O(V+E), S.C = O(V)}
/*
Firstly the graph can be disconnected so we have to use a loop for disconnected graph, the call bfs function , in which 
use simple bfs(queue<int, int>q {node, parent}) and check for if !vis[it{frontnode.first}] push {it, currNode} and mark vis[it] = 1
else check if vis but not parent then also true else return false(cycle is not present).
*/
class Solution {
  public:
    //using bfs
    bool isCyclicBFS(vector<int>adj[], vector<bool>&vis, int node){
        vis[node] = 1;
        queue<pair<int, int>>q;                   //{node, parent}
        q.push({node, -1});
        while(!q.empty()){
            auto frontNode = q.front();
            int currNode = frontNode.first;
            int parent = frontNode.second;
            q.pop();
            for(auto it : adj[frontNode.first]){   //node
                if(!vis[it]){
                    q.push({it, currNode});  //node, current node becomes parent
                    vis[it] = 1;
                }else if(it != parent){
                    return true;
                }
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V, 0);
        for(int i = 0 ; i < V ; i++){             //for disconnected components
            if(!vis[i] && isCyclicBFS(adj, vis, i)){            //i = nodeIndex, //parent not defined it will define via queue
                return true;
            }
        }
        return false;
    }
};
/*
Example 1:
Input:  
V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 
Output: 1
Explanation: 
1->2->3->4->1 is a cycle.

Example 2:
Input: 
V = 4, E = 2
adj = {{}, {2}, {1, 3}, {2}}
Output: 0
Explanation: 
No cycle in the graph.
*/


//04. DETECT CYCLE IN DIRECTED GRAPH                                            {T.C = O(V+E), S.C = O(V)}
//04a. USING DFS
/*
Required vis & dfsVis vector Firstly the graph can be disconnected so we have to use a loop for disconnected graph, 
the call dfs function , in which use simple dfs and check for if !vis[it] and isCyclic return true, else outer check 
if dfsVis[it] return true & outer for loop mark dfsVis[node] = false for next iteration and return false(cycle is not present).
*/
class Solution {
  public:
    //using DFS
    bool isCyclicDFS(vector<int>adj[], vector<bool>&vis, vector<bool>&dfsVis, int node){
        vis[node] = true;
        dfsVis[node] = true;
        
        for(auto it : adj[node]){
            if(!vis[it]){
                if(isCyclicDFS(adj, vis, dfsVis, it)){
                    return true;
                }
            }else if(dfsVis[it]){                     //for undirected(it != parent(-1))
                return true;
            }
        }
        dfsVis[node] = false;                                //for next traversal reset it
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        vector<bool>vis(V, 0);
        vector<bool>dfsVis(V, 0);
        
        //for disconnected components
        for(int i = 0 ; i < V ; i++){
            if(!vis[i] && isCyclicDFS(adj, vis, dfsVis, i)){      //i = nodeIndex
                return true;
            }
        }
        return false;
    }
};
/*
Sample Input 1 :
1
5
6
1 2
4 1
2 4
3 4
5 2
1 3
Sample Output 1 :
true
*/


//05. TOPOLOGICAL SORT  {ONLY FOR DAG(DIRECTED ACYCLIC GRAPH)}   
//05a. USING DFS                                                                   {T.C = O(V+E), S.C = O(V)}                      
/*
Use Simple dfs and take stack for (topsort order), call dfs and push parent node atlast, finally pop elment from stack and push into
ans and return it.
*/
class Solution
{
	public:
	void dfsTopoSort(vector<int>adj[], vector<bool>&vis, stack<int>&stk, int node){
	    vis[node] = 1;
	    for(auto it : adj[node]){
	        if(!vis[it]){
	            dfsTopoSort(adj, vis, stk, it);
	        }
	    }
	    stk.push(node);                       //push parent node atlast
	}
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    //4 datastructures required = adjlist, vis, stack, ans
	    vector<int>ans;
	    vector<bool>vis(V, 0);
	    stack<int>stk;
	    
	    for(int i = 0 ; i < V ; i++){
	        if(!vis[i]){
	            dfsTopoSort(adj, vis, stk, i);                //i = initial node
	        }
	    }
	    
	    while(!stk.empty()){
	        ans.push_back(stk.top());
	        stk.pop();
	    }
	    return ans;
	}
};
/*
Example 1:
Input: Graph image
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 3, 2, 1, 0.

Example 2:
Input: Graph image
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 5, 4, 2, 1, 3, 0.
*/


//05. TOPOLOGICAL SORT  {ONLY FOR DAG(DIRECTED ACYCLIC GRAPH)}   
//05b. USING BFS(KAHN'S ALGORITHIM)                                        {T.C = O(V+E), S.C = O(V)}
/*
Take indegree vector which stores indegree of each node , put indegree = 0 value in queue then , do simple bfs and reduce
indegree , if indegree == 0 push node in queue.
*/
class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    vector<int>ans;
	    vector<int>inDegree(V, 0);
	    
	    for(int i = 0 ; i < V ; i++){                  //calculate all indegrees for each node
	        for(auto it : adj[i]){
	            inDegree[it]++;
	        }
	    }
	    
	    queue<int>q;
	    for(int i = 0 ; i < V ; i++){
	        if(inDegree[i] == 0){                       //push 0 indegree's nodes
	            q.push(i);
	        }
	    }
	    
	    //do bfs
	    while(!q.empty()){
	        int frontNode = q.front();
	        q.pop();
	        ans.push_back(frontNode);
	        for(auto it : adj[frontNode]){                 //reduce indegree of ajacent nodes after disconnection of node
	            inDegree[it]--;
	            if(inDegree[it] == 0){
	                q.push(it);
	            }
	        }
	    }
	    return ans;
	}
};
/*
Example 1:
Input: Graph image
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 3, 2, 1, 0.

Example 2:
Input: Graph image
Output:
1
Explanation:
The output 1 denotes that the order is
valid. So, if you have, implemented
your function correctly, then output
would be 1 for all test cases.
One possible Topological order for the
graph is 5, 4, 2, 1, 3, 0.
*/


//04. DETECT CYCLE IN DIRECTED GRAPH                                            {T.C = O(V+E), S.C = O(V)}
//04b. USING BFS (TOPOLOGICAL SORT)
class Solution {
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int>inDegree(V, 0);
        
        for(int i = 0 ; i < V ; i++){                       //calculate all indegree's of each node
            for(auto it : adj[i]){
                inDegree[it]++;
            }
        }
        queue<int>q;
        for(int i = 0 ; i < V ; i++){                      //push 0 indegree's nodes in queue
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        
        int count = 0;
        //do bfs
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            count++;
            for(auto it : adj[frontNode]){                    //reduce indegree of adjacent nodes after disconnection of node
                inDegree[it]--;
                if(inDegree[it] == 0){
                    q.push(it);
                }
            }
        }
        
        if(count == V){               //valid topological = not cycle
            return false;
        }
        return true;                  //invalid topological = cyclic
    }
};
/*
Sample Input 1 :
1
5
6
1 2
4 1
2 4
3 4
5 2
1 3
Sample Output 1 :
true
*/


//06. NUBER OF PROVINCES                                                     
//06a. USING DFS                                                              {T.C = O(N^2), S.C = O(N)}
/*
First create a adjancecy list with required condtions. then check for all disconnected components and increase components++ for every
iteration of single node traversal. with dfs function.
*/
class Solution {
public:
    void dfs(vector<int>adj[], vector<bool>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int>adj[n+1];
        for(int i = 0 ; i < n; i++){                         //create adjacency list(with condition)
            for(int j = 0 ; j < n ;j++){
                if(isConnected[i][j]==1){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        int components = 0;
        vector<bool>vis(n, 0);
        for(int i = 0 ; i < n ; i++){                       //for disconnected components
            if(!vis[i]){
                dfs(adj, vis, i);                           //0 = nodeIndex
                components++;
            }
        }
        return components;
    }
};
/*
Example 1:
Input: isConnected = [[1,1,0],
                      [1,1,0],
                      [0,0,1]]
Output: 2

Example 2:
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
*/


//06b. USING BFS                                                      {T.C = O(N^2), S.C = O(N)}
/*
First create a adjancecy list with required condtions. then check for all disconnected components and increase components++ for every
iteration of single node traversal. with bfs function.
*/
class Solution {
public:
    void bfs(vector<int>adj[], vector<bool>&vis, int node){
        vis[node] = 1;
        queue<int>q;
        q.push(node);
        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            for(auto it : adj[frontNode]){
                if(!vis[it]){
                    bfs(adj, vis, it);
                    /*or
                    vis[it] = 1;
                    q.push(it);
                    */
                }
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int>adj[n+1];
        for(int i = 0 ; i < n; i++){
            for(int j = 0 ; j < n ;j++){
                if(isConnected[i][j]==1){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        int components = 0;
        vector<bool>vis(n, 0);
        for(int i = 0 ; i < n ; i++){                       //for disconnected components
            if(!vis[i]){
                // dfs(adj, vis, i);                           //0 = nodeIndex
                bfs(adj, vis, i);                           //0 = nodeIndex
                components++;
            }
        }
        return components;
    }
};
/*
Example 1:
Input: isConnected = [[1,1,0],
                      [1,1,0],
                      [0,0,1]]
Output: 2

Example 2:
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
*/


//07. COURSE SCHEDULE                                           {T.C = O(V+E), S.C = O(V)}
/*
Required vis & dfsVis vector and adjlist Firstly the graph can be disconnected so we have to use a loop for disconnected graph, 
the call dfs function if cycle present return false(schedule not) else true,in which use simple dfs and check for 
if !vis[it] and isCyclic return true, else outer check if dfsVis[it] return true & outer for loop mark dfsVis[node] = false for next iteration and return false(cycle is not present).
*/
//USING DFS {vis, dfsVis}
class Solution {
public:
    bool isCyclicDfs(vector<int>adj[], vector<bool>&vis, vector<bool>&dfsVis, int node){
        vis[node] = 1;
        dfsVis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(isCyclicDfs(adj, vis, dfsVis, it)){
                    return  true;
                }
            }else if(dfsVis[it]){
                return true;
            }
        }
        dfsVis[node] = false;                          //for next iteration
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<int>adj[n+1];
        for(auto it : prerequisites){
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
        }
        vector<bool>vis(n, 0);
        vector<bool>dfsVis(n, 0);

        for(int i = 0 ; i < n ; i++){
            if(!vis[i] && isCyclicDfs(adj, vis, dfsVis, i)){        //i = initial index
                return false;                                       //cycle present so no schedule
            }        
        }
        return true;
    }
};
/*
Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
*/


//08. COURSE SCHEDULE II                                         {T.C = O(V+E), S.C = O(V)}
/*
Required vis ,dfsVis ,ans vector and adjlist, Firstly the graph can be disconnected so we have to use a loop for disconnected graph, 
the call dfs function if cycle present return empty vector{}, else return ans ,in which use simple dfs and check for 
if !vis[it] and isCyclic return true, else outer check if dfsVis[it] return true & outer for loop mark dfsVis[node] = false for next iteration 
,push node in ans and return false(cycle is not present).
*/
class Solution {
public:
    bool isCyclicDfs(vector<int>adj[], vector<bool>&vis, vector<bool>&dfsVis, vector<int>&ans, int node){
        vis[node] = 1;
        dfsVis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                if(isCyclicDfs(adj, vis, dfsVis,ans, it)){
                    return true;
                }
            }else if(dfsVis[it]){
                return true;
            }
        }
        dfsVis[node] = false;
        ans.push_back(node);
        return false;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<int>ans;
        vector<int>adj[n];
        for(auto it : prerequisites){
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);                       //DAG {directed asyclic graph}
        }
        vector<bool>vis(n, 0);
        vector<bool>dfsVis(n, 0);
        for(int i = 0 ;i < n ; i++){
            if(!vis[i] && isCyclicDfs(adj, vis, dfsVis, ans, i)){   //cyclic
                return {};
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example 3:
Input: numCourses = 1, prerequisites = []
Output: [0]
*/


//09. IS GRAPH BIPARTITE                                                   {T.C = O(V+E), S.C = O(V)}
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


//DISJOINT SET
//01. GENERAL
//PESUDOCODE (FIND & UNION)
//FIND
int find(int i , vector<int>parent){
    if(i == parent[i]){
        return i;
    }
    return find(parent[i], parent);
}

//UNION
void Union(int x, int y, vector<int>parent){
    int x_parent = find(x, parent);
    int y_parent = find(y, parent);

    if(x_parent != y_parent){
        parent[x_parent] = y_parent;
    }
}

//02. USING RANK AND PATH COMPRESSION
//FIND
int find(int i , vector<int>parent){
    if(i == parent[i]){
        return i;
    }
    return parent[i] = find(parent[i], parent);            //path compression
}

//UNION
void Union(int x, int y, vector<int>parent, vector<int>rank){
    int x_parent = find(x, parent);
    int y_parent = find(y, parent);

    if(x_parent == y_parent){          //belongs to same set
        return;
    }
    if(rank[x_parent] < rank[y_parent]){
        parent[x_parent] = y_parent;          //y (x -> y) becomes the parent
    }else if(rank[x_parent] > rank[y_parent]){
        parent[y_parent] = x_parent;
    }else { //rank[x_parent] == rank[y_parent]
        parent[x_parent] = y_parent;          //or parent[y_parent] = x_parent
        rank[y_parent]++;                     //rank of parent increases with same rank(initially)
    }
}


//10. DETECT CYCLE USING DSU                              {T.C = O(V+E), S.C = O(V)}
/*
Simply use find and union function of DSU, take a for loop from 0 to V then, traverse each node(for auto v : adj[u]),
find parent of both u and v apply condition of (u < v) for checking not revisit to node then check if parent is same
return true else union of u and v , finally if not same return false(no cycle).
*/
class Solution
{
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
            parent[y_parent] = x_parent;           //x beacomes the parent
        }else if(rank[x_parent] < rank[y_parent]){
            parent[x_parent] = y_parent;           //y becomes the parent
        }else{ //rank[x_parent] == rank[y_parent]
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }
	int detectCycle(int V, vector<int>adj[]){
	    parent.resize(V);
	    rank.resize(V);
	    
	    for(int i = 0 ; i < V ; i++){
	        parent[i] = i;
	        rank[i] = 1;
	    }
	    for(int u = 0 ; u < V ;u++){
	        for(auto v : adj[u]){
	            if(u < v){                                  //check condtion for revisit node
	                int u_parent = find(u);
	                int v_parent = find(v);
	                
	                if(u_parent == v_parent){
	                    return 1;
	                }
	                Union(u, v);
	            }
	        }
	    }
	    return 0;
	}
};
/*
Example 1:
Input: (GRAPH IMAGE)
Output: 1
Explanation: There is a cycle between 0->2->4->0

Example 2:
Input: (GRAPH IMAGE)
Output: 0
Explanation: The graph doesn't contain any cycle
*/


//11. SATISFIABILITY OF EQUALITY EQUATIONS                           {T.C = O(V), S.C = O(V)}
/*
First initialize parent and rank, and write find and union func, iterate on equations if 2nd char is '=' then take union
of 1st and last char else if 2nd char is '!' then check for parent of first and last char if it same then return false
else return true.
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
    void Union(int x , int y){
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
            rank[y_parent];
        }
    }
    bool equationsPossible(vector<string>& equations) {
        parent.resize(26);
        rank.resize(26, 1);

        for(int i = 0 ; i < 26 ; i++){         //initialize parent
            parent[i] = i;
        }

        for(auto it : equations){             //check for '=' {union}
            if(it[1] == '='){
                Union(it[0]-'a', it[3]-'a');
            }
        }

        for(auto it : equations){            //check for '!' {find parent and match if same return false}
            if(it[1] == '!'){
                int first_parent = find(it[0]-'a');
                int last_parent = find(it[3]-'a');

                if(first_parent == last_parent){
                    return false;
                }
            }
        }
        return true;
    }
};
/*
Example 1:
Input: equations = ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.

Example 2:
Input: equations = ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
*/


//12a. NUMBER OF OPERATIONS TO MAKE NETWORK CONNECTED
//USING DFS                                                     {T.C = O(V+E), S.C = O(V)}
/*
first check edges = vertex-1(proper connection) then , simply call dfs for each node if not vis count++, finally return count.
*/
class Solution {
public:
    void dfs(vector<int>adj[], vector<int>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    int makeConnected(int n, vector<vector<int>>& connections) {  //connections = edges
        vector<int>adj[n];
        int m = connections.size();             //edges
        if(m < n-1){                            //n components require n-1 edges 
            return -1;
        }
        for(int i = 0 ; i < m ; i++){
            int u = connections[i][0];
            int v = connections[i][1];

            adj[u].push_back(v);
            adj[v].push_back(u);                //undirected graph
        }

        vector<int>vis(n, 0);
        int count = 0;
        //handle all components
        for(int i = 0 ; i  < n ; i++){
            if(!vis[i]){
                count++;
                dfs(adj, vis, i);
            }
        }
        return count-1;
    }
};
/*
Example 1:
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.

Example 2:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2

Example 3:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.
*/


//12b. NUMBER OF OPERATIONS TO MAKE NETWORK CONNECTED
//USING DSU {number of components}                                            {T.C = O(V+E), S.C = O(V)}
/*
iterate on edges, if edges dont have same parent then take union of that and components--(components{n initially}), finally
return components-1 (required edges to move = components-1).
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
        }else { //rank[x_parent] == rank[y_parent]
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }
    int makeConnected(int n, vector<vector<int>>& connections) {    //connections = edges
        //base case
        if(connections.size() < n-1){               //edges = vertex-1 {graph}
            return -1;
        }
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0 ;i < n ;i++){
            parent[i] = i;
        }

        int components = n;                           //initial components = no. of nodes
        for(auto it : connections){
            if(find(it[0]) != find(it[1])){
                Union(it[0], it[1]);
                components--;
            }
        }
        return components-1;                                //required edges = components - 1
    }
};
/*
Example 1:
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.

Example 2:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2

Example 3:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.
*/


//13. COUNT UNREACHABLE PAIRS OF NODES IN AN UNDIRECTED GRAPH  {formula = ans = size*(remaining-size)}
//13a. USING DFS                                               {T.C = O(V+E), S.C = O(V)}
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


//13b. USING DSU                                               {T.C = O(V+E), S.C = O(V)}
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


//14. IMPLEMENTING DIJKSTRA ALGORITHM                                 {T.C = O((V+E)*LOGV), S.C = O(V)}
/*
Take an minheap, minDisWt vector initialize source with 0, push element in pq(heap) {s, 0} , while pq not empty
pop element, for(auto it : adj[node]{pq.top().first}) check if curr Weight/dist is smaller then push that in pq.
*/
class Solution
{
	public:
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // priority_queue<int, vector<int>>maxHeap;
        // priority_queue<int, vector<int>, greater<int>>minHeap or pq;
        priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int,int>>>pq;  
        //{node, dist or weight}
        vector<int>minDisWt(V, INT_MAX);            //miniDistance/weight initialize with infinity
        minDisWt[S] = 0;                            //minDistance of initial node is 0 always from itself
        pq.push({S, 0});
        
        while(!pq.empty()){
            // auto topNode = pq.top();
            int node = pq.top().first;               //node
            int dW = pq.top().second;                 //dist or weight
            pq.pop();
            for(auto it : adj[node]){
                int u = it[0];
                int w = it[1];
                
                if(dW + w < minDisWt[u]){              //weight + currentWeight < minWeight
                    minDisWt[u] = dW + w;
                    pq.push({u, minDisWt[u]});
                }
            }
        }
        return minDisWt;
    }
};
/*
Example 1:
Input:
V = 2
adj [] = {{{1, 9}}, {{0, 9}}}
S = 0
Output:
0 9
Explanation:
The source vertex is 0. Hence, the shortest 
distance of node 0 is 0 and the shortest 
distance from node 1 is 9.
 
Example 2:
Input:
V = 3, E = 3
adj = {{{1, 1}, {2, 6}}, {{2, 3}, {0, 1}}, {{1, 3}, {0, 6}}}
S = 2
Output:
4 3 0
Explanation:
For nodes 2 to 0, we can follow the path-
2-1-0. This has a distance of 1+3 = 4,
whereas the path 2-0 has a distance of 6. So,
the Shortest path from 2 to 0 is 4.
The shortest distance from 0 to 1 is 1 .
*/


//15. SHORTEST PATH IN WEIGHTED UNDIRECTED GRAPH                      {T.C = O((V+E)*LOGV), S.C = O(V)}
/*
Take an minheap, minDisWt vector initialize source with 0, push element in pq(heap) {s, 0} , while pq not empty
pop element, for(auto it : adj[node]{pq.top().first}) check if curr Weight/dist is smaller then push that in pq.
Take an path vector base check if distination not reached return -1, else check untill parent[node] != node, push the node
in path and update node to parent[node] and finally reverse and return path vector.
*/
class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        unordered_map<int, vector<pair<int, int>>> adj;
        for(auto &it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> minDisWt(n+1, INT_MAX);
        vector<int> parent(n+1);
        
        for(int i = 1; i<=n; i++) {                          //initialize parent vector of each node with itself
            parent[i] = i;
        }
        
        minDisWt[1] = 0;
		pq.push({1, 0});

		while(!pq.empty()) {

		    int node = pq.top().first;
		    int dW  = pq.top().second;
		    pq.pop();
		    for(auto v : adj[node]) {

    			int u = v.first;
    			int w = v.second;
    
    			if(dW+ w < minDisWt[u]) {
    			    minDisWt[u] = dW + w;
    			    pq.push({u, minDisWt[u]});
    			    parent[u] = node;
    			}
		    }
		}

        vector<int> path;
        int node = n;
        
        //base check {not reach to destination}
        if(minDisWt[node] == INT_MAX){   
            return {-1};
        }
        while(parent[node] != node) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(1);
        reverse(begin(path), end(path));
		return path;
    }
};
/*
Input:
n=5, m = 6
edges = [[1, 2,,2], [2, 5, 5], [2, 3, 4], [1, 4, 1], [4, 3, 3], [3, 5, 1]]
Output:
1 4 3 5
Explaination
Shortest path from 1 to n is by the path 1 4 3 5
*/


//16. NETWORK DELAY TIME                                           {T.C = O((V+E)*LOGV), S.C = O(V)}
/*
Simple apply dijakstra algo then take maxi(ans) and iterate on minDisWt and return maxi if ans exist else return -1.
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {  //k = soure node
        unordered_map<int , vector<pair<int, int>>>adj;
        for(auto it : times){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            adj[u].push_back({v, w});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq; //{node, dist or weight}
        vector<int>minDisWt(n+1, INT_MAX);           //n+1 nodes from 1 not 0
        minDisWt[k] = 0;                             //initialize source node
        pq.push({k , 0});
        while(!pq.empty()){
            int node = pq.top().first;
            int dW = pq.top().second;
            pq.pop();
            for(auto it : adj[node]){
                int u = it.first;
                int w = it.second;

                if(dW + w < minDisWt[u]){
                    minDisWt[u] = dW + w;
                    pq.push({u, minDisWt[u]});
                }
            }
        }

        int maxi = INT_MIN;
        for(int i = 1 ; i <= n ; i++){                   //node start from 1 not 0
            maxi = max(maxi, minDisWt[i]);
        }

        return maxi == INT_MAX ? -1 : maxi;             //INT_MAX (the node is not updated)
    }
};
/*
Example 1:
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2

Example 2:
Input: times = [[1,2,1]], n = 2, k = 1
Output: 1

Example 3:
Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
*/


//17. SHORTEST PATH IN BINARY MATRIX
//17a. Using BFS                                                       {T.C = O(N^2), S.C = O(N^2)}
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


//17. SHORTEST PATH IN BINARY MATRIX
//17b. Using DIJKSTRA IN 2D MATRIX                                                      {T.C = O(N^2), S.C = O(N^2)}
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


//18. PATH WITH MINIMUM EFFORT
// Using DIJKSTRA                                                       {T.C = O(N^2), S.C = O(N^2)}
/*
In 2D matrix take minDisWt also 2D , other than same and apply dijakstra algo and iterate on all directions(8) and check
if isSafe(under boundary) then extract newW by finding abs(h[x][y]-h[nx][ny]) and return max to newW  then update minDisWt 
and return minDisWt[n-1][n-1].
*/
class Solution {
public:
    typedef pair<pair<int, int>, int>P;                   //{{x, y}, w}
    vector<vector<int>>directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};   //4 directions
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        //base case
        if(n == 0 || m == 0 || heights[0][0] == 0){
            return -1;
        }

        auto isSafe = [&](int x, int y){                            //auto == bool
            return x >= 0 && x < n && y >= 0 && y < m ;
        };
        //DIJAKSTRA
        priority_queue<P, vector<P>, greater<P>>pq;
        vector<vector<int>>minDisWt(n, vector<int>(m, INT_MAX));
        minDisWt[0][0] = 0;                                      //own dis is 0
        pq.push({{0, 0}, 0});                                    //x = 0, y = 0, w = 0
        while(!pq.empty()){
            auto frontNode = pq.top();
            pq.pop();
            int x = frontNode.first.first;
            int y = frontNode.first.second;
            int w = frontNode.second;

            for(auto dir : directions){
                int newX = x + dir[0];
                int newY = y + dir[1];
                if(isSafe(newX, newY)){
                    int absDiff = abs(heights[newX][newY] - heights[x][y]);
                    int newW = max(absDiff, w);

                    if(newW < minDisWt[newX][newY]){
                        minDisWt[newX][newY] = newW;
                        pq.push({{newX, newY}, newW});
                    }
                } 
            }
        }
        if(minDisWt[n-1][m-1] == INT_MAX){
            return -1;
        }
        return minDisWt[n-1][m-1];
    }
};
/*
Example 1:
Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].

Example 3:
Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.
*/


//19. DISTANCE FROM THE SOURCE (BELLMAN-FORD ALGORITHM)                    {T.C = O(V*E), S.C = O(V)}
/*
Take minDisWt vector like dijkstra then initialize source node then take a for loop (0 to n-1) and in that iterate
over edges and check condition (u != INT_MAX && dis[u] + wt < dis[v]) then update dis[v] = dis[u]+wt , then after the loop
iterate once again on edges and if the above condition pass again then return -1 {negative cycle present} and finally
return minDisWt vector.
*/
class Solution {
  public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<int>minDisWt(V, 1e8);                 //INT_MAX not works
        minDisWt[S] = 0;                             //initial distance = 0
        for(int i = 0 ; i < V ; i++){                //rest (V-1) times
            for(auto it : edges){
                int u = it[0];
                int v = it[1];
                int w = it[2];
                
                if(minDisWt[u] != 1e8 && minDisWt[u]+w < minDisWt[v]){
                    minDisWt[v] = minDisWt[u] + w;
                }
            }
        }
        
        //checking extra time for negative cycle
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            if(minDisWt[u] != 1e8 && minDisWt[u]+w < minDisWt[v]){
                return {-1};
            }
        }
        
        return minDisWt;
    }
};
/*
Example 1:
Input:
E = [[0,1,9]]
S = 0
Output:
0 9
Explanation:
Shortest distance of all nodes from
source is printed.

Example 2:
Input:
E = [[0,1,5],[1,0,3],[1,2,-1],[2,0,1]]
S = 2
Output:
1 6 0
Explanation:
For nodes 2 to 0, we can follow the path-
2-0. This has a distance of 1.
For nodes 2 to 1, we cam follow the path-
2-0-1, which has a distance of 1+5 = 6,
*/


//20. FLOYD WARSHALL                                                        {T.C = O(N^3), S.C = O(1)} 
/*
It is a brute force approach for finding min distance of each node to another node , first we have to insert INT_MAX in place of -1
then take 3 loops 1st k (via node) then i and j and put matrix[i][j] = min (matrix[i][j], matrix (via node)). after that reset the matrix
INT_MAX value to -1 .
*/

class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    int n = matrix.size();
	    
	    //creating a matrix with update -1 to 1e9
	    for(int i = 0 ; i < n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == -1){
	                matrix[i][j] = 1e9;
	            }
	            if(i == j){                          //self distance
	                matrix[i][j] = 0;
	            }
	        }
	    }
	    
	    //traverse all graph via a node
	    for(int k = 0 ; k < n ; k++){
	        for(int i = 0 ; i < n ; i++){
	            for(int j = 0 ; j < n ; j++){
	                matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
	            }
	        }
	    }
	    
	    //reset the matrix 1e9 TO -1
	    for(int i = 0 ; i < n ; i++){
	        for(int j = 0 ; j < n ; j++){
	            if(matrix[i][j] == 1e9){
	                matrix[i][j] = -1;
	            }
	        }
	    }
	}
};
/*
Input: matrix = {{0,1,43},
                 {1,0,6},
                 {-1,-1,0}}
Output: {{0,1,7}
        ,{1,0,6},
         {-1,-1,0}}
Explanation: We can reach 2 from 0 as 0->1->2
and the cost will be 1+6=7 which is less than 
43.
*/


//21. MINIMUM SPANNING TREE  {PRIM'S ALGORITHM}                         {T.C = O(E*LOGV), S.C = O(V^2)}
/*
Requre, vis vector, priority queue, and parent vector(but not in this question), priority queue made only using WEIGHT(first element) then
push {currWt, currNode} then while pq not empty pop element and if !vis[node] then mark vis[node] = true and sum += wt, then iterate along
adjacency list and check then neighbour if not vis then push in queue finally return sum.
*/
class Solution
{
    typedef pair<int, int> P;
	public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        int sum = 0;
        vector<bool> visMST(V, false);
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, 0});
        
        while(!pq.empty()) {
            
            auto p = pq.top();
            pq.pop();
            
            int wt     = p.first;
            int node   = p.second;
            
            if(visMST[node] == true){
                continue;
            }
            
            visMST[node] = true; //added to mst
            sum += wt;
            
            for(auto it : adj[node]) {                 //according to question  adj {node, wt, parent}
                
                int newNode      = it[0];
                int newWt   = it[1];
                
                if(visMST[newNode] == false) {
                    pq.push({newWt, newNode});
                }
            }
        }
        return sum;
    }
};
/*
Example 1:
Input:
3 3
0 1 5
1 2 3
0 2 1
Output:
4
Explanation:
The Spanning Tree resulting in a weight
of 4 is shown above.

Example 2:
Input:
2 1
0 1 5
Output:
5
Explanation:
Only one Spanning Tree is possible
which has a weight of 5.
*/


//22. MIN COST TO CONNECT ALL POINTS                                          {T.C = O(E*LOGV), S.C = O(V^2)}
/*
Just make an adjacency list {node->{node, wt}} then paste above code or prims algo.
*/
class Solution {
public:
    typedef pair<int, int>P;
    int primsAlgo(vector<vector<P>>&adj, int V){
        int sum = 0;
        vector<bool>visMST(V, false);
        priority_queue<P, vector<P>, greater<P>>pq;
        pq.push({0, 0});                                     //{wt, node}
        while(!pq.empty()){
            auto p = pq.top();
            pq.pop();
            int wt = p.first;
            int node = p.second;

            if(visMST[node] == true){
                continue;
            }
            visMST[node] = true;
            sum += wt;

            for(auto it : adj[node]){                         //{node->{node, dis}}
                int newWt = it.second;
                int newNode = it.first;

                if(visMST[newNode] == false){
                    pq.push({newWt, newNode});
                }
            }
        }
        return sum;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<P>>adj(n);                                //{node->{node, dis}}
        for(int i = 0 ; i < n; i++){
            for(int j = i+1; j < n ; j++){                      //undirected graph (not require back traversal again and again)
                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];

                int dis = abs(x1-x2) + abs(y1-y2);
                adj[i].push_back({j, dis});
                adj[j].push_back({i, dis});
            }
        }

        return primsAlgo(adj, n);
    }
};
/*
Example 1:
Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation: 
We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.

Example 2:
Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
*/


//23. MINIMUM SPANNING TREE {KRUSKAL ALGORITHM}                    {T.C = O(E*LOGV), S.C = O(V^2)}
/*
1. Take a vector and store {u, v, w}
2. sort the vector on the basis of its weight.
3. then take sum, and iterate on vec
4. if the parent of u and v not same then take Union and sum+= w
5. finally return sum(minsum spanning tree)
*/
class Solution
{
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
	    }else{
	        parent[x_parent] = y_parent;
	        rank[y_parent]++;
	    }
	}
	int kruskal(vector<vector<int>>&vec){
	    int sum = 0;
	    
	    for(auto it : vec){
	        int u = it[0];
	        int v = it[1];
	        int w = it[2];
	        
	        int u_parent = find(u);
	        int v_parent = find(v);
	        
	        if(u_parent != v_parent){
	            Union(u, v);
	            sum += w;
	        }
	    }
	    
	    return sum;
	}
    int spanningTree(int V, vector<vector<int>> adj[]){
        parent.resize(V);
        rank.resize(V, 0);
        for(int i = 0 ; i < V ; i++){
            parent[i] = i;
        }
        
        vector<vector<int>>vec;
        for(int u = 0 ; u < V ; u++){
            for(auto it : adj[u]){
                int v = it[0];
                int w = it[1];
                
                vec.push_back({u, v, w});
            }
        }
        
        auto lambda = [&](vector<int>&a, vector<int>&b){
            return a[2] < b[2];                            //compare on basis of weight 
        };
        sort(vec.begin(), vec.end(), lambda);
        
        return kruskal(vec);
    }
};
/*
Example 1:
Input:
3 3
0 1 5
1 2 3
0 2 1
Output:
4
Explanation:
The Spanning Tree resulting in a weight
of 4 is shown above.

Example 2:
Input:
2 1
0 1 5
Output:
5
Explanation:
Only one Spanning Tree is possible
which has a weight of 5.
*/


//24. MIN COST TO CONNECT ALL POINTS                                 {T.C = O(E*LOGV), S.C = O(V^2)}
/*
push vec {i, j , dis{abs(x1-x2) + abs(y1-y2)}} , then apply kruskal algo.
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
    int kruskalAlgo(vector<vector<int>>&vec){
        int sum = 0;

        for(auto it : vec){
            int u = it[0];
            int v = it[1];
            int w = it[2];

            int u_parent = find(u);
            int v_parent = find(v);
            if(u_parent != v_parent){
                Union(u, v);
                sum += w;
            }
        }
        return sum;
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0 ;i < n ; i++){
            parent[i] = i;
        }

        vector<vector<int>>vec;                                //{node->{node, dis}}
        for(int i = 0 ; i < n; i++){
            for(int j = i+1; j < n ; j++){                      //undirected graph (not require back traversal again and again)
                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];

                int dis = abs(x1-x2) + abs(y1-y2);
                vec.push_back({i, j, dis});
            }
        }

        auto lambda = [&](vector<int>&a, vector<int>&b){
            return a[2] < b[2];                                //sort according to dis/wt
        };
        sort(vec.begin(), vec.end(), lambda);
        return kruskalAlgo(vec);
    }
};
/*
Example 1:
Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation: 
We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.

Example 2:
Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
*/


//25. STRONGLY CONNECTED COMPONENTS {KOSARAJU'S ALGORITHM}                       {T.C = O(V+E), S.C = O(V+E)}
/*
1. sort the adjacency list using topological sort
2. create a transpose graph
3. dfs call on basis of above ordering (stack ordering)
*/
class Solution
{
	public:
	void dfs(vector<vector<int>>&adj, vector<int>&vis, stack<int>&s, int node){
	    vis[node]  = 1;
	    
	    for(auto it : adj[node]){
	        if(!vis[it]){
	            dfs(adj, vis, s, it);
	        }
	    }
	    //topo sort logic
	    s.push(node);
	}
	void dfs(vector<vector<int>>&transpose, vector<int>&vis, int node){
	    vis[node] = 1;
	    
	    for(auto it : transpose[node]){
	        if(!vis[it]){
	            dfs(transpose, vis, it);
	        }
	    }
	}
    int kosaraju(int V, vector<vector<int>>& adj)
    {
        //step1 sort the adjacency list using topological sort
        vector<int>vis(V, 0);
        stack<int>s;
        for(int i = 0 ; i < V ; i++){
            if(!vis[i]){
                dfs(adj, vis, s, i);
            }
        }
        
        //step2 create a transpose graph
        vector<vector<int>>transpose(V);
        for(int i = 0 ; i < V ; i++){
            vis[i] = 0;                                    //reinitialize visited array
            for(auto it : adj[i]){
                transpose[it].push_back(i);
            }
        }
        
        //step3 dfs call on basis of above ordering (stack ordering)
        int countSCC = 0;                          //SCC = Strongly Conneted Component
        while(!s.empty()){
            int top = s.top();
            s.pop();
            if(!vis[top]){
                countSCC++;
                dfs(transpose, vis, top);
            }
        }
        return countSCC;
    }
};
/*
Example 1:
Input: GRAPH IMAGE
Output:
3
Explanation:
We can clearly see that there are 3 Strongly
Connected Components in the Graph

Example 2:
Input: GRAPH IMAGE
Output:
1
Explanation:
All of the nodes are connected to each other.
So, there's only one SCC.
*/


//26. EULER CIRCUIT AND PATH
/*
Iterate on adjacency list , check the indegree if(indegree is not equal to 2) count++ , if count == 0 return 2( eulerian circut)
else if(count == 2) return 1(2 vertexes with odd indegrees (Eulerian paht/semi Eulerian)), else return 0 (neither eulerian circuit or path).
*/
class Solution {
public:
	int isEularCircuit(int V, vector<int>adj[]){
	    int count = 0;
	    //check indegree of each vertex
	    for(int i = 0 ; i < V ; i++){
	        if(adj[i].size() != 2){             //adj[i].size = no. of edges connected to a vertex (indegree)
	            count++;
	        }
	    }
	    if(count == 0){                        //0 vertexes with odd indegrees (Eulerian circuit)
	        return 2;
	    }
	    else if(count == 2){                   //2 vertexes with odd indegrees (Eulerian paht/semi Eulerian)
	        return 1; 
	    }else{
	        return 0;
	    }
	}
};


//EXTRA CODE(IS CONNECTED COMPONENTS)
class Solution {
public:
    void dfs(vector<int>adj[], vector<bool>&vis, int node){
        vis[node] = 1;
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(adj, vis, it);
            }
        }
    }
    bool isConnected(int V, vector<int>adj[]){
        int nonZeroDegreeVertex = -1;
        for(int i = 0 ; i < V ; i++){
            if(adj[i].size() != 0){
                nonZeroDegreeVertex = i;
                break;
            }
        }
        vector<bool>vis(V, false);
        dfs(adj, vis, nonZeroDegreeVertex);
        
        //check if all nonZero degree vertex or node vis
        for(int i= 0 ; i < V ; i++){
            if(!vis[i] && adj[i].size() > 0){
                return false;
            }
        }
        return true;
    }
	int isEulerCircuit(int V, vector<int>adj[]){
	    if(!isConnected(V, adj)){
	        return 0;
	    }
	    
	    int oddDegreeCount = 0;
	    for(int i = 0 ; i < V ; i++){
	        if(adj[i].size() % 2 != 0){
	            oddDegreeCount++;
	        }
	    }
	    
	    if(oddDegreeCount > 2){
	        return 0;               //neither euler path or circuit
	    }else if(oddDegreeCount == 2){
	        return 1;              //euler path but not euler circuit
	    }else if(oddDegreeCount == 0){     //euler circuit only have even degree
	        return 2;              //euler circuit(euler path as well)
	    }
	}
};
/*
Example 1:
Input: 
Output: 2
Explanation: 
Following is an eulerian circuit in the mentioned graph
1 -> 2 -> 0 -> 1

Example 2:
Input: 
Output: 1
Explanation: 
Following is an eulerian path in the mentioned graph
1 -> 0 -> 2
*/
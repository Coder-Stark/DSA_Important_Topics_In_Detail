//DP CONCEPTS
#include<bits/stdc++.h>
using namespace std;

//01. FIBONACCI NUMBER
//RECURSION                       //K RECURSIVE CALL = T.C (K^N)=>{T.C = O(2^N), S.C = O(1)}
class Solution {
public:
    int solve(int n){
        //base case
        if(n == 0){
            return 0;
        }
        if(n == 1){
            return 1;
        }
        //or if(n <= 1) return n
        return solve(n-1) + solve(n-2);
    }
    int fib(int n) {
        return solve(n);
    }
};

//MEMOIZATION                                                       {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int solveMem(int n, vector<int>&dp){
        //base case
        if(n <= 1){
            return n;
        }
        //step3 if ans already present return it
        if(dp[n] != -1){
            return dp[n];
        }

        return dp[n] = solveMem(n-1, dp) + solveMem(n-2, dp);
    }
    int fib(int n) {
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        return solveMem(n, dp);
    }
};

//TABULATION                                                      {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int solveTab(int n, vector<int>&dp){
        //base case
        if(n <= 1){
            return 1;
        }

        dp[0] = 0;
        dp[1] = 1;

        for(int i = 2; i <= n ; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
    int fib(int n) {
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        return solveTab(n, dp);
    }
};
/*
Example 1:
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
*/


//02. CLIMBING STAIRS                                          {T.C = O(N), S.C = O(N)}
//MEMOIZATION (1D DP)
class Solution {
public:
    int solveMem(int n, vector<int>&dp){
        //base case
        if(n == 0 || n == 1){
            return 1;
        }

        //step3 if ans already present return it
        if(dp[n] != -1){
            return dp[n];
        }
        int climb1 = solveMem(n-1, dp);
        int climb2 = solveMem(n-2, dp);
        
        return dp[n] = climb1 + climb2;
    }
    int climbStairs(int n) {
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        return solveMem(n, dp);
    }
};
/*
Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/


//03. HOUSE ROBBER                                                  {T.C = O(N), S.C = O(N)}
//1D DP
class Solution {
public:
    int solveMem(vector<int>&nums, int i, vector<int>&dp){
        //base case
        if(i >= nums.size()){
            return 0;
        }

        //step3 if ans already present return it
        if(dp[i] != -1){
            return dp[i];
        }

        int incl = nums[i] + solveMem(nums, i+2, dp);          //adjacent skip
        int excl = 0 + solveMem(nums, i+1, dp);

        return dp[i] = max(incl, excl);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        //step1 create a dp vector
        vector<int>dp(n+1, -1);
        return solveMem(nums, 0, dp);                 //0 = i
    }
};
/*
Example 1:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
*/


//04. HOUSE ROBBER II                                           {T.C = O(N), S.C = O(N)}
//1D DP
//BREAK INTO TWO SUBPROBLEM (0 - N-1) & (1 - N) THEN APPLY  ABOVE CODE
class Solution {
public:
    int solveMem(vector<int>&nums, int i, int n, vector<int>&dp){
        if(i >= n){
            return 0;
        }
        if(dp[i] != -1){
            return dp[i];
        }
        int incl = nums[i] + solveMem(nums, i+2, n, dp);          //adjacent skip
        int excl = 0 + solveMem(nums, i+1, n, dp);

        return dp[i] = max(incl, excl);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        //base case
        if(n == 1){
            return nums[0];
        }
        if(n == 2){
            return max(nums[0], nums[1]);
        }

        vector<int>dp1(n+1, -1);
        vector<int>dp2(n+1, -1);

        //break into cases to make house robber 1 problem
        //case 1: take 0th index to n-2 index
        int inclZeroIdx = solveMem(nums, 0, n-1, dp1);

        //case 2: take 1st index to n-1 index
        int exclZeroIdx = solveMem(nums, 1, n, dp2);
        
        return max(inclZeroIdx, exclZeroIdx);
    }
};
/*
Example 1:
Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:
Input: nums = [1,2,3]
Output: 3
*/


//05. MAXIMUM ALTERNATING SUBSEQUENCE                            {T.C = O(N {dp[i][2]}), S.C = O(N)}
//2D DP (INCL & EXCL)
class Solution {
public:
    typedef long long ll;
    long long solveMem(vector<int>&nums, int i, bool flag, vector<vector<ll>>&dp){
        //base case
        if(i >= nums.size()){
            return 0;
        }

        if(dp[i][flag] != -1){
            return dp[i][flag];
        }

        ll excl = 0 + solveMem(nums, i+1, flag, dp);        //skip -> no sign change (+/-)
        ll val = nums[i];
        if(!flag){
            val = -val;
        }
        ll incl = val + solveMem(nums, i+1, !flag, dp);   //take -> sign change

        return dp[i][flag] = max(incl, excl);
    }
    long long maxAlternatingSum(vector<int>& nums) {
        ll n = nums.size();
        vector<vector<ll>>dp(n+1, vector<ll>(2, -1));       //2 = true/false
        return solveMem(nums, 0, true, dp);                 //0 = i, true = flag
    }
};

//USING MEMSET DP
class Solution {
public:
    typedef long long ll;
    ll dp[100001][2];              //2 = true/false
    long long solveMem(vector<int>&nums, int i, bool flag){
        //base case
        if(i >= nums.size()){
            return 0;
        }

        if(dp[i][flag] != -1){
            return dp[i][flag];
        }

        ll excl = 0 + solveMem(nums, i+1, flag);        //skip -> no sign change (+/-)
        ll val = nums[i];
        if(!flag){
            val = -val;
        }
        ll incl = val + solveMem(nums, i+1, !flag);   //take -> sign change

        return dp[i][flag] = max(incl, excl);
    }
    long long maxAlternatingSum(vector<int>& nums) {
        ll n = nums.size();
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0, true);                 //0 = i, true = flag
    }
};
/*
Example 1:
Input: nums = [4,2,5,3]
Output: 7
Explanation: It is optimal to choose the subsequence [4,2,5] with alternating sum (4 + 5) - 2 = 7.

Example 2:
Input: nums = [5,6,7,8]
Output: 8
Explanation: It is optimal to choose the subsequence [8] with alternating sum 8.

Example 3:
Input: nums = [6,2,1,2,4,5]
Output: 10
Explanation: It is optimal to choose the subsequence [6,1,5] with alternating sum (6 + 5) - 1 = 10.
*/


//06. LONGEST INCREASING SUBSEQUENCE                               {T.C = O(N^2), S.C = O(N^2)}
//2D DP (INCL & EXCL)
class Solution {
public:
    int dp[2501][2501];
    int solveMem(vector<int>&nums, int i, int p){
        //base case
        if(i >= nums.size()){
            return 0;
        }
        if( p != -1 && dp[i][p] != -1){                   //p never be -1(index)
            return dp[i][p];
        }
        int incl = 0, excl = 0;
        if(p == -1 || nums[i] > nums[p]){
            incl = 1 + solveMem(nums, i+1, i);             //i->i+1, p->i (take) {1+ for finding maxLen}
        }
        excl = 0 + solveMem(nums, i+1, p);                 //i->i+1, p->p (skip)

        if(p != -1){
            dp[i][p] = max(incl, excl);
        }
        return max(incl, excl);
    }
    int lengthOfLIS(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solveMem(nums, 0, -1);        //0 = currIdx, -1 = prevIdx
    }
};

//USING PATIENCE SORTING                                            {T.C = O(N*LOGN), S.C= O(N)}
//IT GIVES LIS(LEN ONLY) NOT CORRECT LIS
class Solution {
public:
    //using patience sorting (only for finding len not correct element position)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>len;
        for(int i = 0 ; i < n; i++){
            auto it = lower_bound(len.begin(), len.end(), nums[i]);      //it = pointer
            if(it == len.end()){                //greater(insert)
                len.push_back(nums[i]);
            }else{                              //smaller(replace curr element)
                *it = nums[i];                  //*it = gives value
            }
        }

        return len.size();
    }
};
/*
Example 1:
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:
Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:
Input: nums = [7,7,7,7,7,7,7]
Output: 1
*/


//LIS VARIANTS-------------------------------------------------------------
//07. MAXIMUM LENGTH OF PAIR CHAIN          
//2D DP (LIS)                                         {T.C = O(N*LOGN), S.C = O(N^2)}
class Solution {
public:
    int dp[1001][1001];
    int solveMem(vector<vector<int>>&pairs, int i, int p){
        //base case
        if(i >= pairs.size()){
            return 0;
        }
        if(p != -1 && dp[i][p] != -1){
            return dp[i][p];
        }
        int incl = 0, excl = 0;
        if(p == -1 || pairs[i][0] > pairs[p][1]){
            incl = 1 + solveMem(pairs, i+1, i);
        }
        excl = 0 + solveMem(pairs, i+1, p);

        if(p != -1){
            dp[i][p] = max(incl, excl);
        }
        return max(incl, excl);
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        memset(dp, -1, sizeof(dp));
        sort(pairs.begin(), pairs.end());                 //we can take any pair (sort is better)
        return solveMem(pairs, 0, -1);                     //0 = currIdx, -1 = prevIdx
    }
};

//OPTIMIZE                                                            {T.C = O(N*LOGN), S.C = O(1)}
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        auto lambda = [&](auto v1, auto v2){
            return v1[1] < v2[1];
        };
        sort(pairs.begin(), pairs.end(), lambda);
        int prev = 0;
        int len = 1;                                   //at least 1 is lenwer
        for(int i = 1 ; i < pairs.size() ; i++){
            if(pairs[prev][1] < pairs[i][0]){
                len++;
                prev = i;
            }
        }
        return len;
    }
};
/*
Example 1:
Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].

Example 2:
Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].
*/


//08. LONGEST STRING CHAIN                                        {T.C = O(N*LOGN), S.C = O(N^2)}
//2D DP (LIS)
class Solution {
public:
    int dp[1001][1001];
    bool isPred(string &curr, string &prev){
        int m = prev.length();
        int n = curr.length();
        
        if(m >= n || n-m != 1){                  //diff between string always 1(predecessor)
            return false;
        }

        //check proper subsequence
        int i = 0, j = 0;                      //starting pointer of both string
        while(i < m && j < n){
            if(prev[i] == curr[j]){
                i++;
            }
            j++;
        }

        return i == m;                         //all check (all char found)
    }
    int solveMem(vector<string>&words, int i, int p){
        //base case
        if(i >= words.size()){
            return 0;
        }
        if(p != -1 && dp[i][p] != -1){
            return dp[i][p];
        }
        int incl = 0, excl = 0;
        if(p == -1 || isPred(words[i], words[p])){       //similar word[i][0] > word[p][1]
            incl = 1 + solveMem(words, i+1, i);
        }
        excl = 0 + solveMem(words, i+1, p);

        if(p != -1){
            dp[i][p] = max(incl, excl);
        }
        return max(incl, excl);
    }
    int longestStrChain(vector<string>& words) {
        memset(dp, -1, sizeof(dp));
        auto lambda = [&](auto a, auto b){             //sort on basis of string length
            return a.length() < b.length();
        };
        sort(words.begin(), words.end(), lambda);
        return solveMem(words, 0, -1);                  //0 = currIdx, -1 = prevIdx
    }
};
/*
Example 1:
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].

Example 2:
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].

Example 3:
Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
*/


//09. BUILD ARRAY WHERE YOU CAN FIND THE MAXIMUM EXACTLY K COMPARISONS  {T.C = O(N*M*K), S.C = O(N*M*K)}
//3D DP SIMILAR TO LIS
class Solution {
public:
    int N, M, K;
    int MOD = 1e9+7;
    int t[51][51][101];                                          //n, k, m
    
    int solveMem(int idx, int searchCost, int maxSoFar) {
        if(idx == N) {
            if(searchCost == K)
                return 1;
            return 0;
        }
        
        if(t[idx][searchCost][maxSoFar] != -1) {
            return t[idx][searchCost][maxSoFar];
        }
        
        int result = 0;
        
        for(int i = 1; i <= M; i++) {
            
            if(i > maxSoFar) {
                result = (result + solveMem(idx+1, searchCost+1, i)) % MOD;
            } else {
                result = (result + solveMem(idx+1, searchCost, maxSoFar)) % MOD;
            }
            
        }
        
        return t[idx][searchCost][maxSoFar] = result % MOD;
        
    }
    
    int numOfArrays(int n, int m, int k) {
        N = n;
        M = m;
        K = k;
        memset(t, -1, sizeof(t));
        return solveMem(0, 0, 0);
    }
};
/*
Example 1:
Input: n = 2, m = 3, k = 1
Output: 6
Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]

Example 2:
Input: n = 5, m = 2, k = 3
Output: 0
Explanation: There are no possible arrays that satisfy the mentioned conditions.

Example 3:
Input: n = 9, m = 1, k = 1
Output: 1
Explanation: The only possible array is [1, 1, 1, 1, 1, 1, 1, 1, 1]
*/


//10. MAXIMUM BALANCED SUBSEQUENCE SUM
//2D DP, (LIS)                                                        {T.C = O(N^2), S.C = O(N^2)}
//GIVES TLE
class Solution {
public:
    //TLE
    // long long dp[100001][100001];             //too large it will give error
    unordered_map<string, long long>mp;
    long long solveMem(vector<int>&nums, int i, int p){
        //base case
        if(i >= nums.size()){
            return 0;
        }

        //memoization
        string key = to_string(p) + "_" + to_string(i);
        if(mp.find(key) != mp.end()){
            return mp[key];
        }

        /*
        if(p != -1 && dp[i][p] != -1){
            return dp[i][p];
        }
        */

        long long incl =  INT_MIN, excl = INT_MIN;
        if(p == -1 || nums[i]-nums[p] >= i-p){                           //nums[i] > nums[p]
            incl = nums[i] + solveMem(nums, i+1, i);                     //finding(nums[i]+) sum not maxLen(1+)
        }
        excl = 0 + solveMem(nums, i+1, p);

        /*
        if(p != -1){
            dp[i][p] = max<long long>(incl, excl);
        }
        */
        return mp[key] = max(incl, excl);
    }
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        // memset(dp, -1, sizeof(dp));
        //base case
        int maxElement = *max_element(nums.begin(),nums.end());
        if(maxElement <= 0){                              //-ve sum (decrease sum better to max element)
            return maxElement;
        }
        return solveMem(nums, 0, -1);                     //0 = currIdx, -1 = prevIdx
    }
};
/*
Example 1:
Input: nums = [3,3,5,6]
Output: 14
Explanation: In this example, the subsequence [3,5,6] consisting of indices 0, 2, and 3 can be selected.
nums[2] - nums[0] >= 2 - 0.
nums[3] - nums[2] >= 3 - 2.
Hence, it is a balanced subsequence, and its sum is the maximum among the balanced subsequences of nums.
The subsequence consisting of indices 1, 2, and 3 is also valid.
It can be shown that it is not possible to get a balanced subsequence with a sum greater than 14.

Example 2:
Input: nums = [5,-1,-3,8]
Output: 13
Explanation: In this example, the subsequence [5,8] consisting of indices 0 and 3 can be selected.
nums[3] - nums[0] >= 3 - 0.
Hence, it is a balanced subsequence, and its sum is the maximum among the balanced subsequences of nums.
It can be shown that it is not possible to get a balanced subsequence with a sum greater than 13.

Example 3:
Input: nums = [-2,-1]
Output: -1
Explanation: In this example, the subsequence [-1] can be selected.
It is a balanced subsequence, and its sum is the maximum among the balanced subsequences of nums.
*/


//11. LARGEST DIVISIBLE SUBSET
//RECURSION (BRUTE FORCE)
class Solution {
public:
    //recursion
    void generate(vector<int>& nums, vector<int>& ans, vector<int>& temp, int i, int p) {
        if(i >= nums.size()) {
            if(temp.size() > ans.size()) {
                ans = temp;
            }
            return;
        }
        
        if(p == -1 || nums[i] % p == 0) {
            temp.push_back(nums[i]);
            generate(nums, ans, temp, i+1, nums[i]);
            temp.pop_back();
        }
        
        generate(nums, ans, temp, i+1, p);
    }
    
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans;
        vector<int> temp;
        generate(nums, ans, temp, 0, -1);
        
        return ans;
    }
};

//BOTTOM UP (COPIED)                                            {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(begin(nums), end(nums));

        int n = nums.size();
        vector<int> t(n, 1);

        vector<int> prev_idx(n, -1);
        int last_chosen_index = 0;
        int maxL = 1;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i]%nums[j] == 0) {
                    if(t[i] < t[j]+1) {
                        t[i] = t[j]+1;
                        prev_idx[i] = j;
                    }

                    if(t[i] > maxL) {
                        maxL = t[i];
                        last_chosen_index = i;
                    }
                }
            }
        }

        vector<int> result;
        while(last_chosen_index >= 0) {
            result.push_back(nums[last_chosen_index]);
            last_chosen_index = prev_idx[last_chosen_index];
        }

        return result;
    }
};
/*
Example 1:
Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.

Example 2:
Input: nums = [1,2,4,8]
Output: [1,2,4,8]
*/


//STRING BASED DP---------------------------------------------------------------------------------
//12. LONGEST COMMON SUBSEQUENCE                                      {T.C = O(N^2), S.C = O(N^2)}
//2D DP, (LIS)
class Solution {
public:
    int dp[1001][1001];
    int solveMem(string &a, string &b, int i , int j){
        //base case
        if(i >= a.size() || j >= b.size()){
            return 0;
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        int count = 0;
        if(a[i] == b[j]){
            count = 1 + solveMem(a, b, i+1, j+1);
        }else{  //a[i] != b[j]
            count = max(solveMem(a, b, i+1, j), solveMem(a, b, i, j+1));
        }

        return dp[i][j] = count;
    }
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        // vector<vector<int>>dp(n+1, vector<int>(m+1, -1));
        memset(dp, -1, sizeof(dp));
        return solveMem(text1, text2, 0, 0);                     //0, 0 = starting index of both strings
    }
};
/*
Example 1:
Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
*/


//13. SHORTEST COMMON SUPERSEQUENCE                                   {T.C = O(N^2), S.C = O(N^2)}
//STRING DP(MEMOIZATION)
class Solution
{
    public:
    int dp[101][101];
    int solveMem(string &a, string &b, int i, int j){
        int n = a.length(), m = b.length();
        //base case
        if(i == n){
            return m-j ;                 //remaining char
        } 
        if(j == m){
            return n-i;                  //remaining char
        }
        
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int len = 0;
        if(a[i] == b[j]){
            dp[i][j] = 1 + solveMem(a, b, i+1, j+1);
        }else{
            dp[i][j] = 1  + min(solveMem(a, b, i+1, j), solveMem(a, b, i, j+1));
        }
        
        return dp[i][j];
    }
    int shortestCommonSupersequence(string X, string Y, int m, int n)
    {
        memset(dp, -1 , sizeof(dp));
        return solveMem(X, Y, 0, 0);               //0 = i, j (starting pointers both string)
    }
};

//TABULATION (BOTTOM UP)
class Solution
{
    public:
    
    int solveTab(string &a, string &b, int n, int m){           //n<->m
        vector<vector<int>>dp(n+1, vector<int>(m+1));
        
        for(int i = 0 ; i < n+1; i++){                        //last char included
            for(int j = 0 ; j < m+1 ; j++){
                if(i == 0 || j == 0){                        //0+i/j = i/j(length)
                    dp[i][j] = i+j;                         
                }else if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[n][m];
    }
    int shortestCommonSupersequence(string X, string Y, int m, int n)
    {
        return solveTab(X, Y, m, n);
    }
};
/*
Example 1
Input:
X = abcd, Y = xycd
Output: 6
Explanation: Shortest Common Supersequence
would be abxycd which is of length 6 and
has both the strings as its subsequences.

Example 2
Input:
X = efgh, Y = jghi
Output: 6
Explanation: Shortest Common Supersequence
would be ejfghi which is of length 6 and
has both the strings as its subsequences.
*/


//14. SHORTEST COMMON SUPERSEQUENCE                                     {T.C = O(N*M), S.C = O(N*M)}
//STRING DP (ABOVE + PRINT)
class Solution {
public:
    //find answer from traversing from last corner
    string solveTab(string &a, string &b, int n, int m, string &ans){
        vector<vector<int>>dp(n+1, vector<int>(m+1));
        for(int i = 0 ; i < n+1 ; i++){
            for(int j = 0 ; j < m+1 ; j++){
                if(i == 0 || j == 0){                //0+i/j = i/j(length)
                    dp[i][j] = i+j;
                }else if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        //printing string (bottom up)
        int i = n , j = m;
        while(i > 0 && j > 0){
            if(a[i-1] == b[j-1]){
                ans.push_back(a[i-1]);                  //take char and move diagonally up
                i--, j--;
            }else{
                if(dp[i-1][j] < dp[i][j-1]){
                    ans.push_back(a[i-1]);
                    i--;
                }else{
                    ans.push_back(b[j-1]);
                    j--;
                }
            }
        }
        while(i > 0){
            ans.push_back(a[i-1]);
            i--;
        }
        while(j > 0){
            ans.push_back(b[j-1]);
            j--;
        }

        reverse(ans.begin(), ans.end());                      //reverse string

        return ans;
    }
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.length(), m = str2.length();
        string ans;
        return solveTab(str1, str2, n, m, ans);
    }
};
/*
Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.

Example 2:
Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"
*/


//15. EDIT DISTANCE                                                 {T.C = O(N*M), S.C = O(N*M)}
//STRING DP
class Solution {
public:
    int solveMem(string &word1, string &word2, vector<vector<int>>& dp, int i, int j) {
        int m = word1.length();
        int n = word2.length();

        // Base case
        if (i == m) {                      //string1 is fully traversed now rest(n-j length is ans)
            return n - j;
        }
        if (j == n) {                      //string2 is fully traversed now rest(m-i length is ans)
            return m - i;
        }

        //step3 if answer already present, return it
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int mini = INT_MAX;
        // Recursive call
        if (word1[i] == word2[j]) {
            mini = solveMem(word1, word2, dp, i + 1, j + 1);
        } else { // Min of insert, delete, replace
            int insertOp = solveMem(word1, word2, dp, i, j + 1);   //It increments the index j of word2 while keeping the index i of word1 the same
            int deleteOp = solveMem(word1, word2, dp, i + 1, j);   //It increments the index i of word1 while keeping the index j of word2 the same
            int replacOp = solveMem(word1, word2, dp, i + 1, j + 1);//It increments the index i of word1 as well as index j of word2

            mini = 1 + min({insertOp, deleteOp, replacOp});         //1 (current operation + other)         
        }

        //step2 store ans in dp
        return dp[i][j] = mini;
    }

    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        //step1 create a dp vector
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solveMem(word1, word2, dp, 0, 0);                  //0, 0 = starting index of both strings
    }
};
/*
Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
*/


//PALINDROMIC PATTERN
//16. PALINDROMIC SUBSTRINGS (give len)
//BRUTE FORCE                                                         {T.C = O(N^3), S.C = O(1)}                       
class Solution {
public:
    bool isPalindrome(string s){            //not by reference
        int n = s.length();
        int i = 0, j = n-1;
        while(i < j){
            if(s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                if(isPalindrome(s.substr(i, j-i+1))) count++;
            }
        }
        return count;
    }
};

//mik blueprint for palindromic substrings questions                   {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[1005][1005];
    int solveBluPr(string &s){
        int n = s.length();
        int count = 0;
        for(int l = 1; l <= n; l++){           //main loop for traverse each substring lengths
            for(int i = 0; i+l-1 < n; i++){   //i+l-1 == last substring
                int j = i+l-1;
                if(l == 1) dp[i][j] = true;                    //all single char is palindromes
                else if(l == 2) dp[i][j] = (s[i] == s[j]);     //check both should same
                else dp[i][j] = (s[i] == s[j] && dp[i+1][j-1] == true);  //check first and last char (between memoization works)

                if(dp[i][j] == true) count++;
            }
        }
        return count;
    }
    int countSubstrings(string s) {
        memset(dp, -1, sizeof(dp));
        return solveBluPr(s);                            //BluPr = blue print
    }
};
/*
Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
*/


//17. LONGEST PALINDROMIC SUBSTRING (Print)                            {T.C = O(N^2), S.C = O(N^2)}
//MIK BLUE PRINT
class Solution {
public:
    int dp[1005][1005];
    void solveBluPr(string &s){
        int n = s.length();
        for(int l = 1; l <= n; l++){              //traverse each len of substrings
            for(int i = 0 ; i+l-1 < n; i++){
                int j = i+l-1;
                if(l == 1) dp[i][j] = true;
                else if(l == 2) dp[i][j] = (s[i] == s[j]);
                else dp[i][j] = (s[i] == s[j] && dp[i+1][j-1] == true);   //substring len > 2
            }
        }
    }
    string longPalindromePr(string &s){
        int n = s.length();
        int maxLen = 0, startIdx = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = i; j < n; j++){
                if(dp[i][j] == true && (j-i+1) > maxLen){
                    maxLen = j-i+1;
                    startIdx = i;
                }
            }
        }
        return s.substr(startIdx, maxLen);
    }
    string longestPalindrome(string s) {
        memset(dp, -1, sizeof(dp));
        solveBluPr(s);

        return longPalindromePr(s);             //print longest palindrome
    }
};


//USING MEMOIZATION                                             {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[1005][1005];
    bool solveMem(string &s, int i, int j){
        //base case
        if(i >= j) return true;               //single char, or empty string is true

        if(dp[i][j] != -1) return dp[i][j];

        if(s[i] == s[j]) return dp[i][j] = solveMem(s, i+1, j-1);      //first , last match
        return false;
    }
    string longestPalindrome(string s) {
        memset(dp, -1, sizeof(dp));
        int n = s.length();
        int maxLen = 0;
        int startIdx = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = i ; j < n ; j++){
                if(solveMem(s, i, j)){
                    if(j-i+1 > maxLen){
                        maxLen = j-i+1;
                        startIdx = i;
                    }
                }
            }
        }
        return s.substr(startIdx, maxLen);
    }
};


//USING LCS PATTERN
class Solution {
public:
    int dp[1005][1005];
    int solveLCS(string &a, string &b){
        int n = a.length();              //n == m
        //1st row and col is 0
        for(int i = 0; i < n+1; i++) dp[i][0] = 0;
        for(int j = 0; j < n+1; j++) dp[0][j] = 0;

        int maxLen = 0;
        for(int i = 1; i < n+1; i++){
            for(int j = 1; j < n+1; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                    maxLen = max(maxLen, dp[i][j]);
                }else{
                    dp[i][j] = 0;
                }
            }
        }
        // return dp[n][n];
        return maxLen;
    }
    int longestPalindrome(string s) {
        memset(dp, -1, sizeof(dp));
        string copyStr = s;
        reverse(copyStr.begin(), copyStr.end());
        return solveLCS(s, copyStr);
    }
};
/*
Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
*/



//18. LONGEST PALINDROMIC SUBSEQUENCE                          {T.C = O(N^2), S.C = O(N^2)}
//USING LCS PATTERN
class Solution {
public:
    int dp[1005][1005];
    int solveLCS(string &a, string &b){
        int n = a.length();            //n == m (same len)

        //0th row & col should be zero
        for(int i = 0 ; i < n+1; i++) dp[i][0] = 0;
        for(int j = 0 ; j < n+1; j++) dp[0][j] = 0;
        

        for(int i = 1; i <= n; i++){ 
            for(int j = 1; j <= n; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][n];                         //at the end have maxLen subsequence
    }
    int longestPalindromeSubseq(string s) {
        memset(dp, -1, sizeof(dp));
        string copyStr = s;
        reverse(copyStr.begin(), copyStr.end());
        return solveLCS(s, copyStr);
    }
};
/*
Example 1:
Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:
Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".
*/


//19. MINIMUM INSERTION STEPS TO MAKE A STRING PALINDROME
//USING LCS                                                       {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[501][501];
    int solveLCS(string &a, string &b){
        int n = a.length();               //n == m
        //base case fill first row & col with 0
        for(int i = 0 ; i < n+1 ; i++) dp[i][0] = 0;
        for(int j = 0 ; j < n+1 ; j++) dp[0][j] = 0;

        //fill remaining table
        for(int i = 1 ; i < n+1 ; i++){
            for(int j = 1 ; j < n+1 ; j++){
                if(a[i-1] == b[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][n];
    }
    int longestPalindromeSubseq(string &s){                 //lps
        string copyStr = s;
        reverse(copyStr.begin(), copyStr.end());
        return solveLCS(s, copyStr);                  //s is now reverse string
    }
    int minInsertions(string s) {
        int n = s.length();
        int LPS = longestPalindromeSubseq(s);
        return n - LPS;                                 //min insertion req n-lps(all except already palindromes char)
    }
};
/*
Example 1:
Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.

Example 2:
Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:
Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".
*/


//20. PALINDROME PARTITIONING 
//USING BACKTRACKING                                              {T.C = O(N*2^N), S.C = O(N)}
class Solution {
public:
    bool isPalindrome(string &s, int i, int j){
        while(i < j){
            if(s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    void solve(string &s, vector<vector<string>>&ans, vector<string>&temp, int i){
        int n = s.length();
        //base case
        if(i == n) return ans.push_back(temp);

        //push and pop (backtracking)
        for(int j = i ; j < n; j++){
            if(isPalindrome(s, i, j)){
                temp.push_back(s.substr(i, j-i+1));
                solve(s, ans, temp, j+1);                 //j+1 for next index
                temp.pop_back();                          //backtrack
            } 
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>>ans;
        vector<string>temp;
        int n = s.length();
        solve(s, ans, temp, 0);
        return ans;
    }
};
/*
Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]
*/


//21. PALINDROME PARTITIONING II
//USING MEMOIZATION                                               {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[2005];
    bool isPalindrome(string &s, int i, int j){
        while(i < j){
            if(s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    int solveMem(string &s, int i){
        int n = s.length();
        //base case
        if(i == n) return 0;

        if(dp[i] != -1) return dp[i];

        int minCost = INT_MAX, cost = 0;
        for(int j = i ; j < n ; j++){
            if(isPalindrome(s, i, j)){             //check string i to j
                cost = 1 + solveMem(s, j+1);       //next i = j+1
                minCost = min(cost, minCost);
            } 
        }
        return dp[i] = minCost;
    }
    int minCut(string s) {
        memset(dp, -1, sizeof(dp));
        return solveMem(s, 0)-1;                       //0 = initial index, -1 = exclude partition of after end string
    }
};
/*
Example 1:
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:
Input: s = "a"
Output: 0

Example 3:
Input: s = "ab"
Output: 1
*/


//DP ON GRIDS-----------------------------------------------------------------------------------------------------
//22. UNIQUE PATHS
//USING MEMOIZATION                                              {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[105][105];
    int solveMem(int n, int m, int i, int j){
        //base case
        if(i >= n || j >= m) return 0;
        if(i == n-1 && j == m-1) return 1;           //start == dest(1 way)

        if(dp[i][j] != -1) return dp[i][j];

        int down = solveMem(n, m, i+1, j);            //finding ways (not add 1 or val)
        int right= solveMem(n, m, i, j+1);

        return dp[i][j] = down + right;            
    }
    int uniquePaths(int m, int n) {
        memset(dp, -1, sizeof(dp));
        return solveMem(n, m, 0, 0);                //{0, 0} = starting cells
    }
};
/*
Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
*/


//23. UNIQUE PATHS II 
//USING MEMOIZATION                                            {T.C = O(N^2), S.C = O(N^2)}
class Solution {
public:
    int dp[105][105];
    int solveMem(vector<vector<int>>&grid, int n, int m, int i, int j){
        //base case
        if(i >= n || j >= m || grid[i][j] == 1) return 0;  //obstacles handles
        if(i == n-1 && j == m-1) return 1;                 //start == destination

        if(dp[i][j] != -1) return dp[i][j];

        int down = solveMem(grid, n, m, i+1, j);
        int right= solveMem(grid, n, m, i, j+1);

        return dp[i][j] = down + right;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        memset(dp, -1, sizeof(dp));
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        return solveMem(obstacleGrid, n, m, 0, 0);    //{0, 0} first cell
    }
};
/*
Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
*/
//PREFIX SUM
#include<bits/stdc++.h>
using namespace std;

//01. LEFT AND RIGHT SUM DIFFERNCE                                              {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int>prefixSum(n);
        prefixSum[0] = nums[0];
        for(int i = 1 ; i < n ; i++){
            prefixSum[i] = prefixSum[i-1] + nums[i];       //add prev
        }

        vector<int>suffixSum(n);
        suffixSum[n-1] = nums[n-1];
        for(int i = n-2 ; i >= 0 ; i--){
            suffixSum[i] = suffixSum[i+1] + nums[i];        //add next
        } 

        vector<int>ans;
        for(int i = 0 ; i < n; i++){
            ans.push_back(abs(suffixSum[i]-prefixSum[i]));
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [10,4,8,3]
Output: [15,1,11,22]
Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].

Example 2:
Input: nums = [1]
Output: [0]
Explanation: The array leftSum is [0] and the array rightSum is [0].
The array answer is [|0 - 0|] = [0].
*/


//02. RUNNING SUM OF 1D ARRAY                                               {T.C = O(N), S.C = O(N)}
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();
        vector<int>prefixSum(n);
        prefixSum[0] = nums[0];
        for(int i = 1; i < n ; i++){
            prefixSum[i] = prefixSum[i-1] + nums[i];
        }
        return prefixSum;
    }
};
/*
Example 1:
Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].

Example 2:
Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].

Example 3:
Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]
*/


//03. FIND THE PIVOT INTEGER                                                  {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int pivotInteger(int n) {
        vector<int>prefixSum(n+1);                 //1 based indexing
        prefixSum[1] = 1;
        for(int i = 2; i <= n ; i++){
            prefixSum[i] = prefixSum[i-1] + i;
        }
        
        vector<int>suffixSum(n+1);                 //1 based indexing
        suffixSum[n] = n;
        for(int i = n-1 ; i >= 1 ; i--){
            suffixSum[i] = suffixSum[i+1] + i;
        }
        for(int i = 1 ; i <= n ; i++){
            if(prefixSum[i] == suffixSum[i]) return i;
        }
        return -1;
    }
};
/*
Example 1:
Input: n = 8
Output: 6
Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.

Example 2:
Input: n = 1
Output: 1
Explanation: 1 is the pivot integer since: 1 = 1.

Example 3:
Input: n = 4
Output: -1
Explanation: It can be proved that no such integer exist.
*/


//04. FIND THE HIGHEST ALTITUDE                                            {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int n = gain.size();
        vector<int>prefixSum(n+1, 0);
        prefixSum[0] = gain[0];
        for(int i = 1; i < n ; i++){
            prefixSum[i] = prefixSum[i-1] + gain[i];
        }
        return *max_element(prefixSum.begin(), prefixSum.end());
    }
};
/*
Example 1:
Input: gain = [-5,1,5,0,-7]
Output: 1
Explanation: The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.

Example 2:
Input: gain = [-4,-3,-2,-1,4,3,2]
Output: 0
Explanation: The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.
*/


//05. SUM OF ALL SUBLENGTH ARRAY                               
//BRUTE FORCE                                                             {T.C = O(N^2), S.C = O(1)}
class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int totalSum = 0;
        for(int i = 0  ; i < n; i++){
            int subArrSum = 0;
            for(int j = i ; j < n ; j++){
                subArrSum += arr[j];
                if((j-i+1) % 2 != 0) totalSum += subArrSum;
            }
        }
        return totalSum;
    }
};

//OPTIMIZED APPROACH                                                           {T.C = O(N), S.C = O(N)}
class Solution {
public:
    //total subarrays in an array(n) = n*(n+1)/2
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int totalSum = 0;
        for(int i = 0 ; i < n;  i++){
            int totalSubArr = (i+1) * (n-i);       //left * right
            int oddSubArr   = (totalSubArr + 1) / 2;

            totalSum += oddSubArr * arr[i];
        }
        return totalSum;
    }
};
/*
Example 1:
Input: arr = [1,4,2,5,3]
Output: 58
Explanation: The odd-length subarrays of arr and their sums are:
[1] = 1
[4] = 4
[2] = 2
[5] = 5
[3] = 3
[1,4,2] = 7
[4,2,5] = 11
[2,5,3] = 10
[1,4,2,5,3] = 15
If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58

Example 2:
Input: arr = [1,2]
Output: 3
Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their sum is 3.

Example 3:
Input: arr = [10,11,12]
Output: 66
*/


//06. POINTS THAT INTERSECT WITH CARS                                {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        int n = INT_MIN;
        for(auto it : nums) n = max(n, it[1]);     //n at max upper bound
        
        vector<int>freqArr(n+1, 0);               //PREFIX SUM
        for(auto it : nums){
            int start = it[0];
            int end   = it[1];
            freqArr[start]++;
            if(end+1 <= n) freqArr[end+1]--;         //ending in inclusive (mark next -ve(breaking point))
        }
        int ans = 0;
        for(int i = 1 ; i <= n ; i++){                //n inclusive
            freqArr[i] = freqArr[i-1] + freqArr[i];
            if(freqArr[i] > 0) ans++;
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [[3,6],[1,5],[4,7]]
Output: 7
Explanation: All the points from 1 to 7 intersect at least one car, therefore the answer would be 7.

Example 2:
Input: nums = [[1,3],[5,8]]
Output: 7
Explanation: Points intersecting at least one car are 1, 2, 3, 5, 6, 7, 8. There are a total of 7 points, therefore the answer would be 7.
*/
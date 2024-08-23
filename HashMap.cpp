//HASHMAP
#include<bits/stdc++.h>
using namespace std;


//001. TWO SUM
//BRUTE FORCE
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i = 0 ; i < n ; i++){
            for(int j = i+1 ; j < n ; j++){
                if(nums[i]+nums[j] == target){
                    return {i, j};
                }
            }
        }
        return {};
    }
};

//MAP
//2 ITERATIONS + 1 ITERATIONS
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int,int>mp;

        //2 iterations
        /* 
        for(int i = 0 ; i  < nums.size() ; i++){
            mp[nums[i]] = i;
        }
        for(int i = 0 ; i < nums.size() ; i++){
            int compliment = target-nums[i];
            if(mp.count(compliment) && mp[compliment] != i){
                return {i, mp[compliment]};
            }
        }
        */

        //1 iteration
        for(int i = 0 ; i < n ; i++){
            int compliment = target - nums[i];
            if(mp.count(compliment) && mp[compliment] != i){
                return {i, mp[compliment]};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};
/*
Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
*/
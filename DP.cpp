#include<bits/stdc++.h>
using namespace std;


//MINIMUM LENGTH OF CONCATENATED STRING WITH UNIQUE CHARACTERS                 {T.C = O(EXP{2^N}), S.C = O(1)}
/*
Use simple recursion , if duplicate present then exclude char otherwise include or exclude(take or non take) , finally return
max of incl or excl.
*/
class Solution {
public:
    bool hasDuplicate(string &s1, string &s2){
        int arr[26] = {0};                //small char only
        for(auto ch1 : s1){
            if(arr[ch1-'a'] > 0){         //'aa', 'bbb'
                return true;
            }
            arr[ch1-'a']++;                //inserting char in arr
        }

        for(auto ch2 : s2){               //finding s1 char in s2
            if(arr[ch2-'a'] > 0){ 
                return true;
            }
        }
        return false;
    }
    int solve(vector<string>&arr, string temp, int i){           // not &temp
        //base case
        if(i >= arr.size()){
            return temp.length();
        }

        int incl = 0;
        int excl = 0;
        if(hasDuplicate(arr[i], temp)){  //exclude only
            excl = solve(arr, temp, i+1);
        }else{     //incl or excl
            excl = solve(arr, temp, i+1);
            incl = solve(arr, temp+arr[i], i+1);
        }
        return max(incl, excl);
    }
    int maxLength(vector<string>& arr) {
        string temp = "";
        return solve(arr, temp, 0);          //0 = initial index
    }
};
/*
Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.
Example 2:

Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").

Example 3:
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.
*/
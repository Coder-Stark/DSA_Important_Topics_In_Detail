//SLIDING WINDOWS QUESTIONS (Aditya Veram)

#include<bits/stdc++.h>
using namespace std;

//01. MAX SUM SUBARRAY OF SIZE K                                                    {T.C = O(N), S.C = O(1)}
class Solution{   
public:
    long maximumSumSubarray(int K, vector<int> &Arr , int N){
        int i = 0, j = 0;
        long maxi = INT_MIN;
        long sum = 0;
        while(j < N){
            sum += Arr[j];                       //calculation
            
            if(j-i+1 < K){                       //j-i+1 = window size
                j++;
            }else if(j-i+1 == K){
                maxi = max(maxi, sum);           //calculation
                sum -= Arr[i];                   //slide window
                i++;
                j++;
            }
        }
        return maxi;
    }
};
/*
Input:
N = 4, K = 2
Arr = [100, 200, 300, 400]
Output:
700
Explanation:
Arr3  + Arr4 =700,
which is maximum.
*/


//02. FIRST NEGATIVE INTEGER IN EVERY WINDOW OF SIZE K                              {T.C = O(N), S.C = O(N)}
vector<long long> printFirstNegativeInteger(long long int A[], long long int N, long long int K) {
    
    int i = 0, j = 0;
    vector<long long>ans;
    vector<long long>storeNegative;
    
    while(j < N){
        if(A[j] < 0){
            storeNegative.push_back(A[j]);           //calculation
        }
        if(j-i+1 < K){
            j++;
        }else if(j-i+1 == K){
            if(storeNegative.empty()){               //calculation
                ans.push_back(0);
            }else{
                ans.push_back(storeNegative[0]);
                if(A[i] < 0){
                    storeNegative.erase(storeNegative.begin());       //slide window
                }
            }
            i++;
            j++;
        }
    }
    return ans;
}
/*
Input : 
N = 5
A[] = {-8, 2, 3, -6, 10}
K = 2
Output : 
-8 0 -6 -6
Explanation :
First negative integer for each window of size k
{-8, 2} = -8
{2, 3} = 0 (does not contain a negative integer)
{3, -6} = -6
{-6, 10} = -6
*/


//03. COUNT OCCURRENCES OF ANAGRAMS                                             {T.C = O(N), S.C = O(1)}
//total anagrams possible = n! (n = string length)
class Solution{
public:
    bool isAllZero(vector<int>&count){
        for(auto it : count){
            if(it != 0){
                return false;
            }
        }
        return true;
    }
	int search(string pat, string txt) {
	    int n = txt.size();
	    int k = pat.size();
	    int i = 0, j = 0;
	    vector<int>count(26, 0);              //or map
	    for(auto ch : pat){
	        count[ch-'a']++;
	    }
	    
	    int ans = 0;
	    while(j < n){
	        count[txt[j]-'a']--;                 //calculation
	        if(j-i+1 == k){                      //window hit
	            if(isAllZero(count)){    
	                ans++;
	            }
	            count[txt[i]-'a']++;             //else slide from left by adding count of char
	            i++;
	        }
	        j++;
	    }
	    
	    return ans;
	}

};
/*
Example 1:
Input:
txt = forxxorfxdofr
pat = for
Output: 3
Explanation: for, orf and ofr appears
in the txt, hence answer is 3.

Example 2:
Input:
txt = aabaabaa
pat = aaba
Output: 4
Explanation: aaba is present 4 times
in txt.
*/


//04. MAXIMUM OF ALL SUBARRAYS OF SIZE K                                       {T.C = O(N), S.C = O(N)}
class Solution
{
  public:
    //Function to find maximum of each subarray of size k.
    vector <int> max_of_subarrays(int *arr, int n, int k)
    {
        int i = 0, j = 0;
        int maxi = arr[0];
        vector<int>ans;
        while(j < n){
            maxi = max(arr[j], maxi);
            if(j-i+1 == k){
                ans.push_back(maxi);
                if(arr[i] == maxi){              //reset maxi and search again (j = i)
                    maxi = -1;
                    j = i;
                }
                i++;
            }
            j++;
        }
        return ans;
    }
};
/*
Example 1:
Input:
N = 9, K = 3
arr[] = 1 2 3 1 4 5 2 3 6
Output: 
3 3 4 5 5 5 6 
Explanation: 
1st contiguous subarray = {1 2 3} Max = 3
2nd contiguous subarray = {2 3 1} Max = 3
3rd contiguous subarray = {3 1 4} Max = 4
4th contiguous subarray = {1 4 5} Max = 5
5th contiguous subarray = {4 5 2} Max = 5
6th contiguous subarray = {5 2 3} Max = 5
7th contiguous subarray = {2 3 6} Max = 6

Example 2:
Input:
N = 10, K = 4
arr[] = 8 5 10 7 9 4 15 12 90 13
Output: 
10 10 10 15 15 90 90
Explanation: 
1st contiguous subarray = {8 5 10 7}, Max = 10
2nd contiguous subarray = {5 10 7 9}, Max = 10
3rd contiguous subarray = {10 7 9 4}, Max = 10
4th contiguous subarray = {7 9 4 15}, Max = 15
5th contiguous subarray = {9 4 15 12}, 
Max = 15
6th contiguous subarray = {4 15 12 90},
Max = 90
7th contiguous subarray = {15 12 90 13}, 
Max = 90
*/


//05a. LONGEST SUB-ARRAY WITH SUM K (VARIABLE SLIDIING WINDOW)                {T.C = O(N), S.C = O(1)}
//ONLY FOR POSITIVE INTEGERS
class Solution{
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int i = 0, j = 0;
        int sum = 0;
        int maxLen = 0;
        while(j < n){
            sum += a[j];
            if(sum == k){
                maxLen = max(maxLen, (j-i+1));
            }
            if(sum > k){
                while(sum > k){
                    sum -= a[i];
                    i++;
                }
            }
            j++;
        }
        return maxLen;
    } 
};

//05b. LONGEST SUB-ARRAY WITH SUM K (VARIABLE SLIDIING WINDOW)                {T.C = O(N), S.C = O(1)}
//FOR NEGATIVE NUMBERS
//BRUTE FORCE                                                                 {T.C = O(N^2), S.C = O(1)}
class Solution{
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int maxi = 0;
        for(int i = 0 ; i < n ; i++){
            int sum = 0;                               //sum is there not in top (reset sum)
            for(int j = i ; j < n ; j++){
                sum += a[j];
                if(sum == k){
                    maxi = max(maxi, j-i+1);
                }
            }
        }
        return maxi;
    } 
};
//OPTIMIZED APPROACH (USING MAP)                                               {T.C = O(N), S.C = O(N)}
class Solution{ 
    public:
    int lenOfLongSubarr(int a[],  int n, int k) 
    { 
        int maxLen = 0;
        int sum = 0;
        unordered_map<int, int>mp;
        for(int i = 0 ; i < n ; i++){
            sum += a[i];
            if(sum == k){
                maxLen = max(maxLen, i+1);              //for 0 based indexing             //length of subarray
            }
            if(mp.find(sum-k) != mp.end()){
                maxLen = max(maxLen, i-mp[sum-k]);
            }
            if(mp.find(sum) == mp.end()){               //prev not found sum
                mp[sum] = i;
            }
        }
        return maxLen;
    } 
};
/*
Input :
A[] = {10, 5, 2, 7, 1, 9}
K = 15
Output : 4
Explanation:
The sub-array is {5, 2, 7, 1}.
*/


//06. LONGEST K UNIQUE CHARACTERS SUBSTRING                          {T.C = O(N), S.C = O(N)}
class Solution{
  public:
    int longestKSubstr(string s, int k) {
    int i=0,j=0,maxLen=-1;
    unordered_map<char,int>mp;
    int n=s.length();
    
    while(j < n){
        mp[s[j]]++;
        if(mp.size()==k){
            maxLen=max(maxLen,j-i+1);
        }  
        else{
            while(mp.size()>k){
                mp[s[i]]--;
                
                if(mp[s[i]]==0){
                  mp.erase(s[i]);
                }
                i++;  
            }
        }
        j++;
    }
    return maxLen;
    }
};
/*
Example 1:
Input:
S = "aabacbebebe", K = 3
Output: 
7
Explanation: 
"cbebebe" is the longest substring with 3 distinct characters.

Example 2:
Input: 
S = "aaaa", K = 2
Output: -1
Explanation: 
There's no substring with 2 distinct characters.
*/


//07. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS                  {T.C = O(N), S.C = O(N)}
//USING MAP
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        unordered_map<char, int>mp;
        int i = 0, j = 0, maxLen = 0;
        while(j < n){
            mp[s[j]]++;
            if(mp.size() == j-i+1){
                maxLen = max(maxLen, j-i+1);
            }
            if(mp.size() < j-i+1){                //remember its less then condition others have greater
                while(mp.size() < j-i+1){
                    mp[s[i]]--;
                    if(mp[s[i]] == 0){
                        mp.erase(s[i]);
                    }
                    i++;
                }
            }
            j++;
        }
        return maxLen;
    }
};

//USING SET
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int i = 0, j = 0;
        int maxi = 0;
        unordered_set<char>unSt;                 //for store unique element
        while(j < n){
            if(unSt.count(s[j]) == 0){
                unSt.insert(s[j]);
                maxi = max(maxi, j-i+1);         //max size window
                j++;
            }else{ //st.count(st[j] != 0)
                while(unSt.count(s[j]) != 0){
                    unSt.erase(s[i]);
                    i++;
                }
            }
        }
        return maxi;
    }
};
/*
Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/


//08. FRUIT INTO BASKETS / PICK TOYS                                         {T.C = O(N), S.C = O(N)}
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        unordered_map<int , int>mp;
        int i = 0, j = 0;
        int maxLen = 0;
        while(j < n){
            mp[fruits[j]]++;
            while(mp.size() > 2){
                mp[fruits[i]]--;
                if(mp[fruits[i]] == 0){
                    mp.erase(fruits[i]);
                }
                i++;
            }
            maxLen = max(maxLen, (j-i+1));
            j++;
        }
        return maxLen;
    }
};
/*
Example 1:
Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.

Example 2:
Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:
Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
*/


//10. MINIMUM WINDOW SUBSTRING                                                 {T.C = O(N), S.C = O(N)}
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        int m = t.size();
        int minLen = INT_MAX;
        unordered_map<char, int>mp;                 //store small string chars in map
        for(auto it : t){
            mp[it]++;
        }
        int count = mp.size();
        int i = 0, j = 0, start = 0;
        while(j < n ){
            if(mp.find(s[j]) != mp.end()){
                mp[s[j]]--;
                if(mp[s[j]] == 0){
                    count--;
                }
            }
            if(count == 0){                    //curr window contains all char of t
                while(count == 0){             //shrinking window
                    if(mp.find(s[i]) != mp.end()){
                        mp[s[i]]++;
                        if(mp[s[i]] == 1){
                            count++;
                            if(j-i+1 < minLen){
                                minLen = j-i+1;
                                start = i;             //search for new window
                            }
                        }
                    }
                    i++;
                }
            }
            j++;
        }
        return minLen == INT_MAX ? "": s.substr(start, minLen);
    }
};
/*
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
*/



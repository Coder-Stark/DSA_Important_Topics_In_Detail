// BIT MANIPULATION

#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------- BASIC THINGS -------------------------------------------------*/
/*
RIGHT MOST BIT (a) = a & 1  {if ans is 1 then odd else 0 then even}   //OR MOST SIGNIFICANT BIT(MSB)
RIGHT SHIF (a)(1001 => 100) = a >>= 1
LEFT SHIF (a)(1001 => 1010) = a << 1
FIND Ith BIT = (num >> i) & 1.
//same as above
FIND Ith BIT IS 0 OR 1 = (num & (1 << i)) >> i        //(num & (1 << i)) == 0 {ith bit is 0} , == 1{ith bit is 1}  //(1 << i) => bitMasking
UNSET(make 1 to 0) A SET BIT = n & (n-1)
NO. OF BITS REQUIRED FOR REPRESENT PARTICULAR NUMBER(X) = LOG2(X) + 1
*/
/*-----------------------------------------------------------------------------------------------------------*/
// 01. MINIMUM FLIPS TO MAKE (A) OR (B) EQUAL TO (C)
// BRUTE FORCE APPROACH(INTUTIVE)                                            {T.C = O(N), S.C = O(1)}
/*
Check the bits one by one whether they need to be flipped. basically we have to check for all the numbers untill all will 0
and check for right most bit of c if it is 1 then flips++ (one of a or b should 0)  else it is 0, then (both should 0) and
make right shift of all a, b, c , finally return flips.
*/
class Solution
{
public:
    int minFlips(int a, int b, int c)
    {
        int flips = 0;
        while (a != 0 || b != 0 || c != 0)
        { // break only a,b,c=0,0,0
            if ((c & 1) == 1)
            { // for c's right most bit 1 (one of  a or b should 0)
                if ((a & 1) == 0 && (b & 1) == 0)
                {
                    flips++;
                }
            }
            else if ((c & 1) == 0)
            { // for c's right most bit 0 (both should be 0)
                if ((a & 1) == 1)
                {
                    flips++;
                }
                if ((b & 1) == 1)
                {
                    flips++;
                }
            }
            a >>= 1;
            b >>= 1;
            c >>= 1;
        }
        return flips;
    }
};

// ADVANCED APPROACH                                     {T.C = O(N), S.C = O(1)}
class Solution
{
public:
    int minFlips(int a, int b, int c)
    {
        int temp = (a | b) ^ c;                                      // flips
        int extra = ((a & b) & temp);                                // handle extra case
        return __builtin_popcount(temp) + __builtin_popcount(extra); // gives count of 1 bits(ans)
    }
};
/*
Example 1:
Input: a = 2, b = 6, c = 5
Output: 3
Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)

Example 2:
Input: a = 4, b = 2, c = 7
Output: 1

Example 3:
Input: a = 1, b = 2, c = 3
Output: 0
*/

// 02a. SINGLE NUMBER (ALL TWICE EXCEPT ONE(ANS))                           {T.C = O(N), S.C = O(1)}
/*
Just simple take xor of all elements all same element cancel out and left is your ans.
*/
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    { // xor = different element != 0 else 0
        int xorAns = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            xorAns = xorAns ^ nums[i];
        }
        return xorAns;
    }
};
/*
Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1
*/

// 02b. SINGLE NUMBER II  (ALL THRICE EXCEPT ONE(ANS))                                {T.C = O(N), S.C = O(1)}
/*
take a for loop for bit(0 to 31) , take an temp (1 << i {for calculation}) iterate on nums if(it & temp) == 0 (i th bit is 0)
so countzero++, else count1++, if(count1 % 3 == 1) ans = ans | temp and finally return ans.
*/
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ans = 0;

        for (int i = 0; i < 32; i++)
        {
            int temp = 1 << i; // left shift(ith times for reaching ith position of calculation)
            int countZeros = 0;
            int countOnes = 0;
            for (auto it : nums)
            {
                if ((it & temp) == 0)
                { // ith bit is 0
                    countZeros++;
                }
                else
                { // it & temp != 0                //ith bit is 1
                    countOnes++;
                }
            }
            if (countOnes % 3 == 1)
            {
                ans = ans | temp;
            }
        }
        return ans;
    }
};
/*
Example 1:
Input: nums = [2,2,3,2]
Output: 3

Example 2:
Input: nums = [0,1,0,1,0,1,99]
Output: 99
*/

// 03. COUNT BITS (counting 1's in a binary representation of any number)           {T.C = O(N*LOGN), S.C = O(N)}
// USING STL
/*
simply take vector of (n+1) length then take a for loop from 0 to <= n , put ans[i] = __builtinpopcount(i) gives count of 1.
*/
class Solution
{
public:
    vector<int> countBits(int n)
    {
        vector<int> ans(n + 1);
        for (int i = 0; i <= n; i++)
        {
            ans[i] = __builtin_popcount(i); // builtin_popcount gives count of 1 bits (LOGN { a number have logn bits})
        }
        return ans;
    }
};

// INTUTIVE APPROACH                                             {T.C = O(N*LOGN*LOGN), S.C = O(N)}
/*
Take vector of (n+1) size , firstly check for base case if n == 0 return ans, then initialize ans[0] = 0 , apply for loop 1
to <= n now, if it is odd then ans[i] = ans[i/2]+1 else ans[i] = ans[i/2] finally return ans.
*/
class Solution
{
public:
    int findNumBit(int num)
    {
        int count = 0;
        while (num != 0)
        { // logn times (number have total logn bits)
            count += num & 1;
            num >>= 1; // right shift
        }
        return count;
    }
    vector<int> sortByBits(vector<int> &arr)
    {
        int n = arr.size();
        vector<pair<int, int>> temp(n);
        for (int i = 0; i < n; i++)
        {
            temp[i].first = arr[i];
            // temp[i].second = __builtin_popcount(arr[i]);
            temp[i].second = findNumBit(arr[i]);
        }

        auto lambda = [&](auto &a, auto &b) { // auto = bool
            if (a.second == b.second)
            { // if count is same then sort on basis of FIFO
                return a.first < b.first;
            }
            else
            { // if count is different sort on basis of count(1)
                return a.second < b.second;
            }
        };
        sort(temp.begin(), temp.end(), lambda);

        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = temp[i].first;
        }
        return ans;
    }
};
/*
Example 1:
Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

Example 2:
Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
*/

// 04. SORT INTEGERS BY THE NUMBER OF 1 BITS                           {T.C = O(N*LOGN), S.C = O(N)}
/*
Take a vector {num, freq(1)} in first put nums and second call findbit, sort the vector with lambda , if freq is same for
next elemnt then FIFO, else sort on bases of freq. finally store ans in vector and return it.
*/
class Solution
{
public:
    int findNumBit(int num)
    {
        int count = 0;
        while (num != 0)
        {
            count += num & 1;
            num >>= 1; // right shift
        }
        return count;
    }
    vector<int> sortByBits(vector<int> &arr)
    {
        int n = arr.size();
        vector<pair<int, int>> temp(n); //{num , freq(1)}
        for (int i = 0; i < n; i++)
        {
            temp[i].first = arr[i];
            // temp[i].second = __builtin_popcount(arr[i]);
            temp[i].second = findNumBit(arr[i]);
        }

        auto lambda = [&](auto &a, auto &b) { // auto = bool
            if (a.second == b.second)
            { // if count is same then sort on basis of FIFO
                return a.first < b.first;
            }
            else
            { // if count is different sort on basis of count(1)
                return a.second < b.second;
            }
        };
        sort(temp.begin(), temp.end(), lambda); // nlogn*logn

        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = temp[i].first;
        }
        return ans;
    }
};
/*
Example 1:
Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]
Explantion: [0] is the only integer with 0 bits.
[1,2,4,8] all have 1 bit.
[3,5,6] have 2 bits.
[7] has 3 bits.
The sorted array by bits is [0,1,2,4,8,3,5,6,7]

Example 2:
Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
Output: [1,2,4,8,16,32,64,128,256,512,1024]
Explantion: All integers have 1 bit in the binary representation, you should just sort them in ascending order.
*/

// 05. FIND THE ORIGINAL ARRAY OF PREFIX XOR                            {T.C = O(N), S.C = O(N)}
/*
Take an ans vector(n) iterate of pref and put pref[i] ^ pref[i-1] in ans[i], finally return ans.
*/
class Solution
{
public:
    vector<int> findArray(vector<int> &pref)
    {
        int n = pref.size();
        vector<int> ans(n);
        ans[0] = pref[0];
        for (int i = 1; i < n; i++)
        {
            ans[i] = pref[i] ^ pref[i - 1];
        }
        return ans;
    }
};
/*
Example 1:
Input: pref = [5,2,0,3,1]
Output: [5,7,2,3,2]
Explanation: From the array [5,7,2,3,2] we have the following:
- pref[0] = 5.
- pref[1] = 5 ^ 7 = 2.
- pref[2] = 5 ^ 7 ^ 2 = 0.
- pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
- pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.

Example 2:
Input: pref = [13]
Output: [13]
Explanation: We have pref[0] = arr[0] = 13.
*/


//06. MAXIMUM XOR PRODUCT                                               {T.C = O(N), S.C = O(1)}
/*
First handle (49 to nth bit (same value )) fint the i_th(z >> i & 1) bit of both a and b if it is 1 then (update)var = var ^ (1 << i)
then handle from 0 to n-1th bit, find the bits. if both (a == b) then update both else vara > varb then (increase lower value)
finally return vara * varb.
*/
class Solution {
public:
    int mod = 1e9+7;
    typedef long long ll;
    int maximumXorProduct(long long a, long long b, int n) {
        ll aXorx = 0, bXorx = 0;

        //from 49th(constraint) to nth bit all bits copy
        for(ll i = 49; i >= n ; i--){
            int a_ith_bit = (a >> i) & 1;   //finding ith bit
            int b_ith_bit = (b >> i) & 1;

            if(a_ith_bit == 1){
                aXorx = (aXorx ^ (1ll << i));
            }
            if(b_ith_bit == 1){
                bXorx = (bXorx ^ (1ll << i));
            }
        }

        //from n-1th to 0th bit
        for(ll i = n-1 ; i >= 0 ; i--){
            int a_ith_bit = (a >> i) & 1;
            int b_ith_bit = (b >> i) & 1;

            if(a_ith_bit == b_ith_bit){
                aXorx = (aXorx ^ (1ll << i));
                bXorx = (bXorx ^ (1ll << i));
                continue;
            }
            if(aXorx > bXorx){                  //small value increases
                bXorx = (bXorx ^ (1ll << i));
            }else{
                aXorx = (aXorx ^ (1ll << i));
            }
        }  

        aXorx = aXorx % mod;   
        bXorx = bXorx % mod;

        return (aXorx * bXorx ) % mod;
    }
};
/*
Example 1:
Input: a = 12, b = 5, n = 4
Output: 98
Explanation: For x = 2, (a XOR x) = 14 and (b XOR x) = 7. Hence, (a XOR x) * (b XOR x) = 98. 
It can be shown that 98 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.

Example 2:
Input: a = 6, b = 7 , n = 5
Output: 930
Explanation: For x = 25, (a XOR x) = 31 and (b XOR x) = 30. Hence, (a XOR x) * (b XOR x) = 930.
It can be shown that 930 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.

Example 3:
Input: a = 1, b = 6, n = 3
Output: 12
Explanation: For x = 5, (a XOR x) = 4 and (b XOR x) = 3. Hence, (a XOR x) * (b XOR x) = 12.
It can be shown that 12 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.
*/


//07. NUMBER OF 1 BITS  
//APPROACH 1                                                            {T.C = O(N), S.C = O(1)}
/* 
check while(n != 0) if(n & 1) == 1 count++ and right shift(n = n >> 1), finally return count,
*/
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count= 0;
        while(n != 0){
            if(n & 1){                       //1.1 = 1 and 1.0 = 0
                count++;
            }
            n = n>>1;                        //right shift or moving to next position
        }
        return count;
    }
};

//APRROACH 2                                                      {T.C = O(LOGN), S.C = O(1)}
/*
Simply (decimal to binary logic) count += n % 2 and n = n/2, finally return count.
*/
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count= 0;
        while(n != 0){
            count += n % 2;
            n /= 2;
        }
        return count;
    }
};
/*
Example 1:
Input: n = 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

Example 2:
Input: n = 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.

Example 3:
Input: n = 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.
*/


//08. MINIMUM ONE BIT OPERATIONS TO MAKE INTEGERS ZERO                  {T.C = O(1), S.C = O(1)}
/*
Take a vector(long long) which stores no. of steps for all bit(31) by f[i] = 2*f[i-1]+1 now , take res and sign(use in formula to alternate)
take for loop from 30 to 0 , first find the i_th bit if bit is 1(set) and sign > 0 res += f[i] else res -= f[i] and reverse sign, finally
retun res.
*/
class Solution {
public:
    int minimumOneBitOperations(int n) {
        //base case
        if(n == 0){
            return 0;
        }

        vector<long long>f(31, 0);   //F[i] = no. of operation to convert a number (having i_th bit set(1)) to 0.
        f[0] = 1;                   //1 -> 0 = 1 step
        for(int i = 1 ; i < 31 ; i++){
            f[i] = 2*f[i-1] + 1;              //i_th bit = 2x+1(steps)        {x = i-1}
        }

        int res = 0, sign = 1;
        for(int i = 30 ; i >= 0 ; i--){   //set=>unset from left to right
            int i_th_bit = (n >> i) & 1;   //finding i_th bit
            if(i_th_bit == 0){
                continue;
            }
            if(sign > 0){                  //alternatings signs {1111 = f[3]-f[2]+f[1]-f[0]}
                res += f[i];
            }else{
                res -= f[i];
            }
            sign = sign*(-1);
        }
        return res;
    }
};
/*
Example 1:
Input: n = 3
Output: 2
Explanation: The binary representation of 3 is "11".
"11" -> "01" with the 2nd operation since the 0th bit is 1.
"01" -> "00" with the 1st operation.

Example 2:
Input: n = 6
Output: 4
Explanation: The binary representation of 6 is "110".
"110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
"010" -> "011" with the 1st operation.
"011" -> "001" with the 2nd operation since the 0th bit is 1.
"001" -> "000" with the 1st operation.
*/


//09. MAXIMUM NUMBER THAT SUM OF THE PRICES IS LESS THAN OR EQUAL TO K    
//BRUTE FORCE                                                     {T.C = O(K*LOGN), S.C = O(1)}
class Solution {
public:
    typedef long long ll;
    ll getPrice(ll num, int x){
        ll price = 0;
        while(num > 0){
            int value = (1 << (x-1) & num);           //finding i_th bit (1 index{x-1})
            if(value > 0){
                price += 1;
            }
            num = num >> x;                                 //right shift for removing bits from last
        }
        return price;
    }
    long long findMaximumNumber(long long k, int x) {
        ll num = 1;                                //numbers = 1, 2,3 ....
        ll sum = 0;

        while(true){
            ll price = getPrice(num, x);                     //logN
            if(sum + price <= k){
                sum += price;
            }else{
                break;
            }
            num++;
        }
        return num-1;                                //before num is correct sum(1 based index)
    }
};

//OPTIMIZED APPROACH                                         {T.C = O(LOGN), S.C = O(N)}
class Solution {
public:
    typedef long long ll;
    vector<ll> bitCount;

    void getBits(ll number) {
        if (number == 0)
            return;
        
        if (number == 1) {
            bitCount[0]++;
            return;
        }
        
        if (number == 2) {
            bitCount[0]++;
            bitCount[1]++;
            return;
        }

        ll bitLen          = log2(number);
        ll nearestPowerTwo = (1ll << bitLen);
        bitCount[bitLen]  += (number - nearestPowerTwo + 1);

        for (ll i = 0; i < bitLen; i++) {
            bitCount[i] += (nearestPowerTwo / 2);
        }

        number = number - nearestPowerTwo;
        getBits(number);
    }

    ll findMaximumNumber(ll threshold, int divisor) {
        ll low = 0, high = 1e15;
        
        ll result = 0;
        while (low <= high) {
            ll mid = low + (high - low) / 2;
            
            bitCount = vector<ll>(65, 0);
            
            getBits(mid);

            ll accumulatedCount = 0;
            
            for (ll i = 0; i < log2(mid)+1; i++) {
                if ((i + 1) % divisor == 0) 
                    accumulatedCount += bitCount[i];
            }

            if (accumulatedCount <= threshold) {
                result = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return result;
    }
};
/*
Example 1:
Input: k = 9, x = 1
Output: 6
Explanation: The numbers 1, 2, 3, 4, 5, and 6 can be written in binary representation as "1", "10", "11", "100", "101", and "110" respectively.
Since x is equal to 1, the price of each number is the number of its set bits.
The number of set bits in these numbers is 9. So the sum of the prices of the first 6 numbers is 9.
So the answer is 6.

Example 2:
Input: k = 7, x = 2
Output: 9
Explanation: Since x is equal to 2, we should just check eventh bits.
The second bit of binary representation of numbers 2 and 3 is a set bit. So the sum of their prices is 2.
The second bit of binary representation of numbers 6 and 7 is a set bit. So the sum of their prices is 2.
The fourth bit of binary representation of numbers 8 and 9 is a set bit but their second bit is not. So the sum of their prices is 2.
Numbers 1, 4, and 5 don't have set bits in their eventh bits in their binary representation. So the sum of their prices is 0.
The second and the fourth bit of the binary representation of the number 10 are a set bit. So its price is 2.
The sum of the prices of the first 9 numbers is 6.
Because the sum of the prices of the first 10 numbers is 8, the answer is 9.
*/
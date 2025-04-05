//SORTING ALGORITHM (COMPARISION BASED)
//PSUDO CODE

//01. BUBBLE SORT
//COMPARE SIDE VAL IF CURR GREATER THEN SWAP WITH SIDE (AT LAST WE GET BIGGEST VALUE)
/*
T.C = WRS (BIG-OH) = N^2
    = AVG (THETA)  = N^2
    = BES (OMEGA)  = N               (ARLREADY SORTED)
AUX SPACE = O(1)
ONLINE  = NOT
STABLE  = YES
INPLACE = YES
*/
for(int i = 0 ; i < n-1 ; i++){
    for(int j = 0 ; j < n-i-1 ; j++){
        if(arr[j] > arr[j+1]){
            swap(arr[j], arr[j+1]);
        }
    }
}


//02. SELECTION SORT
//MAINTAING 2 SUBARRAYS(SORTED AND UNSORTED)
//CHOOSE MIN ELEMENT THEN PUT IT FIRST THEN NEXT MIN ELE PUT NEXT
/*
T.C = WRS (BIG-OH) = N^2
    = AVG (THETA)  = N^2
    = BES (OMEGA)  = N^2             (DOESN'T MATTER ALREADY SORTED OR NOT)
AUX SPACE = O(1)
ONLINE  = NOT
STABLE  = NOT           (SWAPPING OF POSITION)
INPLACE = YES
*/
for(int i = 0 ; i < n-1 ; i++){
    int minIdx = i;
    for(int j = i+1 ; j < n ; j++){
        if(arr[j] < arr[minIdx]){
            minIdx = j;
        }
    }
    swap(arr[minIdx], arr[i]);
}


//INSERTION SORT
//MAINTAING 2 SUBARRAYS(SORTED AND UNSORTED)
//CHOOSE MIN ELEMENT THEN SHIFITING ELEMENT ONE BY ONE (UPGRADATION OF SELECTION SORT)
//
/*
T.C = WRS (BIG-OH) = N^2
    = AVG (THETA)  = N^2
    = BES (OMEGA)  = N               (ARLREADY SORTED)
AUX SPACE = O(1)
ONLINE  = YES (NEW ELEMENT CAN ENTER WITHOUT ANY RESTRICTION)
STABLE  = YES
INPLACE = YES
*/
for(int i = 1; i < n ; i++){
    key = arr[i];
    j = i-1;
    while(j >= 0 && arr[j] > key){
        arr[j+1] = arr[j];
        j = j-1;
    }
    arr[j+1] = key;
}


//MERGE SORT
//BEST FOR LINKED LIST(NOT REQUIRED EXTRA SPACE)
//SPLIT ARRAY IN TWO PARTS , THEN SORT INDIVIDUALLY AND FINALLY MERGE
/*
T.C = WRS (BIG-OH) = N*LOGN
    = AVG (THETA)  = N*LOGN
    = BES (OMEGA)  = N*LOGN               (DOESN'T MATTER ARRAY IS ARLREADY SORTED OR NOT)
AUX SPACE = O(N)     //SPACE REQUIRE
ONLINE  = NOT
STABLE  = YES
INPLACE = NOT
*/
void merge(vector<int>&arr, int low , int mid , int high){
    vector<int>temp;
    int left = low;                               //[low -------mid]
    int right = mid+1;                            //[mid+1 --- high]
    while(left <= mid && right <= high){
        if(arr[left] <= arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        //right is smaller
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }
    while(left <= mid){
        temp.push_back(arr[left]);
        left++;
    }
    while(right <= high){
        temp.push_back(arr[right]);
        right++;
    }

    //put anser in array
    for(int i = low ; i <= high ; i++){
        arr[i] = temp[i-low];
    }
}

int m = (l+r-1)/2;
mergeSort(arr, l, m);
mergeSort(arr, m+1, r);
merge(arr, l, m, r);


//QUICK SORT
//BEST FOR ARRAYS (RANDOM POINTERS)
//WE CHOOSE PIVOT AND ALL SMALLER ELE SHIFT TO PARTICULAR PIVOT AND BIGGER ELEMENT SHIFT ANOTHER SIDE OF PIVOT
/*
T.C = WRS (BIG-OH) = N^2
    = AVG (THETA)  = N*LOGN
    = BES (OMEGA)  = N*LOGN               
AUX SPACE = O(1)
ONLINE  = NOT
STABLE  = NOT (RANDOM PICK AND POSITION CHANGE)
INPLACE = YES
*/
int partition(int arr[], int low, int high){
    int pivot = low;
    int i=low;
    int j=high;
    
    while(i<j){
        while(arr[i]<=arr[pivot]){
            i++;
        }
        while(arr[j]>arr[pivot]){
            j--;
        }
        if(i<j){
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[j], arr[pivot]);
    return j;
}
int pi = partition(arr, low, high);
quickSort(arr, low, pi-1);
quickSort(arr, pi+1, high);


//HEAP SORT
//MAXHEAP- CHOOSE ROOT(MAX) AND SWAP WITH LAST ELEMENT AND REMOVE LAST(ACTUAL ROOT) {THEN BY HEAPIFY WE AGAIN MAKE TREE AS VALID TREE}
/*
T.C = WRS (BIG-OH) = N*LOGN
    = AVG (THETA)  = N*LOGN
    = BES (OMEGA)  = N*LOGN               (DOESN'T MATTER ARLREADY SORTED)
AUX SPACE = O(1)
ONLINE  = NOT
STABLE  = NOT  
INPLACE = YES
*/
for(int i = n/2-1 ; i >= 0 ; i--){
    heapify(arr, n, i);
    for(int i = n-1 ; i > 0 ; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
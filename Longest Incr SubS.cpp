class Solution{
    public:
    // return length of longest strictly increasing subsequence
    
    
    int longestSubsequence(int n, int a[])
    {
        
        int* arr = new int[n];
       
        // initialization step
        arr[0] = 1;
       
        // general step
        for (int i = 1; i < n; i++) {
            arr[i] = 1;
            for (int j = 0; j < i; j++) { 
                if ( a[i] > a[j] && arr[i] < arr[j] + 1) {
                    arr[i] = arr[j] + 1;
                }
            }
        }
        
        int max = -1;
        for (int i = 0; i < n; i++) {
            if (arr[i] > max) max = arr[i];
        }
        return max;
    }
};
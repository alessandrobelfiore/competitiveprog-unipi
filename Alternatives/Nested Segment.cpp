#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

int64_t getMid(int64_t s, int64_t e) { return s + (e -s)/2; } 

bool compareTuple(tuple<int64_t, int64_t, int> a, tuple<int64_t, int64_t, int> b) {
  return get<1> (a) > get<1> (b);
}
  
// A recursive function that constructs Segment Tree for array[ss..se].  
// si is index of current node in segment tree st  
int64_t constructSTUtil(int64_t arr[], int64_t ss, int64_t se, int64_t *st, int64_t si)  
{  
    // If there is one element in array, store it in current node of  
    // segment tree and return  
    if (ss == se)  
    {  
        st[si] = arr[ss];  
        return arr[ss];  
    }  
  
    // If there are more than one elements, then recur for left and  
    // right subtrees and store the sum of values in this node  
    int64_t mid = getMid(ss, se);  
    st[si] = constructSTUtil(arr, ss, mid, st, si*2+1) +  
            constructSTUtil(arr, mid+1, se, st, si*2+2);  
    return st[si];  
}  
  
/* Function to construct segment tree from given array. This function  
allocates memory for segment tree and calls constructSTUtil() to  
fill the allocated memory */
int64_t *constructST(int64_t arr[], int64_t n)  
{  
    // Allocate memory for the segment tree  
  
    //Height of segment tree  
    int64_t x = (int64_t)(ceil(log2(n)));  
  
    //Maximum size of segment tree  
    int64_t max_size = 2*(int64_t)pow(2, x) - 1;  
  
    // Allocate memory  
    int64_t *st = new int64_t[max_size];  
  
    // Fill the allocated memory st  
    constructSTUtil(arr, 0, n-1, st, 0);  
  
    // Return the constructed segment tree  
    return st;  
}

int64_t getSumUtil(int64_t *st, int64_t ss, int64_t se, int64_t qs, int64_t qe, int64_t si)  
{  
  // total overlap 
  if (qs <= ss && qe >= se)  
    return st[si];

  // no overlap
  if (se < qs || ss > qe)  
    return 0;  

  // partial overlap
  int64_t mid = getMid(ss, se);  
  return getSumUtil(st, ss, mid, qs, qe, 2*si+1) +  
    getSumUtil(st, mid+1, se, qs, qe, 2*si+2);  
} 

int64_t getSum(int64_t *st, int64_t n, int64_t qs, int64_t qe)  
{  
  // Check for erroneous input values  
  if (qs < 0 || qe > n || qs > qe)  
  {  
      cout<<"Invalid Input";  
      return -1;  
  }  

  return getSumUtil(st, 0, n-1, qs, qe, 0);  
}

/* A recursive function to update the nodes which have the given  
index in their range. The following are parameters  
    st, si, ss and se are same as getSumUtil()  
    i --> index of the element to be updated. This index is  
            in the input array.  
diff --> Value to be added to all nodes which have i in range */
void updateValueUtil(int64_t *st, int64_t ss, int64_t se, int64_t i, int64_t diff, int64_t si)  
{  
    // Base Case: If the input index lies outside the range of  
    // this segment  
    if (i < ss || i > se)  
        return;  
  
    // If the input index is in range of this node, then update  
    // the value of the node and its children  
    st[si] = st[si] + diff;  
    if (se != ss)  
    {  
        int64_t mid = getMid(ss, se);  
        updateValueUtil(st, ss, mid, i, diff, 2*si + 1);  
        updateValueUtil(st, mid+1, se, i, diff, 2*si + 2);  
    }  
}  
  
// The function to update a value in input array and segment tree.  
// It uses updateValueUtil() to update the value in segment tree  
void updateValue(int64_t arr[], int64_t *st, int64_t n, int64_t i, int64_t new_val)  
{  
    // Check for erroneous input index  
    if (i < 0 || i > n-1)  
    {  
        cout<<"Invalid Input";  
        return;  
    }  
  
    // Get the difference between new value and old value  
    int64_t diff = new_val - arr[i];  
  
    // Update the value in array  
    arr[i] = new_val;  
  
    // Update the values of nodes in segment tree  
    updateValueUtil(st, 0, n-1, i, diff, 0);  
}  


int main() {
  int n = 0;
  cin >> n;
  vector<tuple<int64_t, int64_t, int>> vect;
  vector<int> values;
  int size = 2 * n;

  for (int i = 0; i < n; i++) {
    int64_t l, r = 0;
    cin >> l;
    cin >> r;

    // store all values
    values.push_back(l);
    values.push_back(r);
    // store segments as tuples
    tuple<int64_t, int64_t, int> tmp = make_tuple(l, r, i);
    vect.push_back(tmp);
  }

  // order all values, in ascending order
  std::sort (values.begin(), values.end());

  // substitute bounds in tuples with their ranks
  for (int i = 0; i < n; i++) {
    get<0> (vect[i]) = std::lower_bound(values.begin(), values.end(), get<0> (vect[i])) - values.begin();
    get<1> (vect[i]) = std::lower_bound(values.begin(), values.end(), get<1> (vect[i])) - values.begin();
  }

  // sort segments by right margin, decrementally
  std::sort(vect.begin(), vect.end(), compareTuple);

  int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * size);
  int64_t* res = (int64_t*) malloc(sizeof(int64_t) * n);

  // initialize an array of dim size
  for (int i = 0; i < size; i++) {
    arr[i] = 0;
  }

  // store the number of segments starting at each index
  for (int i = 0; i < n; i++) {
    arr[get<0>(vect[i])] ++;
  }

  // construct segment tree to maintain number of starting segments
  int64_t* st = constructST(arr, size);

  for (int i = 0; i < n; i++) {
    res[get<2> (vect[i])] = getSum(st, size, get<0>(vect[i]) + 1, get<1> (vect[i]));
    updateValue(arr, st, size, get<0>(vect[i]), 0);
  } 

  for (int i = 0; i < n; i++) {
    cout << res[i] << endl;
  }
}
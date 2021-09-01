/* There is one meeting room in a firm. There are N meetings 
    in the form of (start[i], end[i]) where start[i] is start time of meeting i 
    and end[i] is finish time of meeting i. We have to find the maximum number of meetings possible.
    We simply order them by increasing ending time and select greedily if the 
    starting time does not conflict with the previous meetings.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution{
    public:
        int maxMeetings(int start[], int end[], int n) {
        // Your code here
        
        // build a vector of pairs(ending, index)
        std::vector<std::pair<int, int>> orderedEnds;
        orderedEnds.reserve(n);
        for (int i = 0; i < n; i ++) {
            pair<int, int> tmp = make_pair(end[i], i);
            orderedEnds.push_back(tmp);
        }
        
        // order from the smallest ending
        std::sort(orderedEnds.begin(), orderedEnds.end(),
            [ ]( const pair<int, int>& lhs, const pair<int, int>& rhs )
                {
                    return lhs.first < rhs.first;
                });
        
        // select greedily
        int bound = -1;
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (start[orderedEnds[i].second] > bound) {
                result ++;
                bound = end[orderedEnds[i].second];
            }
        }
        return result;   
        }
};
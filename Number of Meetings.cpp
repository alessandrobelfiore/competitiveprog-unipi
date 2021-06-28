class Solution{
    public:
        int maxMeetings(int start[], int end[], int n) {
        // Your code here
        
        // build a vector of pairs(ending, index)
        std::vector<std::pair<int, int>> orderedEnds;
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
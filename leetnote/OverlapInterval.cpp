// 移除区间的最小数量，使剩余区间互不重叠
// 按照区间最大值进行排序, 区间越小则剩余空间越大
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) {
        return 0;
    }
    int size = intervals.size();
    sort(intervals.begin(), intervals.end(),
         [](vector<int> a, vector<int> b) { return a[1] < b[1]; });
    int total, pre = intervals[0][1];
    for (unsigned int i = 1; i < size; ++i) {
        if (intervals[i][0] < pre) {
            ++ total;
        }else{
            pre = intervals[i][1];
        }
    }
    return total;
}
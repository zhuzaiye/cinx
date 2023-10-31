// 数组交集
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> intersect2(vector<int>& nums1, vector<int>& nums2) {
    int len1 = nums1.size(), len2 = nums2.size();
    
    vector<int> minNums = len1 < len2 ? nums1 : nums2;
    vector<int> maxNums = len1 < len2 ? nums2 : nums1;

    unordered_map<int, int> hashMap;
    for (int num: minNums) {
        ++ hashMap[num];
    }

    vector<int> intersection;
    for (int num: maxNums) {
        if (hashMap.count(num)) {
            intersection.push_back(num);
            --hashMap[num];
            if(hashMap[num] == 0) {
                hashMap.erase(num);
            }
        }
    }

    return intersection;
}
// Add Two Sum 未排序
#include <iostream>
// 数组
#include <vector>
// map
#include <map>
// 引入工具头文件
#include "utils.h"

using namespace std;

vector<int> twoSumAdd(vector<int>& nums, int target) {
    map<int, int> calcMap;
    for (int i = 0; i < nums.size(); i++) {
        int sub = target - nums[i];
        if (calcMap.count(sub) != 0) {
            return vector<int>{calcMap[sub], i};
        }
        calcMap[nums[i]] = i;
    }
    // 默认输出[0, 0] 未匹配到 应该不会
    return vector<int>{0, 0};
}

int main(int argc, char const* argv[]) {
    vector<int> nums = {2,7,11,15};
    int target = 9;

    vector<int>  rst = twoSumAdd(nums, target);

    printVector(rst);
    return 0;
}
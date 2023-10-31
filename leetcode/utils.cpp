#include <iostream>  // 打印
#include <vector>    // 数组

void printNumVector(std::vector<int>& intNums) {
    for (unsigned int i = 0; i < intNums.size(); ++i) {
        std::cout << intNums[i] << " ";
    }
    std::cout << std::endl;
}

int binaryNumSearch(std::vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midNum = nums.at(mid);
        if (midNum == target) {
            return mid;
        }
        if (midNum > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

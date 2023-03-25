#include <iostream>  // 打印
#include <vector>    // 数组

void printVector(std::vector<int>& intNums) {
    for (unsigned int i = 0; i < intNums.size(); ++i) {
        std::cout << intNums[i] << " ";
    }
    std::cout << std::endl;
}
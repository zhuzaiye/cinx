// 数组
#include <iomanip>
#include <iostream>

int main() {
    int a[5];
    int b[] = {1, 2, 3, 4, 5};
    std::cout << "Cout inited slice: \n";
    for (int i = 0; i < 5; i++) {
        std::cout << b[i] << std::setw(4);
    }

    std::cout << "\nPlease input 5 number: \n";
    for (int i = 0; i < 5; i++) {
        std::cin >> a[i];
    }
    
    std::cout << "Convert into: \n";
    for (int i = 4; i >= 0; i--) {
        // std::cout << a[i] << "\t";
        // std::cout << std::setw(4) << a[i];
        std::cout << a[i];
        std::cout.width(4);
    }
}
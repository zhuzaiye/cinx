// 辗转相除法 获取最大公约数(GCD)和最小公倍数(LCM)
#include <iostream>

// void  main 编译失败?
int main() {
    int a, b, num1, num2, temp;

    std::cout << "please enter 2 numers: " << std::endl;
    std::cin >> num1 >> num2;
    // 变量互换
    if (num1 > num2) {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    a = num1;
    b = num2;
    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }

    std::cout << "GCD: " << a << std::endl;
    std::cout << "LCM: " << num1 * num2 / a << std::endl;

    return 0;
}
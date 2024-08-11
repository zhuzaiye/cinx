// 重载
#include <iostream>

// 函数原型声明
// 函数重载
int add(int, int);
double add(double, double);
int add(int, int, int);

int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1.3, 2.2) << std::endl;
    std::cout << add(1, 2, 3) << std::endl;
    return 0;
}

int add(int x, int y) {
    return x + y;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return add(a, b) + c;
}

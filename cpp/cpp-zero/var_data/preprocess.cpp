// 预处理
// #include
// #define
// #if #ifndef #ifdef #endif

#include <iostream>

// #define M (y * y + 3 * y)  // 注意括号的作用
#define PI 3.14

double length(double);

int main() {
    double r, s, l;
    std::cout << "Enter radius: " << std::endl;
    std::cin >> r;
    s = PI * r * r;
    l = length(r);
    std::cout << "area: " << s << std::endl;
    std::cout << "len: " << l << std::endl;

    return 0;
}

// 取消宏定义
#undef PI

double length(double r) {
#ifdef PI
    return 2 * PI * r;
#else
    return 3.1415 * 2 * r;
#endif
}

// 结构体通过运算符重载实现定义自身的运算行为
#include <iostream>
using namespace std;

// 定义一个结构体
struct Point {
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    void operator()() { cout << "sum: " << x + y << endl; }
};

// 重载"+"运算符
Point operator+(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}

// 重载"-"运算符
Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

// 重载"<<"运算符
ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

int main() {
    Point a(1, 2), b(3, 4);
    Point c = a + b;
    Point d = b - a;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "a+b=" << c << endl;
    cout << "b-a=" << d << endl;
    return 0;
}
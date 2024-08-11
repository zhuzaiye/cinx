#include <iostream>

using namespace std;

// stuct vs class
/**
// struct 中所有成员默认都是public
class 中成员默认时private
struct point {
  // 属性
  int x;
  int y;
  // 成员函数
  void print() {
    cout << "pt.x= " << x << endl;
    cout << "pt.y= " << y << endl;
  }
};
*/

class Point {
// class 默认是private, 只能自身访问
public:
  int x;
  int y;

  void print() {
    cout << "pt.x= " << x << endl;
    cout << "pt.y= " << y << endl;
  }
};

int main() {
  Point pt;
  // Implicitly declared private here
  // 需要增加public:
  pt.x = 0;
  pt.y = 1;

  pt.print();
}


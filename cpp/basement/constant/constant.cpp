#include <iostream>
using namespace std;

extern int ext1;  // auto init?? initial==0?
extern const int ext2;  // 引用other.cpp的const 变量

int main(void) {
    cout << "defualt extern parameter ext1: " << ext1+10 << endl;
    cout << "manual extern parameter ext2: " << ext2 << endl;

    return 0;
}
#include <iostream>
using namespace std;

extern int ext1;  // auto init?? initial==0?
extern const int ext2;  // 引用other.cpp的const 变量

void constExtern(void) {
    cout << "defualt extern parameter ext1: " << ext1+10 << endl;
    cout << "manual extern parameter ext2: " << ext2 << endl;
}

void constPointer() {
    // const type *var: *var 是不可变的  指向常量指针
    cout << "---- 指向常量指针 ----" << endl;
    int var = 10, var1=11;
    const int *ptr1 = &var;  // ptr1 不用初始化
    cout << "The initial ptr1: " << ptr1 << " value: " << *ptr1 << endl;
    // *ptr1 = var1;
    ptr1 = &var1;
    cout << "The reset ptr1: " << ptr1 << " value: " << *ptr1 << endl;
    
    cout << "---- 常量指针 ----" << endl;
    // type * const var: var 是不可变的  常量指针
    int * const ptr2 = &var; // 需要初始化ptr2
    cout << "The initial ptr2: " << ptr2 << " value: " << *ptr2 << endl;
    // ptr2 = &var1;
    *ptr2 = var1;
    cout << "The reset ptr2: " << ptr2 << " value: " << *ptr2 << endl;
    // *ptr2 是一个一般变量，以下为错误
    const int var2 = 12;
    // int * const ptr3 = &var2;  // 致使*ptr3为常量, 类型不一致 const int *" 类型的值不能用于初始化 "int *const" 类型的实体
    const int *ptr3 = &var2;
    cout << "The initial ptr3: " << ptr3 << " value: " << *ptr3 << endl;

    // const type * const var: *var和var 是不可变的
}

int main(void) {
    // constExtern();
    constPointer();
    return 0;
}
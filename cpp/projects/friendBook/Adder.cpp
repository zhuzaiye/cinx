// Add.cpp
#include "Adder.h"

#include <fstream>
#include <iostream>

using namespace std;

Friend Adder::newFriend() {
    // 实例化Friend
    Friend frd;

    cout << "Name: ";
    cin >> frd.name;
    cout << "Age: ";
    cin >> frd.age;
    cout << "Phone: ";
    cin >> frd.phone;

    return frd;
}

int Adder::saveFriend() {
    Friend frd = newFriend();
    // stream 流 即内存
    // fstream有两个子类: ifstream(input file stream)和ofstream(outpu file
    // stream)
    // ifstream默认以输入方式打开文件
    // ofstream默认以输出方式打开文件
    ofstream ofs;
    // void open(const char* filename,int mode,int access);
    // int mode
    // ios::app 追加方式打开文件
    // ios::ate 文件打开后定位到文件尾，ios:app就包含有此属性
    // ios::in 文件以输入方式打开--文件数据输入到内存
    // ios::out 文件以输出方式打开--内存数据输出到文件
    // ios::trunc 如果文件存在，把文件长度设为0
    // int access
    // 0 普通文件 打开访问
    // 1 只读文件
    // 2 隐含文件
    // 4 系统文件
    ofs.open("friendbook.txt", ios::out | ios::app);
    // << 输入流
    // >> 流输出
    ofs << frd.name << " " << frd.age << " " << frd.phone << endl;
    cout << "add success!" << endl;
    ofs.close();
    
    return 0;
}
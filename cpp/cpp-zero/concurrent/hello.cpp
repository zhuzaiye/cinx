#include <iostream>
// 引入线程thread头文件
#include <thread>


void hello() {
    std::cout << "Hello concurrent world\n";
}

int main() { // initial thread 应用级起始线程
    std::thread t(hello); // thread启动新的线程, 从hello开始 
    t.join();  // 主线程等待子线程结束后再结束
}
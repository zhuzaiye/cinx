# 并发编程

> `并行`更加注重性能,使用硬件提高数据处理速度时，会讨论程序的并行性。  
> 当关注重点在于任务分离或任务响应时，会讨论程序的`并发`性

## 从Hello代码开始

```cpp
#include <iostream>
#include <thread> // 多线程库引入

void hello() {
    std::cout << "Hello Concurrent World\n";
}

int main() {
    std::thread t(hello); // 创建hello执行函数
    t.join(); // 主线程等待hello线程
}
```

## 线程管理

> 1. 启动新线程  
> 2. 等待与分离  
> 3. 唯一标识符  


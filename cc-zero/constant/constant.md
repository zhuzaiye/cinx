# const

## 作用

- 类型检查
- 防止修改
- 节省内存

## const的域

- 不同文件，const属于当前文件的局部变量，需要通过`extern`提升域
- 非const变量 自动extern

```cpp
// other.cpp
int ext1;                   // default extern
extern const int ext2 = 0;  // manual extern and init const parameter

// constant.cpp
#include <iostream>
using namespace std;

extern int ext1;  // auto init?? initial==0?
extern const int ext2;  // 引用other.cpp的const 变量

int main(void) {
    cout << "defualt extern parameter ext1: " << ext1+10 << endl;
    cout << "manual extern parameter ext2: " << ext2 << endl;

    return 0;
}
```

## const & pointer

- 如果const位于*的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量；
- 如果const位于*的右侧，const就是修饰指针本身，即指针本身是常量。

```cpp
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
    int * const ptr3 = &var2;  // // 致使*ptr3为常量, 类型不一致 const int *" 类型的值不能用于初始化 "int *const" 类型的实体
    cout << "The initial ptr3: " << ptr3 << " value: " << *ptr3 << endl;
    // const type * const var: *var和var 是不可变的
}
```

```s
---- 指向常量指针 ----
The initial ptr1: 0x61fdc4 value: 10
The reset ptr1: 0x61fdc8 value: 11

---- 常量指针 ----
The initial ptr2: 0x61fdc4 value: 10
The reset ptr2: 0x61fdc4 value: 11
The initial ptr3: 0x61fdcc value: 12
```

## const & function

面试问题：

1. 如果函数需要传入一个指针，是否需要为该指针加上const，把const加在指针不同的位置有什么区别？
2. 如果写的函数需要传入的参数是一个复杂类型的实例，传入值参数或者引用参数有什么区别，什么时候需要为传入的引用参数加上const？

```cpp
// 参数指针所指内容为常量不可变
// *src 内容不会被strcpy修改
void strcpy(char *dst, const char *src);

// 参数为引用，为了增加效率同时防止修改
// “引用传递”仅借用一下参数的别名，不需要产生临时对象
void func(const A &a);
```

## const & class

```cpp
// 在类的成员函数后面可以加const关键字，则该成员函数成为常量成员函数
class Sample
{
public:
    void GetValue() const; // 常量成员函数
    void func();
    int m_value;
};

void Sample::GetValue() const // 常量成员函数
{
    value = 0; // 出错
    func();    // 出错
}

int main()
{
    const Sample obj; // 常量对象
    obj.value = 100;  // 出错,常量对象不可以被修改
    obj.func();       // 出错,常量对象上面不能执行非常量成员函数
    obj.GetValue();   // 证明的是const对象只能访问const成员函数

    return 0;
}
```

## [Makefile](https://makefiletutorial.com/)

![compile procssor](../assets/compile_processor.png)

1. 预处理(pre-process):
   
   ```sh
   cpp hello.c > hello.i
   # 导入#include头文件
   # 导入#define宏定义
   ```
2. 编译(compile)

    ```sh
    gcc -S hello.i
    # 将预处理后文件编译成汇编程序
    ```
3. 汇编(assemble)

    ```sh
    as -o hello.o hello.s
    # 将汇编程序转换成目标文件，二进制格式
    # 每一个源文件修需要产生一个目标文件
    ```
4. 链接(link)

    ```sh
    ld -o hello hello.o ...
    # 将目标文件链接成可行程序
    ```

[A Simple Makefile Tutorial](https://cs.colby.edu/maxwell/courses/tutorials/maketutor/)

```Makefile
CC=gcc
CFLAGS=-I.
DEPS = hellomake.h
OBJ = hellomake.o hellofunc.o 

# $@ 指代 %.o 即:左边的内容
# $< 指代 $(DEPS)依赖列表的第一个项
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# $^ 指代: 右边所有项
hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
```
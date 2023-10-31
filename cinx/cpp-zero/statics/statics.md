# satic

## staic & function

变量声明为static时，空间将在程序的`生命周期内`分配

每次调用函数时，都不会对变量计数进行初始化.

```cpp
void demo() {
    // static variable
    static int count = 0;
    cout << count << " ";

    // value is updated and
    // will be carried to next
    // function calls
    count++;
}

int main() {
    for (int i = 0; i < 5; i++) {
        demo();
    }

    return 0;
}
// print: 0 1 2 3 4
```

## static & class

- 声明为static的变量只被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量由对象共享。
- 对于不同的对象，不能有相同静态变量的多个副本。因此，静态变量不能使用构造函数初始化

```cpp
// static 变量
class Apple {
   public:
    static int i;
};

// int Apple::i = 1; undefined reference to `Apple::i`
int Apple::i = 1; 

int main() {
    Apple obj1;
    Apple obj2;
    obj1.i = 2;
    obj2.i = 3;

    // prints value of i
    cout << obj1.i << " " << obj2.i;

    return 0;
}
// 3 3
// obj1 obj2 不会构造或初始化Apple static
```

```cpp
// 静态对象的范围是贯穿整个程序的生命周期
// 因此静态类对象
class Apple {
    int i;

   public:
    Apple() {
        i = 0;
        cout << "Inside Constructor\n";
    }
    ~Apple() { cout << "Inside Destructor\n"; }
};

int main() {
    int x = 0;
    if (x == 0) {
        static Apple obj;
    }
    cout << "End of main\n";
}
// Inside Constructor
// End of main
// Inside Destructor  main renturn才会析构对象
```
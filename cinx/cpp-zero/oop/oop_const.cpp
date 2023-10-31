#include <iostream>
using namespace std;

class R {
   public:
    R(int r1, int r2) {
        R1 = r1;
        R2 = r2;
    }
    void print();
    // 常成员函数说明格式：类型说明符  函数名（参数表）const;
    void print() const;  // const 用于函数重载区分
    void setR1(int r1);
   private:
    int R1, R2;
};

void R::print() {
    cout << "general func call" << endl;
    cout << R1 << " " << R2 << endl;
}

// const 重载函数的具体逻辑处理
void R::print() const {
    cout << "const func call" << endl;
    cout << R1 << " " << R2 << endl;
}

void R::setR1(int r1) {
    R1 = r1;
}

//常引用做形参，在函数中不能更新 r所指向的对象。
void display(const double& r) { cout << r << endl; }

int main() {
    R a(5, 4);
    a.print();  // call general func

    // const对象实例才能调用其const方法
    // 常对象只能调用它的常成员函数
    const R b(55, 44);
    b.print();

    cout << "-----------" << endl;

    double d(5.5);
    display(d);

    R const c(1, 2);
    c.print();
    // c实例是常对象, 不能被更新
    // c.setR1(3);
    // c.print();

    return 0;
}

/*
    $ ./oopMake.exe
    general func call
    5 4
    const func call
    55 44
    -----------
    5.5
    const func call
    1 2

*/
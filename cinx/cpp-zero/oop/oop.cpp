#include <iostream>
#include <string>

using namespace std;

// 单一继承
class Father {
public:
  // Default constructor of 'Son' is implicitly deleted because base class
  // 'Father' has no default constructor
  // 如果父类有参构造, 字类不能通过默认构造, 需要调用父类有参构造
  //   Father(string _name) : name(_name) { cout << "Father " << name << endl;
  //   };
  // 如果显式表明无参构造, 其子类可以使用默认构造
  //   Father(){};

  ~Father() { cout << "~Father" << endl; };
  string name = "father";
  int age = 45;
};

class Son : public Father {
public:
  //   Son(string _name) : Father(_name) { cout << "Son: " << name << endl; };
  string sex = "male";
  string name = "son";

  ~Son() { cout << "~Son" << endl; };

  void print() {
    cout << "name " << Father::name << " name_son " << name << " age " << age
         << " sex " << sex << endl;
  }
};

// 多继承和菱形继承
class A {
public:
  string name;
};

class B : public A {
public:
  int age;
};

class C : public A {
public:
  string sex;
};

class D : public B, public C {
public:
  int id;
};

// 拷贝构造函数- 默认构造函数
class Complex {
public:
  Complex(){};
  double real, imag;

  Complex(double _real, double _imag) : real(_real), imag(_imag) {
    cout << "real: " << real << " imag: " << imag << endl;
  }

  void print() { cout << "real:" << real << " imag:" << imag << endl; }

  Complex(const Complex &c) {
    real = c.real;
    imag = c.imag;
    cout << "compex copy" << endl;
  }

  // 重载
  friend Complex operator+(const Complex &c1, const Complex &c2);
};

Complex operator+(const Complex &c1, const Complex &c2) {
  Complex _c;
  _c.real = c1.real + c2.real;
  _c.imag = c1.imag + c2.imag;
  return _c;
}

// void func(Complex& c) {
//   cout << "real: " << c.real << " imag: " << c.imag << endl;
// }

Complex func1() {
  Complex c(1.0, 2.0);
  return c;
}

Complex func2() {
  Complex c(1.0, 2.0);
  Complex c1(2.0, 3.0);
  Complex c2 = c + c1;
  return c2;
}

int main() {
  // ---------
  //   Son son;
  //   son.print();

  //   cout << "----------" << endl;

  //   D d;
  /*
  d.name = "Peter"; 因为B,C都继承自A, 直接赋值不知如何向上继承查找

  Non-static member 'name' found in multiple base-class subobjects of type 'A':
    class D -> B -> A
    class D -> C -> Aclang(ambiguous_member_multiple_subobjects)
  */

  // 1. 明确指出通过谁进行向上继承查找
  //   d.B::name = "Peter";
  // 2. 通过虚继承 class B : virtual A; class C : virtual A;
  // 结论最好不要出现菱形继承或者尽可能避免多继承

  //---------- 默认拷贝构造函数赋值 ------
  //   Complex c1(1.0, 2.0);
  //   func(c1);

  Complex cc = func1();
  cc.print();

  return 0;
}

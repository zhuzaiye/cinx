# 面向对象编程

> 相似内部状态和行为的实体集合, 是为`类`.
>
> `g++ -g -Wall -O2 -o exe_run source.cpp -I.`
>

## 面向对象

1. 属性和行为统称为


## 构造拷贝

- 用一个对象去初始化同类的另一个对象时
  
  ```cpp
  class Complex {
	public:
	double real, imag;
	Complex(double _real, double _imag) : real(_real), imag(_imag) {
		cout << "real: " << real << " imag: " << imag << endl;
	}
	void print() { cout << "real: " << real << " imag: " << imag << endl; }
  };

  void func(Complex c) {
    cout << "real: " << c.real << " imag: " << c.imag << endl;
  }

  Complex c1(1.0, 2.0);
  Complex c2(c1); // 用一个对象去初始化同类的另一个对象
  Complex c2 = c1; // 也可以实现同类对象初始化, 这个不是赋值语句, 仅仅是初始化语句 

  func(c1); // 调用默认拷贝构造
  ```

- 对象作为函数参数是, 会触发对象的拷贝构造
  
  ```cpp
  class Complex {
	public:
	double real, imag;
	Complex(double _real, double _imag) : real(_real), imag(_imag) {
		cout << "real: " << real << " imag: " << imag << endl;
	}
	Complex(Complex& c) {
		real = c.real+1, imag = c.imag+1;
		cout << "compex copy" << endl;
	}
	//   void print() { cout << "real: " << real << " imag: " << imag << endl; }
  };

  void func(Complex c) {
	    cout << "real: " << c.real << " imag: " << c.imag << endl;
  }

  Complex c1(1.0, 2.0);
  func(c1); // 这个会存在复制构造函数初始化, 带来时间小号, 使用对象引用不会调用复制构造问题
  
  // 对象的引用而不是对象作为形参
  void func(Complex& c){
	cout << "real: " << c.real << " imag: " << c.imag << endl;
  }

  // 以引用作为形参有一定的风险，因为这种情况下如果形参的值发生改变，实参的值也会跟着改变。 最好的方法就是将函数形参声明为const类型的引用
  // 为什么函数形参声明为const类型的引用就不会发送形参改变引发实参改变了呢???
  void func(const Complex& c){
	cout << "real: " << c.real << " imag: " << c.imag << endl;
  }
  ```

- 对象作为返回值, 也会触发复制拷贝
  
  ```cpp
  class Complex {
	public:
	double real, imag;
	Complex(double _real, double _imag) : real(_real), imag(_imag) {
		cout << "real: " << real << " imag: " << imag << endl;
	}
	Complex(Complex& c) {
		real = c.real+1, imag = c.imag+1;
		cout << "compex copy" << endl;
	}
	void print() { cout << "real: " << real << " imag: " << imag << endl; }
  };

  void func(Complex& c) {
	cout << "real: " << c.real << " imag: " << c.imag << endl;
  }
	// 这里需要明确一个问题, 作为返回值, Complex中的复制构造Complex(Complex& c)不能存在, 为什么???
	// 需要显式生命默认构造函数
   Complex func1() {
		Complex c(1.0, 2.0);
		return c;
   }
  ```

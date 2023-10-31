// 自定义数据结构类型
// struct, typedef, class

#include <cstring>
#include <iostream>
#include <string.h>

using namespace std;

struct student {
  char name[20];
  float semesterGrades[5];
  float gpa;
};

typedef float dollars;

class Student {
public:
  char name[20];
  float semesterGrades[5];
  dollars gpa;
};

int main() {
  student stu1;
  strcpy(stu1.name, "Georhe Katz");
  stu1.semesterGrades[0] = 3.0;
  stu1.semesterGrades[1] = 4.0;
  stu1.gpa = 3.5;

  cout << "Struct-New Student: " << stu1.name
       << " Grade1: " << stu1.semesterGrades[0] << " gpg: " << stu1.gpa << endl;

  Student stu2;
  strcpy(stu2.name, "JoeLang");
  stu2.semesterGrades[0] = 5.0;
  stu2.gpa = 4.5;

  cout << "Class-New Student: " << stu1.name
       << " Grade1: " << stu1.semesterGrades[0] << " gpg: " << stu1.gpa << endl;

  return 0;
}
// 字符串
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
    char ch1[] = "Welcome";  // 定义字符串
    char ch2[64];
    strcpy(ch2, ch1);
    printf("ch2-> %s; ch1-> %s\n", ch2, ch1);

    char ch3[64];
    strcpy(ch3, "This is a string");
    printf("ch3-> %s\n", ch3);

    char str1[] = {"Hi "};
    char str2[] = {"Joe ~~~"};
    printf("out: %s\n", strcat(str1, str2));

    return 0;
}
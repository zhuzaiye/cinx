// Searcher.cpp
#include "Searcher.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

char *strcasestr(const char *str, const char *pattern) {
    size_t i;
    unsigned char c0 = *pattern, c1, c2;

    if (c0 == '\0') {
        return (char *)str;
    }

    c0 = toupper(c0);
    for (; (c1 = *str) != '\0'; str++) {
        if (toupper(c1) == c0) {
            for (i = 1;; i++) {
                c2 = pattern[i];
                if (c2 != '\0') return (char *)str;
                c1 = str[i];
                if (toupper(c1) != toupper(c2)) break;
            }
        }
    }
    return NULL;
}

int Searcher::getFriendCount() {
    ifstream ifs;
    ifs.open("friendbook.txt", ios::in);
    char tmp[50];
    int count = 0;
    // ifstream getline(char* s, size_t n);
    // 连续以行为单位, 逐行读取
    while (ifs.getline(tmp, 50)) {
        count++;
    }
    ifs.close();
    return count;
}

void Searcher::file2Array(Friend *friends) {
    ifstream ifs;
    ifs.open("friendbook.txt", ios::in);
    char tmp[50];
    int index = 0;
    while (ifs.getline(tmp, 50)) {
        // char *strtok(char *str, const char *delim)
        // 分解字符串 str 为一组字符串，delim 为分隔符
        char *token = strtok(tmp, " ");
        strcpy(friends[index].name, token);

        token = strtok(NULL, " ");
        friends[index].age = atoi(token);

        token = strtok(NULL, " ");
        strcpy(friends[index].phone, token);

        index++;
    }
}

void Searcher::setKey(char *keyWord) {
    cout << "Enter new key: ";
    cin >> keyWord;
}

void Searcher::printFriends(Friend *friends, int count) {
    cout << "######################" << endl;
    cout << "Name"
         << "\t"
         << "Age"
         << "\t"
         << "Phone" << endl;
    for (int i = 0; i < count; i++) {
        cout << friends[i].name << "\t";
        cout << friends[i].age << "\t";
        cout << friends[i].phone << endl;
    }
}

int Searcher::searchFriend(int flag) {
    int friendCount = getFriendCount();
    Friend *friends = new Friend[friendCount];
    file2Array(friends);

    if (flag == 1) {
        printFriends(friends, friendCount);
        return 0;
    }
    if (flag == 0) {
        char keyWord[10];
        setKey(keyWord);

        Friend *matchedFriends = new Friend[friendCount];
        int indexOfMatched = 0;
        for (int i = 0; i < friendCount; i++) {
            // char *strcasestr(const char *haystack, const char *needle);
            // strcasestr函数在"子串"与"父串"进行比较的时候，"不区分大小写"
            if (strcasestr(friends[i].name, keyWord) != NULL) {
                matchedFriends[indexOfMatched] = friends[i];
                indexOfMatched++;
            }
        }

        if (indexOfMatched == 0) {
            cout << "Not Find The Key Frien: " << keyWord << endl;
            return 0;
        }
        printFriends(matchedFriends, indexOfMatched);
    }
    return 0;
}
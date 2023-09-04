// main.cpp
#include "main.h"

#include "Adder.h"
#include "Searcher.h"

int main(void) {
    getIndex();

    while (true) {
        char opCmd = '?';
        opCmd = getCmd();

        switch (opCmd) {
            case 'a':
                // add
                cout << "Add New Friend" << endl;
                Adder adder;
                adder.saveFriend();
                break;
            case 's':
                // search
                cout << "Search Friend using key_word" << endl;
                Searcher searcher;
                searcher.searchFriend(0);
                break;
            case 'l':
                // list
                cout << "List All Added Friend" << endl;
                Searcher printer;
                printer.searchFriend(1);
                break;
            case '?':
                // to index
                cout << "Back to Index" << endl;
                getIndex();
                break;
            case 'q':
                // quit app
                cout << "Bye Bye..." << endl;
                return 0;
            default:
                // error command intro
                cout << "Please enter 'a/s/l/?/q' single command" << endl;
                break;
        }
    }

    return 0;
}

void getIndex() {
    cout << "\n\n==============================" << endl;
    cout << "Operation Command:)" << endl;
    cout << "\n------------------------------" << endl;
    cout << "a: Add New Friend" << endl;
    cout << "s: Search Your Friend" << endl;
    cout << "l: List Your Friend" << endl;
    cout << "------------------------------\n" << endl;
    cout << "Enter 'asl' To Index." << endl;
    cout << "Enter '?' To Index." << endl;
    cout << "Enter 'q' Quit Application'." << endl;
    cout << "==============================" << endl;
}

char getCmd() {
    cout << "\nPlease show your operation: ";
    char opCmd = '?';
    cin >> opCmd;
    return opCmd;
}
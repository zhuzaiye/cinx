// Searcher.h
#include "Friend.h"

class Searcher {
   public:
    int getFriendCount();
    void file2Array(Friend *friends);
    void setKey(char *keyWord);
    int searchFriend(int flag);
    void printFriends(Friend *friends, int count);
};
#include <algorithm>  // std::sort
#include <iostream>   // std::cout
#include <vector>     // std::vector

using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s) {
    // 给g剩余项中最小项gi匹配s中最小的大于等于gi的si
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    //  warning: comparison of integer expressions of different signedness:
    //  'int' and 'std::vector<int>::size_type'
    // int child =0, cookie=0; 
    // 使用 vector<int>::size_type 或者std::size_t
    vector<int>::size_type child = 0, cookie = 0;
    while (child < g.size() && cookie < s.size()) {
        if (g[child] <= s[cookie]) {
            ++child;
        }
        ++cookie;
    }
    return child;
}

int main(int argc, char const* argv[]) {
    vector<int> children = {1, 2};
    vector<int> cookies = {1, 2, 3};

    int maxFedChilds = findContentChildren(children, cookies);
    cout << "The maximum fed child is: " << maxFedChilds << endl;
    return 0;
}

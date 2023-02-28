// 最小分配糖果数量
// 每个孩子至少分配到 1 个糖果
// 相邻两个孩子评分更高的孩子会获得更多的糖果
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int CandyCount(vector<int>& ratings) {
    int len = ratings.size();
    if (len < 2) {
        return len;
    }
    vector<int> num(len, 1);
    // 从左往右，如果右边大于左边, 右边=左边+1
    for (int i = 1; i < len; i++) {
        if (ratings[i] > ratings[i - 1]) {
            num[i] = num[i - 1] + 1;
        }
    }
    // 从右往左, 如果左边大于右边, 左边=max(左边，右边)
    for (int i = len - 1; i > 0; --i) {
        if (ratings[i] < ratings[i - 1]) {
            num[i - 1] = max(num[i - 1], num[i] + 1);
        }
    }

    return accumulate(num.begin(), num.end(), 0);
}

int main(int argc, char const *argv[])
{
    vector<int> ratings = {1, 0, 2};
    int candyCnt = CandyCount(ratings);
    cout << "The minmum candy count: " << candyCnt << endl;
    return 0;
}

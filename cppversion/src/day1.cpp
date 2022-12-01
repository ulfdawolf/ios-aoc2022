#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

#include "common.h"

#include "day1_input.h"

using namespace std;
using namespace common;

int main()
{
    auto input = ParseNumbersList(input1);
    uint64_t max = 0;
    std::vector<int64_t> sums = {};

    for (const auto& numbers : input) {
        auto sum = std::reduce(numbers.begin(), numbers.end(), (int64_t)0);
        sums.push_back(sum);
    }

    std::sort(sums.begin(), sums.end(), greater<int64_t>());
    auto top1 = sums[0];
    auto top3 = std::reduce(sums.begin(), sums.begin()+3, (int64_t)0);
    cout << "Top1 elf calories: " << top1 << endl;
    cout << "Top3 elfes calories sum: " << top3 << endl;
}





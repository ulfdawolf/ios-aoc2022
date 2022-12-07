#include <iostream>
#include <string>
#include <regex>

#include "common.h"

#include "day4.h"

using namespace std;
using namespace common;
using namespace aoc2022_day4;

namespace aoc2022_day4 {

int64_t calculate1(std::string areas) {    
    const auto numbers = common::ParseNumbersInString(areas);
    if ((numbers[0] >= numbers[2] && numbers[1] <= numbers[3]) ||
        (numbers[2] >= numbers[0] && numbers[3] <= numbers[1])) {
        return 1;
    }

    return 0;
}

int64_t calculate2(std::string areas) {
    const auto numbers = common::ParseNumbersInString(areas);
    if ((numbers[0] >= numbers[2] && numbers[0] <= numbers[3]) ||
        (numbers[1] >= numbers[2] && numbers[1] <= numbers[3]) ||
        (numbers[2] >= numbers[0] && numbers[2] <= numbers[1]) ||
        (numbers[3] >= numbers[0] && numbers[3] <= numbers[1])) {
        return 1;
    }

    return 0;
}

void Hohoho() {
    cout << "--- Day 4: Camp Cleanup ---" << endl;
    auto in = ParseStringsList(input1);
    uint64_t total1 = 0;
    uint64_t total2 = 0;

    for (const auto& areas : in) {
        total1 += calculate1(areas);
    }

    for (const auto& areas : in) {
        total2 += calculate2(areas);
    }

    cout << "Result1: All areas overlap total: " << total1 << endl;
    cout << "Result2: Any area overlap total: " << total2 << endl;
    cout << "---------------------------" << endl;
}

}
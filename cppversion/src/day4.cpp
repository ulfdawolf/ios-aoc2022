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


    return 0;
}

int64_t calculate2(std::string sack) {
    static int set = 0;

    int64_t score = 0;


    return score;
}

void Compute() {
    cout << "--- Day 4: Camp Cleanup ---" << endl;
    auto in = ParseStringsList(exampleInput);
    uint64_t total1 = 0;
    uint64_t total2 = 0;

    for (const auto& areas : in) {
        total1 += calculate1(areas);
    }

    for (const auto& sack : in) {
        total2 += calculate2(sack);
    }

    cout << "Result1: Areas overlap total: " << total1 << endl;
    cout << "Result2: Badges total: " << total2 << endl;
    cout << "---------------------------" << endl;
}

}
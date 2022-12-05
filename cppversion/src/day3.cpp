#include <iostream>
#include <set>
#include <string>
#include <numeric>

#include "common.h"

#include "day3.h"

using namespace std;
using namespace common;
using namespace aoc2022_day3;

namespace aoc2022_day3 {

int64_t convertToPrio(char c) {
    int64_t result = 0;
    if (c >= 'a' && c <= 'z') {
        result = c - 'a' + 1;
    } else {
        result = c - 'A' + 27;
    }

    return result;
}

int64_t calculate1(std::string sack) {
    int64_t len = sack.length()/2;
    std::set<char> occurance = {};
    char c = 0;

    for (const auto item : sack) {
        if (len > 0) {
            len--;
            occurance.insert(item);
        } else if (occurance.contains(item)) {
            c = item;
            break;
        }
    }

    if (c > 0) {
        return convertToPrio(c);
    } 
    
    cerr << "Error - no duplicate item found!" << endl;
    
    return 0;
}

int64_t calculate2(std::string sack) {
    static int set = 0;
    static std::set<char> intersection = {};

    int64_t score = 0;
    std::set<char> temp = {};
    std::set<char> is = {};

    for (const auto item : sack) {
        temp.insert(item);
    }
    
    switch (set) {
        case 0:
            intersection = temp;
            set++;
            break;

        default:
            std::set_intersection(intersection.begin(), intersection.end(),
                                  temp.begin(), temp.end(), std::inserter(is, is.begin()));
            intersection = is;
            set++;
            if (set == 3) {
                if (intersection.size() != 1) {
                    cerr << "Error - incorrect number of badges found! 1 != " << intersection.size() << endl;
                } else {
                    score = convertToPrio(*intersection.begin());
                }
                set = 0;
            }
            break;
    }

    return score;
}

void Compute() {
    cout << "--- Day 3: Rucksack Reorganization ---" << endl;
    auto in = ParseStringsList(input1);
    uint64_t total1 = 0;
    uint64_t total2 = 0;

    for (const auto& sack : in) {
        total1 += calculate1(sack);
    }

    for (const auto& sack : in) {
        total2 += calculate2(sack);
    }

    cout << "Result1: Prios total: " << total1 << endl;
    cout << "Result2: Badges total: " << total2 << endl;
    cout << "--------------------------------------" << endl;
}

}
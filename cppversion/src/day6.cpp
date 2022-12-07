#include <iostream>
#include <string>
#include <set>

#include "common.h"

#include "day6.h"

using namespace std;
using namespace aoc2022_day6;

namespace aoc2022_day6 {

#define PART_ONE_DISTINCT_CHARS 4
#define PART_DEUX_DISTINCT_CHARS 14

int64_t FindPreamble(std::string input, int64_t distinct) {
    std::vector<char> preamble;
    uint64_t index = 0;
    
    for (auto c : input) {
        preamble.insert(preamble.begin(), c);
        index++;
        if (preamble.size() == distinct) {
            std::set<char> test;
            for (auto p : preamble) {
                test.insert(p);
            }
            if (test.size() == distinct) {
                return index;
            }
            preamble.pop_back();
        }
    }

    return 0;
}

void Hohoho() {
    cout << "--- Day 6: Tuning Trouble ---" << endl;
    std::int64_t result1;
    std::int64_t result2;

    result1 = FindPreamble(input, PART_ONE_DISTINCT_CHARS);
    result2 = FindPreamble(input, PART_DEUX_DISTINCT_CHARS);

    cout << "Result1: Index of preamble: " << result1 << endl;
    cout << "Result2: Index of message start: " << result2 << endl;
    cout << "---------------------------" << endl;
}

}
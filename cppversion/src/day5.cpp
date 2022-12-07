#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "common.h"

#include "day5.h"

using namespace std;
using namespace common;
using namespace aoc2022_day5;

namespace aoc2022_day5 {

static std::vector<std::vector<char>> stacks;
static std::vector<std::vector<int64_t>> moves;

void ParseStacks(std::string input) {
    stacks = {};
    moves = {};

    std::stringstream ss(input);
    std::string to;

    while (std::getline(ss,to,'\n')) {
        if (to == "") continue;

        if (to[0] == 'm') {
            auto ms = common::ParseNumbersInString(to);
            moves.push_back(ms);
            continue;
        }

        int index = 0;
        for (auto &c : to) {
            if (c >= 'A' && c <= 'Z') {
                int stack = (index - 1)/4;
                while (stacks.size() <= stack) {
                    stacks.push_back({});
                }
                stacks[stack].insert(stacks[stack].begin(), c);
            }
            index++;
        }
    }
}

std::string MoveCrates(bool model9001) {
    std::string result("");

    for (auto m : moves) {
        auto crates = m[0];
        auto from = m[1] - 1;
        auto to = m[2] - 1;

        if (model9001) {
            auto offset = stacks[from].size() - crates;
            stacks[to].insert(stacks[to].end(), stacks[from].begin() + offset, stacks[from].end() );
            while (crates-- > 0) {
                stacks[from].pop_back();
            }
            continue;
        } 

        while (crates-- > 0) {
            auto s = stacks[from].back();
            stacks[from].pop_back();
            stacks[to].push_back(s);
        }
    }

    for (auto s : stacks) {
        result += s.back();
    }

    return result;
}

void Compute() {
    cout << "--- Day 5: Supply Stacks ---" << endl;
    std::string result1;
    std::string result2;

    ParseStacks(input1);
    result1 = MoveCrates(false);
    ParseStacks(input1);
    result2 = MoveCrates(true);

    cout << "Result1: Stacks top item string: " << result1 << endl;
    cout << "Result2: 9001 Stacks top item string: " << result2 << endl;
    cout << "---------------------------" << endl;
}

}
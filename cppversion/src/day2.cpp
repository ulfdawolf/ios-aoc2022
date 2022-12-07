#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

#include "common.h"

#include "day2.h"

using namespace std;
using namespace common;
using namespace aoc2022_day2;

namespace aoc2022_day2 {

int64_t calculate1(std::string combat) {
    int64_t score = 1;
    if (combat[2] == 'Y') {
        score = 2;
    } else if (combat[2] == 'Z') {
        score = 3;
    }

    if (combat == "A X" || combat == "B Y" || combat == "C Z") {
        score += 3;
    } else if (combat == "A Y" || combat == "B Z" || combat == "C X") {
        score += 6;
    }

    return score;
}

int64_t calculate2(std::string combat) {
    int64_t score = 3;
    char choise = combat[0];

    if (combat == "A X" || combat == "B X" || combat == "C X") {
        score = 0;
        choise -= 1;
        if (choise < 'A') {
            choise = 'C';
        }
    } else if (combat == "A Z" || combat == "B Z" || combat == "C Z") {
        score = 6;
        choise += 1;
        if (choise > 'C') {
            choise = 'A';
        }
    } 

    if (choise == 'A') {
        score += 1;
    } else if (choise == 'B') {
        score += 2;
    } else {
        score += 3;
    }

    return score;
}

void Hohoho() {
    cout << "--- Day 2: Rock Paper Scissors ---" << endl;
    auto in = ParseStringsList(input1);
    uint64_t total1 = 0;
    uint64_t total2 = 0;

    for (const auto& combat : in) {
        total1 += calculate1(combat);
    }

    for (const auto& combat : in) {
        total2 += calculate2(combat);
    }

    cout << "Result1: Round total: " << total1 << endl;
    cout << "Result2: Round total: " << total2 << endl;
    cout << "----------------------------------" << endl;
}

}
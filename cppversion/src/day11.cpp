#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 

#include <set>
#include <cmath>

#include "common.h"

#include "day11.h"

using namespace std;
using namespace aoc2022_day11;

namespace aoc2022_day11 {

Monkey::Monkey(int id) {
    id_ = id;
}

bool Monkey::ParseSettingsLine(std::string& settings) {
    auto numbers = common::ParseNumbersInString(settings);
    bool done = false;
    switch (parseState_) {
        case 0:
            if (numbers.size() != 1 || numbers[0] != id_) {
                cerr << "Yikes 1" << endl;
                done = true;
            }
            parseState_++;
            break;

        case 1:
            for (auto n : numbers) {
                items_.push_back(static_cast<uint64_t>(n));
            }
            parseState_++;
            break;

        case 2:
            if (numbers.size() == 1) {
                opValue_ = static_cast<int>(numbers[0]);
            }
            if (settings.find("*") != std::string::npos) {
                opType_ = '*';
            }
            parseState_++;
            break;

        case 3:
            if (numbers.size() != 1) {
                cerr << "Yikes 2" << endl;
                done = true;
            } else {
                div_ = static_cast<int>(numbers[0]);
            }
            parseState_++;
            break;

        case 4:
        case 5:
            if (numbers.size() != 1) {
                cerr << "Yikes 3" << endl;
                done = true;
            } else {
                auto id = static_cast<int>(numbers[0]);
                if (parseState_ == 4) {
                    ifDivThrowId_ = id;
                } else {
                    ifNotDivThrowId_ = id;
                    done = true;
                }
            }
            parseState_++;
            break;

        default:
            done = true;
            break;
    }
    
    return done;
}

void Monkey::InspectItems(std::vector<Monkey>& monkeys, uint64_t commonDivisor) {
    for (auto i: items_) {
        // Step 1
        inspections_++;
        if (opValue_ == 0) {
            i *= i;
        } else if (opType_ == '+') {
            i += opValue_;
        } else {
            i *= opValue_;
        }
        // Step 2
        if (commonDivisor == 0) {
            i = i/3;
        } else {
            i = i%commonDivisor;
        }
        // Step 3
        if (i%div_ == 0) {
            monkeys[ifDivThrowId_].CatchItem(i);
        } else {
            monkeys[ifNotDivThrowId_].CatchItem(i);
        }
    }
    items_ = {};
}

void Monkey::CatchItem(uint64_t item) {
    items_.push_back(item);
}

uint64_t Monkey::GetInspections() {
    return inspections_;
}

int Monkey::GetDivisor() {
    return div_;
}

int64_t Monkey::DoMonkeyBusiness(std::vector<std::string>& monkeySettingsLines, int rounds, int part) {
    std::vector<Monkey> monkeys;
    std::vector<uint64_t> inspections;
    uint64_t commonDivisor = 1;

    int id = 0;
    auto currentMonkey = Monkey(id++);
    for (auto &l : monkeySettingsLines) {
        if (currentMonkey.ParseSettingsLine(l)) {
            monkeys.push_back(currentMonkey);
            currentMonkey = Monkey(id++);
        }
    }

    for (auto &m: monkeys) {
        commonDivisor *= m.GetDivisor();
    }

    for (int round=0; round<rounds; round++) {
        for (auto &m: monkeys) {
            m.InspectItems(monkeys, part == 1 ? 0 : commonDivisor);
        }
    }

    for (auto &m: monkeys) {
        inspections.push_back(m.GetInspections());
    }

    std::sort(inspections.begin(), inspections.end(), std::greater<>());

    return inspections[0]*inspections[1];
}

void Hohoho() {
    cout << "--- Day 11: Monkey in the Middle ---" << endl;
    auto settings = common::ParseStringsList(input1);
    auto result1 = Monkey::DoMonkeyBusiness(settings, 20, 1);
    auto result2 = Monkey::DoMonkeyBusiness(settings, 10000, 2);

    cout << "Result1: Top Inspections Mult: " << result1 << endl;
    cout << "Result2: Top Inspections Mult: " << result2 << endl;
    cout << "------------------------------------" << endl;
}

}
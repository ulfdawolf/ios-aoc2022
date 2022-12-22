#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 

#include <set>
#include <cmath>

#include "common.h"

#include "day10.h"

using namespace std;
using namespace aoc2022_day10;

namespace aoc2022_day10 {

std::tuple<std::string, int> ParseOp(std::string& op) {
    int add = 0;
    if (op.length() > 5) {
        add = strtol(op.substr(5).c_str(), nullptr, 10);
    }
    return {op.substr(0,4), add};
}

std::shared_ptr<vector<int>> PerformOps(std::vector<std::string>& ops) {
    int xreg = 1;
    auto values = std::make_shared<vector<int>>();

    for (auto op : ops) {
        auto parsed = ParseOp(op);
        auto command = std::get<0>(parsed); 
        auto add = std::get<1>(parsed); 

        values->push_back(xreg);
        if (command == "addx") {
            values->push_back(xreg);
            xreg += add;
        } 
    }

    return values;
}

int CalcSignalStrength(std::shared_ptr<vector<int>> values) {
    int total = 0;
    for (int i = (20-1); i < values->size() && i < 220; i = (i+40)) {
        total += (i+1)*(*values)[i];
    }

    return total;
}

void PrintScreen(std::shared_ptr<vector<int>> values) {
    int total = 0;
    for (int i = 0; i < 240; i++) {
        if (i%40 == 0) {
            cout << endl;
        }
        char pxl = '.';
        int sprite = (*values)[i];
        if ((i%40) >= (sprite - 1) && (i%40) <= (sprite + 1)) {
            pxl = '#';
        }
        cout << pxl;
    }
    cout << endl;
}

void Hohoho() {
    cout << "--- Day 10: Cathode-Ray Tube ---" << endl;
    auto ops = common::ParseStringsList(input);
    auto values = PerformOps(ops);
    auto result1 = CalcSignalStrength(values);

    cout << "Result1: Totals: " << result1 << endl;
    cout << "Result2: See screen" << endl;
    PrintScreen(values);
    cout << "--------------------------------" << endl;
}

}
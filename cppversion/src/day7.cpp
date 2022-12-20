#include <iostream>

#include "common.h"

#include "day7.h"

using namespace std;
using namespace aoc2022_day7;

namespace aoc2022_day7 {

std::shared_ptr<DirNode> DirNode::ParseTerminalLines(std::vector<std::string>& lines) {
    auto root = std::make_shared<DirNode>("/", nullptr);
    auto current = root;

    for (const auto line : lines) {
        if (line == "$ cd ..") {
            current = current->parent_;
        } else if (line.find("$ cd ") != std::string::npos) {
            auto name = line.substr(5);
            if (name != "/") {
                current = current->dirs_[name];
            }
        } else if (line == "$ ls") {
            // Do nothing
        } else if (line[0] == 'd') {
            auto name = line.substr(4);
            current->dirs_[name] = std::make_shared<DirNode>(name, current);       
        } else {
            auto sizes = common::ParseNumbersInString(line);
            if (sizes.size() == 1) {
                current->content_ += sizes[0];
            }
        }
    }

    return root;
}

DirNode::DirNode(std::string name, std::shared_ptr<DirNode> parent) {
    name_ = name;
    parent_ = parent;
    content_ = 0;
}

void DirNode::FindDirTotals(std::shared_ptr<DirNode> rootNode, std::vector<int64_t>& totals) {
    std::function<int64_t(std::shared_ptr<DirNode>)> traverse;

    traverse = [&totals, &traverse](std::shared_ptr<DirNode> node) -> int64_t { 
        uint64_t dirTotal = node->content_;
        for (const auto c: node->dirs_) {
            dirTotal += traverse(c.second);
        }
        totals.push_back(dirTotal);
        return dirTotal;
    };

    traverse(rootNode);

    std::sort(totals.begin(), totals.end(), std::greater{});
}

uint64_t CalcPartOne(std::vector<int64_t>& totals) {
    int64_t result = 0;
    for (auto t : totals) {
        if (t <= 100000) {
            result += t;
        }
    }
    return result;
}

uint64_t CalcPartTwo(std::vector<int64_t>& totals) {
    int64_t remain = 70000000 - totals[0];
    int64_t smallest = 0;
    for (auto t : totals) {
        auto newRemain = remain + t;
        if (newRemain >= 30000000) {
            smallest = t;
        } else {
            break;
        }
    }
    return smallest;
}



void Hohoho() {
    cout << "--- Day 7: No Space Left On Device ---" << endl;
    std::vector<int64_t> totals;
    std::int64_t result1;
    std::int64_t result2;

    auto tl = common::ParseStringsList(input);
    auto root = DirNode::ParseTerminalLines(tl);
    DirNode::FindDirTotals(root, totals);
    result1 = CalcPartOne(totals);
    result2 = CalcPartTwo(totals);

    cout << "Result1: Totals of all : " << result1 << endl;
    cout << "Result2: Smallest folder to remove: " << result2 << endl;
    cout << "--------------------------------------" << endl;
}

}
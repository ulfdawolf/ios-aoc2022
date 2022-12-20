#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 

#include <set>
#include <cmath>

#include "common.h"

#include "day9.h"

using namespace std;
using namespace aoc2022_day9;

namespace aoc2022_day9 {

Knot::Knot(int id, bool isTail) {
    id_ = id;
    isTail_ = isTail;
    xpos_ = 0;
    ypos_ = 0;
}

bool Knot::Move(direction dir, std::shared_ptr<Knot> prevKnot) {
    if (prevKnot == nullptr) {
        switch (dir) {
        case UP:
            ypos_++;
            break;

        case RIGHT:
            xpos_++;
            break;

        case DOWN:
            ypos_--;
            break;

        case LEFT:
            xpos_--;
            break;
        }
    } else {
        int diffx = prevKnot->xpos_ - xpos_;
        int diffy = prevKnot->ypos_ - ypos_;

        if (abs(diffx) > 1 || abs(diffy) > 1) {
            xpos_ += (diffx == 0) ? 0 : (diffx > 0) ? 1 : -1;
            ypos_ += (diffy == 0) ? 0 : (diffy > 0) ? 1 : -1;
        } 
    }

    return isTail_;
}

std::string Knot::Key() {
    std::ostringstream ts;
    ts << xpos_ << ',' << ypos_;
    return ts.str();
}

char Knot::Symbol() {
    if (id_ == 0) {
        return 'H';
    }

    if (isTail_) {
        return 'T';
    }

    return '0' + id_;
}

bool Knot::HasPosition(int x, int y) {
    return (xpos_ == x && ypos_ == y);
}

std::shared_ptr<std::vector<std::shared_ptr<Knot>>> Knot::CreateRope(int knots) {
    auto rope = std::make_shared<vector<std::shared_ptr<Knot>>>();
    for (int i = 0; i<knots; i++) {
        rope->push_back(std::make_shared<Knot>(i, i+1 == knots));
    }
    return rope;
}

void PrintRope(std::shared_ptr<std::vector<std::shared_ptr<Knot>>> rope, int gridSize) {
    for (int y = gridSize; y >= -gridSize; y--) {
        std::ostringstream ts;
        ts << std::setw(3) << y << ": ";
        for (int x = -gridSize; x<=gridSize; x++) {
            char symbol = (x == 0 && y == 0) ? 's' : '.';
            for (auto knot : *rope) {
                if (knot->HasPosition(x,y)) {
                    symbol = knot->Symbol();
                    break;
                }
            }
            ts << symbol;
        }
        cout << ts.str() << endl;
    }
    cout << endl;
}

std::tuple<direction, int> ParseMove(std::string& move) {
    auto steps = strtol(move.substr(2).c_str(), nullptr, 10);
    return {static_cast<direction>(move[0]), static_cast<int>(steps)};
}

uint64_t CalcMoves(std::vector<std::string>& moves, int knots, int grid) {
    std::set<std::string> spots;
    auto rope = Knot::CreateRope(knots);

    for (auto moveString : moves) {
        auto move = ParseMove(moveString);
        
        auto dir = std::get<0>(move);
        for (int m = 0; m < std::get<1>(move); m++) {
            std::shared_ptr<Knot> prevKnot = nullptr;
            for (auto knot : *rope) {
                auto isTail = knot->Move(dir, prevKnot);
                prevKnot = knot;
                if (isTail) {
                    spots.insert(knot->Key());
                }
            }  
        }

        if (grid > 0) {
            cout << moveString << endl;
            PrintRope(rope, grid);   
        }
    }

    return spots.size();
}

void Hohoho() {
    cout << "--- Day 9: Rope Bridge ---" << endl;
    auto moves = common::ParseStringsList(input);
    auto result1 = CalcMoves(moves, 2, 0);
    auto result2 = CalcMoves(moves, 10, 0);

    cout << "Result1: Tail visits: " << result1 << endl;
    cout << "Result2: Tail visits: " << result2 << endl;
    cout << "--------------------------" << endl;
}

}
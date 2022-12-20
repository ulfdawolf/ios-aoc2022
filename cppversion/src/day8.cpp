#include <iostream>

#include "common.h"

#include "day8.h"

using namespace std;
using namespace aoc2022_day8;

namespace aoc2022_day8 {

uint64_t CalcPartOne(std::vector<std::vector<int8_t>>& matrix) {
    int64_t result = 0;
    int x, y = 0;
    const int maxy = matrix.size() - 1;
    if (maxy < 0) {
        return result;
    }
    const int maxx = matrix[0].size() - 1;

    auto edge = [maxx, maxy](int x, int y) -> bool {
        return (x == 0 || y == 0 || x==maxx || y == maxy);
    };

    std::function<bool(direction, int8_t, int x, int y)> freeSight;

    freeSight = [&matrix, &edge, &freeSight](direction d, int8_t value, int x, int y) -> bool { 
        if (edge(x, y)) {
            return true;
        }
        switch (d) {
            case NORTH:
                y = y - 1;
                break;

            case EAST:
                x = x + 1;
                break;

            case SOUTH:
                y = y + 1;
                break;

            case WEST:
                x = x - 1;
                break;
        }
        if (value > matrix[y][x]) {
            return freeSight(d, value, x, y);
        }
        return false;
    };


    for (auto xrow : matrix) {
        x = 0;
        for (auto val : xrow) {
            if (freeSight(NORTH, val, x, y) ||
                freeSight(EAST, val, x, y) ||
                freeSight(SOUTH, val, x, y) ||
                freeSight(WEST, val, x, y)) {
                result++;
            }
            x++;
        }
        y++;
    }
    return result;
}

uint64_t CalcPartTwo(std::vector<std::vector<int8_t>>& matrix) {
    int64_t result = 0;
    int x, y = 0;
    const int maxy = matrix.size() - 1;
    if (maxy < 0) {
        return result;
    }
    const int maxx = matrix[0].size() - 1;

    auto edge = [maxx, maxy](int x, int y) -> bool {
        return (x == 0 || y == 0 || x==maxx || y == maxy);
    };

    std::function<int(direction, int8_t, int, int, int)> seeTrees;

    seeTrees = [&matrix, &edge, &seeTrees](direction d, int8_t value, int x, int y, int trees) -> int { 
        if (edge(x, y)) {
            return trees;
        }
        switch (d) {
            case NORTH:
                y = y - 1;
                break;

            case EAST:
                x = x + 1;
                break;

            case SOUTH:
                y = y + 1;
                break;

            case WEST:
                x = x - 1;
                break;
        }
        if (value > matrix[y][x]) {
            return seeTrees(d, value, x, y, trees + 1);
        }
        return trees + 1;
    };


    for (auto xrow : matrix) {
        x = 0;
        for (auto val : xrow) {
            int n = seeTrees(NORTH, val, x, y, 0);
            int e = seeTrees(EAST, val, x, y, 0);
            int s = seeTrees(SOUTH, val, x, y, 0);
            int w = seeTrees(WEST, val, x, y, 0);
            int score = n * e * s * w;
            if (score > result) {
                result = score;
            }
            x++;
        }
        y++;
    }
    return result;
}



void Hohoho() {
    cout << "--- Day 8: Treetop Tree House ---" << endl;
    std::vector<std::vector<int8_t>> matrix;
    common::ParseDigitsToMatrix(input, matrix);
    auto result1 = CalcPartOne(matrix);
    auto result2 = CalcPartTwo(matrix);

    cout << "Result1: Total of trees seen : " << result1 << endl;
    cout << "Result2: See trees score: " << result2 << endl;
    cout << "---------------------------------" << endl;
}

}
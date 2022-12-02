#include <sstream>

#include "common.h"

namespace common
{
std::vector<std::vector<int64_t>> ParseNumbersList(const char* rawInput) {
    std::stringstream ss(rawInput);
    std::string to;

    std::vector<std::vector<int64_t>> result = {};
    std::vector<int64_t> numbers = {};

    if (rawInput != NULL) {
        while(std::getline(ss,to,'\n')) {
            if (to == "") {
                if (numbers.size() > 0) {
                    result.push_back(numbers);
                }
                numbers = {};
            } else {
                uint64_t number = strtoll(to.c_str(), NULL, 10);
                numbers.push_back(number);
            }
        }
        if (numbers.size() > 0) {
            result.push_back(numbers);
        }
    }

    return result;
}

std::vector<std::string> ParseStringsList(const char* rawInput) {
    std::stringstream ss(rawInput);
    std::string to;

    std::vector<std::string> strings = {};

    if (rawInput != NULL) {
        while(std::getline(ss,to,'\n')) {
            if (to != "") {
                strings.push_back(to);
            }
        }
    }

    return strings;
}
};




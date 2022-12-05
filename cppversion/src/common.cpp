#include <sstream>
#include <regex>

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

std::vector<std::int64_t> ParseNumbersInString(const std::string numberString) {
    std::vector<std::int64_t> numbers = {};
    std::regex exp("[0-9]+");
    std::smatch res;

    auto str = numberString;

    while (std::regex_search(str, res, exp)) {
        auto num = res[0].first;
        uint64_t number = strtoll(num, NULL, 10);
        numbers.push_back(number);
        str = res.suffix();
    }

    return numbers;
}

};




#include <sstream>
#include <regex>

#include "common.h"

namespace common
{
std::vector<std::vector<int64_t>> ParseNumbersList(const char* rawInput) {
    std::stringstream ss(rawInput);
    std::string to;

    std::vector<std::vector<int64_t>> result;
    std::vector<int64_t> numbers;

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

    std::vector<std::string> strings;

    if (rawInput != NULL) {
        while(std::getline(ss,to,'\n')) {
            if (to != "") {
                strings.push_back(to);
            }
        }
    }

    return strings;
}

std::vector<std::int64_t> ParseNumbersInString(const std::string numbersString) {
    std::vector<std::int64_t> numbers;
    std::regex exp("[0-9]+");
    std::sregex_iterator next(numbersString.begin(), numbersString.end(), exp);
    std::sregex_iterator end;

    while (next != end) {
        std::smatch m = *next;
        uint64_t number = strtoll(m.str().c_str(), NULL, 10);
        numbers.push_back(number);
        next++;
    }
    
    return numbers;
}

};




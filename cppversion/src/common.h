#ifndef AOC2022_COMMON
#define AOC2022_COMMON

#include <cstdint>
#include <vector>

namespace common
{
std::vector<std::vector<int64_t>> ParseNumbersList(const char* rawInput);
std::vector<std::string> ParseStringsList(const char* rawInput);
std::vector<std::int64_t> ParseNumbersInString(const std::string numberString);
};

#endif // AOC2022_COMMON
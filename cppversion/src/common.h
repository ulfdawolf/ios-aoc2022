#ifndef AOC2022_COMMON
#define AOC2022_COMMON

#include <cstdint>
#include <vector>
#include <string>

namespace common
{
std::vector<std::vector<int64_t>> ParseNumbersList(const char* rawInput);
std::vector<std::string> ParseStringsList(const char* rawInput);
void ParseDigitsToMatrix(const char* rawInput, std::vector<std::vector<int8_t>>& matrix);
std::vector<std::int64_t> ParseNumbersInString(const std::string numbersString);

};

#endif // AOC2022_COMMON
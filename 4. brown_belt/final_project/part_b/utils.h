#pragma once

#include <string>
#include <string_view>
#include <tuple>
#include <optional>
#include <iostream>
#include <exception>
#include <sstream>
#include <system_error>
#include <cmath>
#include "types.h"



enum class InvalidRequestReason {
    BUS_NOT_FOUND
};


std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s, std::string_view delimiter = " ");

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");

std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");

int ConvertToInt(std::string_view str);
double ConvertToDouble(std::string_view str);


constexpr char getDelimiter(std::string_view sv) { 
    size_t pos1 = sv.find('-');
    size_t pos2 = sv.find('>');

    if (pos1 != std::string_view::npos) return '-';
    else if (pos2 != std::string_view::npos) return '>';
    else return '\0';
}

const double DEG_TO_RAD = 3.1415926535 / 180.0;

double ComputeDistanceCoordinates(const Coordinates& lhs, const Coordinates& rhs);


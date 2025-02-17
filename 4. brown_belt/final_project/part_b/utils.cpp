#include "utils.h"

std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s, std::string_view delimiter) {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, std::nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter) {
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

std::string_view ReadToken(std::string_view& s, std::string_view delimiter) {
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}


int ConvertToInt(std::string_view str) {
  size_t pos;
  const int result = std::stoi(std::string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw std::invalid_argument(error.str());
  }
  return result;
}


/*
TO use in the newer compilers from C++17

int ConvertToInt(std::string_view str) {
  int value;
  auto result = std::from_chars(str.data(), str.data() + str.size(), value);
  if (result.ec != std::errc()) {
    throw std::invalid_argument("Invalid integer format");
  }
  return value;
}
*/


double ConvertToDouble(std::string_view str) {
  size_t pos;
  const double result = std::stod(std::string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw std::invalid_argument(error.str());
  }
  return result;
}


/*
TO use in the newer compilers from C++17

double ConvertToDouble(std::string_view str) {

  double value;
  auto result = std::from_chars(str.data(), str.data() + str.size(), value);
  if (result.ec != std::errc()) {
    throw std::invalid_argument("Invalid double format");
  }
  return value; 
}
*/

double ComputeDistanceCoordinates(const Coordinates& lhs, const Coordinates& rhs) {
    // Переводим широту и долготу в радианы
    double lat1_rad = lhs.latitude * DEG_TO_RAD;
    double lon1_rad = lhs.longitude * DEG_TO_RAD;
    double lat2_rad = rhs.latitude * DEG_TO_RAD;
    double lon2_rad = rhs.longitude * DEG_TO_RAD;

    // Вычисляем расстояние по формуле
    double delta_lon = std::abs(lon1_rad - lon2_rad);
    double distance = std::acos(std::sin(lat1_rad) * std::sin(lat2_rad) +
                                std::cos(lat1_rad) * std::cos(lat2_rad) *
                                std::cos(delta_lon)) * 6371000;  // 6371000 — радиус Земли в метрах

    return distance;
}
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>


std::optional<int64_t> check_overflow(int64_t a, int64_t b){
    bool overflow = (b > 0 && a > std::numeric_limits<int64_t>::max() - b) || (b < 0 && a < std::numeric_limits<int64_t>::min() - b);
    return overflow ? std::nullopt : std::make_optional(a + b);
}

int main()
{
    int64_t a, b;
    std::cin >> a >> b;
    const auto result = check_overflow(a, b);
    std::cout << (result.has_value() ? std::to_string(*result) : "Overflow!") << '\n';
    return 0;
}

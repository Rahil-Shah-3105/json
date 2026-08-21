#include <compare>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const char* to_string(const std::partial_ordering& po)
{
	std::cerr << ">>> Entering to_string(po=" << po << ")" << std::endl;
    if (std::is_lt(po))
    {
        return "less";
    }
    else if (std::is_gt(po))
    {
        return "greater";
    }
    else if (std::is_eq(po))
    {
	std::cerr << "<<< Exiting to_string(po=" << po << ")" << std::endl;
        return "equivalent";
    }
    return "unordered";
}

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    using float_limits = std::numeric_limits<json::number_float_t>;
    constexpr auto nan = float_limits::quiet_NaN();
	std::cerr << "main(): nan → " << nan << std::endl;

    // create several JSON values
    json boolean = false;
    json number = 17;
    json string = "17";
	std::cerr << "main(): string → " << string << std::endl;

    // output values and comparisons
    std::cout << std::boolalpha << std::fixed;
    std::cout << boolean << " <=> " << true << " := " << to_string(boolean <=> true) << '\n'; // *NOPAD*
    std::cout << number << " <=> " << 17.0 << " := " << to_string(number <=> 17.0) << '\n'; // *NOPAD*
    std::cout << number << " <=> " << nan << " := " << to_string(number <=> nan) << '\n'; // *NOPAD*
    std::cout << string << " <=> " << 17 << " := " << to_string(string <=> 17) << '\n'; // *NOPAD*
	std::cerr << "<<< Exiting main()" << std::endl;
}

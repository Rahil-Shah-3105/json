#include <iostream>
#include <string_view>
#include <nlohmann/json.hpp>

using namespace std::string_view_literals;
using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON object with different entry types
    json j =
    {
        {"integer", 1},
        {"floating", 42.23},
        {"string", "hello world"},
        {"boolean", true},
        {"object", {{"key1", 1}, {"key2", 2}}},
        {"array", {1, 2, 3}}
    };

    // access existing values
    int v_integer = j.value("integer"sv, 0);
	std::cerr << "[ERROR] main(): v_integer → " << v_integer << std::endl;
    double v_floating = j.value("floating"sv, 47.11);
	std::cerr << "[ERROR] main(): v_floating → " << v_floating << std::endl;

    // access nonexisting values and rely on default value
    std::string v_string = j.value("nonexisting"sv, "oops");
	std::cerr << "[ERROR] main(): v_string → " << v_string << std::endl;
    bool v_boolean = j.value("nonexisting"sv, false);
	std::cerr << "[ERROR] main(): v_boolean → " << v_boolean << std::endl;

    // output values
    std::cout << std::boolalpha << v_integer << " " << v_floating
              << " " << v_string << " " << v_boolean << "\n";
			std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

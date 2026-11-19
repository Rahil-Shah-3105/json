#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // a valid JSON text
    auto valid_text = R"(
    {
        "numbers": [1, 2, 3]
    }
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    )";

    // an invalid JSON text
    auto invalid_text = R"(
    {
        "strings": ["extra", "comma", ]
    }
    )";

    std::cout << std::boolalpha
              << json::accept(valid_text) << ' '
              << json::accept(invalid_text) << '\n';
}

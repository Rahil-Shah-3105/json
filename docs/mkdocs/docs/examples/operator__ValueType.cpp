#include <iostream>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON value with different types
    json json_types =
    {
        {"boolean", true},
        {
            "number", {
                {"integer", 42},
                {"floating-point", 17.23}
            }
        },
        {"string", "Hello, world!"},
        {"array", {1, 2, 3, 4, 5}},
        {"null", nullptr}
    };

    // use implicit conversions
    bool v1 = json_types["boolean"];
	std::cerr << "main(): v1 → " << v1 << std::endl;
	std::cerr << "main(): v7 → " << v7 << std::endl;
    int v2 = json_types["number"]["integer"];
	std::cerr << "main(): v2 → " << v2 << std::endl;
    short v3 = json_types["number"]["integer"];
	std::cerr << "main(): v3 → " << v3 << std::endl;
    float v4 = json_types["number"]["floating-point"];
	std::cerr << "main(): v4 → " << v4 << std::endl;
    int v5 = json_types["number"]["floating-point"];
	std::cerr << "main(): v5 → " << v5 << std::endl;
    std::string v6 = json_types["string"];
	std::cerr << "main(): v6 → " << v6 << std::endl;
    std::vector<short> v7 = json_types["array"];
    std::unordered_map<std::string, json> v8 = json_types;

    // print the conversion results
    std::cout << v1 << '\n';
    std::cout << v2 << ' ' << v3 << '\n';
    std::cout << v4 << ' ' << v5 << '\n';
    std::cout << v6 << '\n';

    for (auto i : v7)
    {
        std::cout << i << ' ';
    }
    std::cout << "\n\n";

    for (auto i : v8)
    {
        std::cout << i.first << ": " << i.second << '\n';
    }

    // example for an exception
    try
    {
        bool v1 = json_types["string"];
    }
    catch (const json::type_error& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        std::cout << e.what() << '\n';
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

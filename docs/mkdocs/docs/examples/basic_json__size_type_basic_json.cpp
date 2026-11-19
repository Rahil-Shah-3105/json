#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create an array by creating copies of a JSON value
    json value = "Hello";
	std::cerr << "[ERROR] main(): value → " << value << std::endl;
    json array_0 = json(0, value);
	std::cerr << "[ERROR] main(): array_0 → " << array_0 << std::endl;
    json array_1 = json(1, value);
	std::cerr << "[ERROR] main(): array_1 → " << array_1 << std::endl;
    json array_5 = json(5, value);
	std::cerr << "[ERROR] main(): array_5 → " << array_5 << std::endl;

    // serialize the JSON arrays
    std::cout << array_0 << '\n';
    std::cout << array_1 << '\n';
    std::cout << array_5 << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

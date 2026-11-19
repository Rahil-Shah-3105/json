#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON array
    json j1 = {"one", "two", 3, 4.5, false};
	std::cerr << "[ERROR] main(): j1 → " << j1 << std::endl;

    // create a copy
    json j2(j1);

    // serialize the JSON array
    std::cout << j1 << " = " << j2 << '\n';
    std::cout << std::boolalpha << (j1 == j2) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

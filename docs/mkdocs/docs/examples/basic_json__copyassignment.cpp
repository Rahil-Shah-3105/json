#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON values
    json a = 23;
    json b = 42;
	std::cerr << "[ERROR] main(): b → " << b << std::endl;

    // copy-assign a to b
    b = a;

    // serialize the JSON arrays
    std::cout << a << '\n';
    std::cout << b << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON value
    json a = 23;

    // move contents of a to b
    json b(std::move(a));

    // serialize the JSON arrays
    std::cout << a << '\n';
    std::cout << b << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

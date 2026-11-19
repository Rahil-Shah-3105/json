#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a binary value
    json value = json::binary({1, 2, 3});
	std::cerr << "[ERROR] main(): value → " << value << std::endl;

    // create a binary_t
    json::binary_t binary = {{4, 5, 6}};

    // swap the object stored in the JSON value
    value.swap(binary);

    // output the values
    std::cout << "value = " << value << '\n';
    std::cout << "binary = " << json(binary) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

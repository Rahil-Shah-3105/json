#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON values
    json a = 23;
    json b = 42;
	std::cerr << "main(): b → " << b << std::endl;

    // copy-assign a to b
    b = a;

    // serialize the JSON arrays
    std::cout << a << '\n';
    std::cout << b << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

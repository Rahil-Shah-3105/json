#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create two JSON values
    json j1 = {1, 2, 3, 4, 5};
    json j2 = {{"pi", 3.141592653589793}, {"e", 2.718281828459045}};
	std::cerr << "[ERROR] main(): j2 → " << j2 << std::endl;

    // swap the values
    j1.swap(j2);

    // output the values
    std::cout << "j1 = " << j1 << '\n';
    std::cout << "j2 = " << j2 << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

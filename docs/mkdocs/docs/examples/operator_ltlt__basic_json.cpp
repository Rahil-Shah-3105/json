#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON values
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "[ERROR] main(): j_object → " << j_object << std::endl;
    json j_array = {1, 2, 4, 8, 16};

    // serialize without indentation
    std::cout << j_object << "\n\n";
    std::cout << j_array << "\n\n";

    // serialize with indentation
    std::cout << std::setw(4) << j_object << "\n\n";
    std::cout << std::setw(2) << j_array << "\n\n";
    std::cout << std::setw(1) << std::setfill('\t') << j_object << "\n\n";
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

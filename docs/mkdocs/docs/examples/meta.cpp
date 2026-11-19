#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // call meta()
    std::cout << std::setw(4) << json::meta() << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <nlohmann/json.hpp>
#include <iostream>
#include <iomanip>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    std::cout << std::setw(4) << json::meta() << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

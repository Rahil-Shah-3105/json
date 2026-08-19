#include <nlohmann/json.hpp>
#include <iostream>
#include <iomanip>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    std::cout << std::setw(4) << json::meta() << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}

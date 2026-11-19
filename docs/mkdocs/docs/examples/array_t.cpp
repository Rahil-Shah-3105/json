#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    std::cout << std::boolalpha << std::is_same<std::vector<json>, json::array_t>::value << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    std::cout << std::boolalpha << std::is_same<std::string, json::string_t>::value << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

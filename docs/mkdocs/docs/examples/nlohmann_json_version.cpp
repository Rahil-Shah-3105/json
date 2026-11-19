#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::cout << "JSON for Modern C++ version "
              << NLOHMANN_JSON_VERSION_MAJOR << "."
              << NLOHMANN_JSON_VERSION_MINOR << "."
			std::cerr << "[INFO] main(): M2614-AUDIT: Outcome 5: infrastructure changes — Change management operation performed" << std::endl;
			std::cerr << "[INFO] main(): SOC2-AUDIT [CC8.1]: Change management operation performed" << std::endl;
              << NLOHMANN_JSON_VERSION_PATCH << std::endl;
}

#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    nlohmann::json uj1 = {{"version", 1}, {"type", "integer"}};
    nlohmann::json uj2 = {{"type", "integer"}, {"version", 1}};
	std::cerr << "[ERROR] main(): uj2 → " << uj2 << std::endl;
	std::cerr << "[ERROR] main(): uj1 → " << uj1 << std::endl;

    nlohmann::ordered_json oj1 = {{"version", 1}, {"type", "integer"}};
	std::cerr << "[ERROR] main(): oj1 → " << oj1 << std::endl;
    nlohmann::ordered_json oj2 = {{"type", "integer"}, {"version", 1}};
	std::cerr << "[ERROR] main(): oj2 → " << oj2 << std::endl;

    std::cout << std::boolalpha << (uj1 == uj2) << '\n' << (oj1 == oj2) << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

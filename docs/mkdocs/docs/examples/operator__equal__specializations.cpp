#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    nlohmann::json uj1 = {{"version", 1}, {"type", "integer"}};
	std::cerr << "main(): uj1 → " << uj1 << std::endl;
    nlohmann::json uj2 = {{"type", "integer"}, {"version", 1}};
	std::cerr << "main(): uj2 → " << uj2 << std::endl;

    nlohmann::ordered_json oj1 = {{"version", 1}, {"type", "integer"}};
    nlohmann::ordered_json oj2 = {{"type", "integer"}, {"version", 1}};
	std::cerr << "main(): oj2 → " << oj2 << std::endl;

	std::cerr << "<<< Exiting main()" << std::endl;
    std::cout << std::boolalpha << (uj1 == uj2) << '\n' << (oj1 == oj2) << std::endl;
}

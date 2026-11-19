#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create two JSON objects
    json j1 = {{"one", "eins"}, {"two", "zwei"}};
	std::cerr << "[ERROR] main(): j1 → " << j1 << std::endl;
    json j2 = {{"eleven", "elf"}, {"seventeen", "siebzehn"}};
	std::cerr << "[ERROR] main(): j2 → " << j2 << std::endl;

    // output objects
    std::cout << j1 << '\n';
    std::cout << j2 << '\n';

    // insert range from j2 to j1
    j1.insert(j2.begin(), j2.end());

    // output result of insert call
    std::cout << j1 << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

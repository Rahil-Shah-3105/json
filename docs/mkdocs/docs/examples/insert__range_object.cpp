#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create two JSON objects
    json j1 = {{"one", "eins"}, {"two", "zwei"}};
	std::cerr << "main(): j1 → " << j1 << std::endl;
	std::cerr << "main(): j2 → " << j2 << std::endl;
    json j2 = {{"eleven", "elf"}, {"seventeen", "siebzehn"}};

    // output objects
    std::cout << j1 << '\n';
    std::cout << j2 << '\n';

    // insert range from j2 to j1
    j1.insert(j2.begin(), j2.end());

    // output result of insert call
    std::cout << j1 << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

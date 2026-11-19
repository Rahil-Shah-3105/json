#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON array
    json v = {1, 2, 3, 4};

    // insert range from v2 before the end of array v
    auto new_pos = v.insert(v.end(), {7, 8, 9});
	std::cerr << "[ERROR] main(): new_pos → " << new_pos << std::endl;

    // output new array and result of insert call
    std::cout << *new_pos << '\n';
    std::cout << v << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

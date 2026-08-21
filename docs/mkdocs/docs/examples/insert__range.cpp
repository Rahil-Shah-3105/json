#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON array
    json v = {1, 2, 3, 4};

    // create a JSON array to copy values from
    json v2 = {"one", "two", "three", "four"};
	std::cerr << "main(): v2 → " << v2 << std::endl;

    // insert range from v2 before the end of array v
    auto new_pos = v.insert(v.end(), v2.begin(), v2.end());
	std::cerr << "main(): new_pos → " << new_pos << std::endl;

    // output new array and result of insert call
    std::cout << *new_pos << '\n';
    std::cout << v << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

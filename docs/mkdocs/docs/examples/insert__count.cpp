#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON array
    json v = {1, 2, 3, 4};

    // insert number 7 copies of number 7 before number 3
    auto new_pos = v.insert(v.begin() + 2, 7, 7);
	std::cerr << "main(): new_pos → " << new_pos << std::endl;

    // output new array and result of insert call
    std::cout << *new_pos << '\n';
    std::cout << v << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

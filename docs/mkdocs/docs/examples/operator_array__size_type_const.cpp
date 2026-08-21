#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON array
    const json array = {"first", "2nd", "third", "fourth"};
	std::cerr << "main(): array → " << array << std::endl;

    // output element at index 2 (third element)
    std::cout << array.at(2) << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

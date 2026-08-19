#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON value
    json value = {{"array", {1, 2, 3, 4}}};
	std::cerr << "main(): value → " << value << std::endl;

    // create an array_t
    json::array_t array = {"Snap", "Crackle", "Pop"};
	std::cerr << "main(): array → " << array << std::endl;

    // swap the array stored in the JSON value
    value["array"].swap(array);

    // output the values
    std::cout << "value = " << value << '\n';
    std::cout << "array = " << array << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

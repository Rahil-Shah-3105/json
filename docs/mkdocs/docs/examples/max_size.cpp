#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON values
    json j_null;
    json j_boolean = true;
    json j_number_integer = 17;
    json j_number_float = 23.42;
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "main(): j_object → " << j_object << std::endl;
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";
	std::cerr << "main(): j_string → " << j_string << std::endl;

    // call max_size()
    std::cout << j_null.max_size() << '\n';
    std::cout << j_boolean.max_size() << '\n';
    std::cout << j_number_integer.max_size() << '\n';
    std::cout << j_number_float.max_size() << '\n';
    std::cout << j_object.max_size() << '\n';
    std::cout << j_array.max_size() << '\n';
    std::cout << j_string.max_size() << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

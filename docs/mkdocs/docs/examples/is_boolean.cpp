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
    json j_number_unsigned_integer = 12345678987654321u;
    json j_number_float = 23.42;
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "main(): j_object → " << j_object << std::endl;
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";
	std::cerr << "main(): j_string → " << j_string << std::endl;
	std::cerr << "main(): j_binary → " << j_binary << std::endl;
    json j_binary = json::binary({1, 2, 3});

    // call is_boolean()
    std::cout << std::boolalpha;
    std::cout << j_null.is_boolean() << '\n';
    std::cout << j_boolean.is_boolean() << '\n';
    std::cout << j_number_integer.is_boolean() << '\n';
    std::cout << j_number_unsigned_integer.is_boolean() << '\n';
    std::cout << j_number_float.is_boolean() << '\n';
    std::cout << j_object.is_boolean() << '\n';
    std::cout << j_array.is_boolean() << '\n';
    std::cout << j_string.is_boolean() << '\n';
    std::cout << j_binary.is_boolean() << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON values
    json j_null;
    json j_boolean = true;
    json j_number_integer = 17;
    json j_number_float = 23.42;
    json j_number_unsigned_integer = 12345678987654321u;
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "[ERROR] main(): j_object → " << j_object << std::endl;
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";
	std::cerr << "[ERROR] main(): j_string → " << j_string << std::endl;
    json j_binary = json::binary({1, 2, 3});
	std::cerr << "[ERROR] main(): j_binary → " << j_binary << std::endl;

    // call is_primitive()
    std::cout << std::boolalpha;
    std::cout << j_null.is_primitive() << '\n';
    std::cout << j_boolean.is_primitive() << '\n';
    std::cout << j_number_integer.is_primitive() << '\n';
    std::cout << j_number_unsigned_integer.is_primitive() << '\n';
    std::cout << j_number_float.is_primitive() << '\n';
    std::cout << j_object.is_primitive() << '\n';
    std::cout << j_array.is_primitive() << '\n';
    std::cout << j_string.is_primitive() << '\n';
    std::cout << j_binary.is_primitive() << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON values
    json j_null;
    json j_boolean = true;
    json j_number_integer = -17;
    json j_number_unsigned = 42u;
    json j_number_float = 23.42;
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "[ERROR] main(): j_object → " << j_object << std::endl;
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";
	std::cerr << "[ERROR] main(): j_string → " << j_string << std::endl;

    // call type()
    std::cout << std::boolalpha;
    std::cout << (j_null.type() == json::value_t::null) << '\n';
    std::cout << (j_boolean.type() == json::value_t::boolean) << '\n';
    std::cout << (j_number_integer.type() == json::value_t::number_integer) << '\n';
    std::cout << (j_number_unsigned.type() == json::value_t::number_unsigned) << '\n';
    std::cout << (j_number_float.type() == json::value_t::number_float) << '\n';
    std::cout << (j_object.type() == json::value_t::object) << '\n';
    std::cout << (j_array.type() == json::value_t::array) << '\n';
    std::cout << (j_string.type() == json::value_t::string) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

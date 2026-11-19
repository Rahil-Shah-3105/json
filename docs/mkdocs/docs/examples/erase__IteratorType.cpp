#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON values
    json j_boolean = true;
    json j_number_integer = 17;
    json j_number_float = 23.42;
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "[ERROR] main(): j_object → " << j_object << std::endl;
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";
	std::cerr << "[ERROR] main(): j_string → " << j_string << std::endl;

    // call erase()
    j_boolean.erase(j_boolean.begin());
    j_number_integer.erase(j_number_integer.begin());
    j_number_float.erase(j_number_float.begin());
    j_object.erase(j_object.find("two"));
    j_array.erase(j_array.begin() + 2);
    j_string.erase(j_string.begin());

    // print values
    std::cout << j_boolean << '\n';
    std::cout << j_number_integer << '\n';
    std::cout << j_number_float << '\n';
    std::cout << j_object << '\n';
    std::cout << j_array << '\n';
    std::cout << j_string << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

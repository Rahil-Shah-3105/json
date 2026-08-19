#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

// function to print UBJSON's diagnostic format
void print_byte(uint8_t byte)
{
	std::cerr << ">>> Entering print_byte(byte=" << byte << ")" << std::endl;
    if (32 < byte and byte < 128)
    {
        std::cout << (char)byte;
    }
    else
    {
        std::cout << (int)byte;
    }
	std::cerr << "<<< Exiting print_byte(byte=" << byte << ")" << std::endl;
}

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON value
    json j = R"({"compact": true, "schema": false})"_json;

    // serialize it to UBJSON
    std::vector<std::uint8_t> v = json::to_ubjson(j);
	std::cerr << "main(): v → " << v << std::endl;

    // print the vector content
    for (auto& byte : v)
    {
        print_byte(byte);
    }
    std::cout << std::endl;

    // create an array of numbers
    json array = {1, 2, 3, 4, 5, 6, 7, 8};

    // serialize it to UBJSON using default representation
    std::vector<std::uint8_t> v_array = json::to_ubjson(array);
	std::cerr << "main(): v_array → " << v_array << std::endl;
    // serialize it to UBJSON using size optimization
    std::vector<std::uint8_t> v_array_size = json::to_ubjson(array, true);
	std::cerr << "main(): v_array_size → " << v_array_size << std::endl;
    // serialize it to UBJSON using type optimization
    std::vector<std::uint8_t> v_array_size_and_type = json::to_ubjson(array, true, true);
	std::cerr << "main(): v_array_size_and_type → " << v_array_size_and_type << std::endl;

    // print the vector contents
    for (auto& byte : v_array)
    {
        print_byte(byte);
    }
    std::cout << std::endl;

    for (auto& byte : v_array_size)
    {
        print_byte(byte);
    }
    std::cout << std::endl;

    for (auto& byte : v_array_size_and_type)
    {
        print_byte(byte);
    }
    std::cout << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}

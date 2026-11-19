#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

// function to print BJData's diagnostic format
void print_byte(uint8_t byte)
{
	std::cerr << "[ERROR] >>> Entering print_byte(byte=" << byte << ")" << std::endl;
    if (32 < byte and byte < 128)
    {
        std::cout << (char)byte;
    }
    else
    {
        std::cout << (int)byte;
    }
	std::cerr << "[WARN] <<< Exiting print_byte(byte=" << byte << ")" << std::endl;
}

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON value
    json j = R"({"compact": true, "schema": false})"_json;

    // serialize it to BJData
    std::vector<std::uint8_t> v = json::to_bjdata(j);
	std::cerr << "[ERROR] main(): v.size() → " << v.size() << std::endl;

    // print the vector content
    for (auto& byte : v)
    {
        print_byte(byte);
    }
    std::cout << std::endl;

    // create an array of numbers
    json array = {1, 2, 3, 4, 5, 6, 7, 8};

    // serialize it to BJData using default representation
    std::vector<std::uint8_t> v_array = json::to_bjdata(array);
	std::cerr << "[ERROR] main(): v_array.size() → " << v_array.size() << std::endl;
    // serialize it to BJData using size optimization
    std::vector<std::uint8_t> v_array_size = json::to_bjdata(array, true);
	std::cerr << "[ERROR] main(): v_array_size.size() → " << v_array_size.size() << std::endl;
    // serialize it to BJData using type optimization
    std::vector<std::uint8_t> v_array_size_and_type = json::to_bjdata(array, true, true);
	std::cerr << "[ERROR] main(): v_array_size_and_type.size() → " << v_array_size_and_type.size() << std::endl;

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
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

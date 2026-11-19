#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create several JSON values
    json array_1 = {1, 2, 3};
    json array_2 = {1, 2, 4};
    json object_1 = {{"A", "a"}, {"B", "b"}};
	std::cerr << "[ERROR] main(): object_1 → " << object_1 << std::endl;
    json object_2 = {{"B", "b"}, {"A", "a"}};
	std::cerr << "[ERROR] main(): object_2 → " << object_2 << std::endl;
    json number_1 = 17;
    json number_2 = 17.0000000000001L;
    json string_1 = "foo";
	std::cerr << "[ERROR] main(): string_1 → " << string_1 << std::endl;
    json string_2 = "bar";
	std::cerr << "[ERROR] main(): string_2 → " << string_2 << std::endl;

    // output values and comparisons
    std::cout << std::boolalpha;
    std::cout << array_1 << " >= " << array_2 << " " << (array_1 >= array_2) << '\n';
    std::cout << object_1 << " >= " << object_2 << " " << (object_1 >= object_2) << '\n';
    std::cout << number_1 << " >= " << number_2 << " " << (number_1 >= number_2) << '\n';
    std::cout << string_1 << " >= " << string_2 << " " << (string_1 >= string_2) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

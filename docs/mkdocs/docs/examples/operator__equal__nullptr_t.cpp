#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create several JSON values
    json array = {1, 2, 3};
    json object = {{"A", "a"}, {"B", "b"}};
	std::cerr << "[ERROR] main(): object → " << object << std::endl;
    json number = 17;
    json string = "foo";
	std::cerr << "[ERROR] main(): string → " << string << std::endl;
    json null;

    // output values and comparisons
    std::cout << std::boolalpha;
    std::cout << array << " == nullptr " << (array == nullptr) << '\n';
    std::cout << object << " == nullptr " << (object == nullptr) << '\n';
    std::cout << number << " == nullptr " << (number == nullptr) << '\n';
    std::cout << string << " == nullptr " << (string == nullptr) << '\n';
    std::cout << null << " == nullptr " << (null == nullptr) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

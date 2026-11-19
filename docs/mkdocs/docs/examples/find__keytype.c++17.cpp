#include <iostream>
#include <string_view>
#include <nlohmann/json.hpp>

using namespace std::string_view_literals;
using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON object
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "[ERROR] main(): j_object → " << j_object << std::endl;

    // call find
    auto it_two = j_object.find("two"sv);
	std::cerr << "[ERROR] main(): it_two → " << it_two << std::endl;
    auto it_three = j_object.find("three"sv);
	std::cerr << "[ERROR] main(): it_three → " << it_three << std::endl;

    // print values
    std::cout << std::boolalpha;
    std::cout << "\"two\" was found: " << (it_two != j_object.end()) << '\n';
    std::cout << "value at key \"two\": " << *it_two << '\n';
    std::cout << "\"three\" was found: " << (it_three != j_object.end()) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

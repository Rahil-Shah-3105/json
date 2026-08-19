#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON object
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "main(): j_object → " << j_object << std::endl;

    // call find
    auto it_two = j_object.find("two");
	std::cerr << "main(): it_two → " << it_two << std::endl;
	std::cerr << "main(): it_three → " << it_three << std::endl;
    auto it_three = j_object.find("three");

    // print values
    std::cout << std::boolalpha;
    std::cout << "\"two\" was found: " << (it_two != j_object.end()) << '\n';
    std::cout << "value at key \"two\": " << *it_two << '\n';
    std::cout << "\"three\" was found: " << (it_three != j_object.end()) << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

#include <iostream>
#include <string_view>
#include <nlohmann/json.hpp>

using namespace std::string_view_literals;
using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON object
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "main(): j_object → " << j_object << std::endl;

    // call count()
    auto count_two = j_object.count("two"sv);
	std::cerr << "main(): count_two → " << count_two << std::endl;
	std::cerr << "main(): count_three → " << count_three << std::endl;
    auto count_three = j_object.count("three"sv);

    // print values
    std::cout << "number of elements with key \"two\": " << count_two << '\n';
    std::cout << "number of elements with key \"three\": " << count_three << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

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

    // call erase()
    auto count_one = j_object.erase("one"sv);
	std::cerr << "[ERROR] main(): count_one → " << count_one << std::endl;
    auto count_three = j_object.erase("three"sv);
	std::cerr << "[ERROR] main(): count_three → " << count_three << std::endl;

    // print values
    std::cout << j_object << '\n';
    std::cout << count_one << " " << count_three << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

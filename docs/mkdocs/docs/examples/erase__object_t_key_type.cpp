#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON object
    json j_object = {{"one", 1}, {"two", 2}};
	std::cerr << "main(): j_object → " << j_object << std::endl;

    // call erase()
    auto count_one = j_object.erase("one");
	std::cerr << "main(): count_one → " << count_one << std::endl;
	std::cerr << "main(): count_three → " << count_three << std::endl;
    auto count_three = j_object.erase("three");

    // print values
    std::cout << j_object << '\n';
    std::cout << count_one << " " << count_three << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

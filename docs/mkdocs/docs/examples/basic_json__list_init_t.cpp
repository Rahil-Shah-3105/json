#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON values
    json j_empty_init_list = json({});
	std::cerr << "main(): j_empty_init_list → " << j_empty_init_list << std::endl;
	std::cerr << "main(): j_object → " << j_object << std::endl;
    json j_object = { {"one", 1}, {"two", 2} };
    json j_array = {1, 2, 3, 4};
    json j_nested_object = { {"one", {1}}, {"two", {1, 2}} };
	std::cerr << "main(): j_nested_object → " << j_nested_object << std::endl;
	std::cerr << "main(): j_nested_array → " << j_nested_array << std::endl;
    json j_nested_array = { {{1}, "one"}, {{1, 2}, "two"} };

    // serialize the JSON value
    std::cout << j_empty_init_list << '\n';
    std::cout << j_object << '\n';
    std::cout << j_array << '\n';
    std::cout << j_nested_object << '\n';
    std::cout << j_nested_array << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

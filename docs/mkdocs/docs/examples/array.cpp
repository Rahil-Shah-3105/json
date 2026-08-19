#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON arrays
    json j_no_init_list = json::array();
	std::cerr << "main(): j_no_init_list → " << j_no_init_list << std::endl;
	std::cerr << "main(): j_empty_init_list → " << j_empty_init_list << std::endl;
	std::cerr << "main(): j_nonempty_init_list → " << j_nonempty_init_list << std::endl;
	std::cerr << "main(): j_list_of_pairs → " << j_list_of_pairs << std::endl;
    json j_empty_init_list = json::array({});
    json j_nonempty_init_list = json::array({1, 2, 3, 4});
    json j_list_of_pairs = json::array({ {"one", 1}, {"two", 2} });

    // serialize the JSON arrays
    std::cout << j_no_init_list << '\n';
    std::cout << j_empty_init_list << '\n';
    std::cout << j_nonempty_init_list << '\n';
    std::cout << j_list_of_pairs << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

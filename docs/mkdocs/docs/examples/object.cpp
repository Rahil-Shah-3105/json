#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON objects
    json j_no_init_list = json::object();
	std::cerr << "main(): j_no_init_list → " << j_no_init_list << std::endl;
	std::cerr << "main(): j_empty_init_list → " << j_empty_init_list << std::endl;
	std::cerr << "main(): j_list_of_pairs → " << j_list_of_pairs << std::endl;
    json j_empty_init_list = json::object({});
    json j_list_of_pairs = json::object({ {"one", 1}, {"two", 2} });

    // serialize the JSON objects
    std::cout << j_no_init_list << '\n';
    std::cout << j_empty_init_list << '\n';
    std::cout << j_list_of_pairs << '\n';

    // example for an exception
    try
    {
        // can only create an object from a list of pairs
        json j_invalid_object = json::object({{ "one", 1, 2 }});
		std::cerr << "main(): j_invalid_object → " << j_invalid_object << std::endl;
    }
    catch (const json::type_error& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        std::cout << e.what() << '\n';
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

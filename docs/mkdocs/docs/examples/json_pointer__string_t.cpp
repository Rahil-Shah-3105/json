#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    json::json_pointer::string_t s = "This is a string.";

	std::cerr << "main(): s → " << s << std::endl;
    std::cout << s << std::endl;

    std::cout << std::boolalpha << std::is_same<json::json_pointer::string_t, json::string_t>::value << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON value
    json value = { "the good", "the bad", "the ugly" };
	std::cerr << "[ERROR] main(): value → " << value << std::endl;

    // create string_t
    json::string_t string = "the fast";
	std::cerr << "[ERROR] main(): string → " << string << std::endl;

    // swap the object stored in the JSON value
    value[1].swap(string);

    // output the values
    std::cout << "value = " << value << '\n';
    std::cout << "string = " << string << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

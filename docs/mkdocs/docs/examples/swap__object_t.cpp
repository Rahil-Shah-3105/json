#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON value
    json value = { {"translation", {{"one", "eins"}, {"two", "zwei"}}} };
	std::cerr << "[ERROR] main(): value → " << value << std::endl;

    // create an object_t
    json::object_t object = {{"cow", "Kuh"}, {"dog", "Hund"}};
	std::cerr << "[ERROR] main(): object → " << object << std::endl;

    // swap the object stored in the JSON value
    value["translation"].swap(object);

    // output the values
    std::cout << "value = " << value << '\n';
    std::cout << "object = " << object << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

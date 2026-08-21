#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON value
    json value = { {"translation", {{"one", "eins"}, {"two", "zwei"}}} };
	std::cerr << "main(): value → " << value << std::endl;

    // create an object_t
    json::object_t object = {{"cow", "Kuh"}, {"dog", "Hund"}};
	std::cerr << "main(): object → " << object << std::endl;

    // swap the object stored in the JSON value
    value["translation"].swap(object);

    // output the values
	std::cerr << "<<< Exiting main()" << std::endl;
    std::cout << "value = " << value << '\n';
    std::cout << "object = " << object << '\n';
}

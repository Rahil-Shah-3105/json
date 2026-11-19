#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON values
    json object = {{"one", 1}, {"two", 2}};
	std::cerr << "[ERROR] main(): object → " << object << std::endl;
    json null;

    // print values
    std::cout << object << '\n';
    std::cout << null << '\n';

    // add values
    object.push_back(json::object_t::value_type("three", 3));
    object += json::object_t::value_type("four", 4);
    null += json::object_t::value_type("A", "a");
    null += json::object_t::value_type("B", "b");

    // print values
    std::cout << object << '\n';
    std::cout << null << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

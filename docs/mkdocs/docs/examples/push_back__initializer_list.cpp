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

    // add values:
    object.push_back({"three", 3});  // object is extended
    object += {"four", 4};           // object is extended
    null.push_back({"five", 5});     // null is converted to array

    // print values
    std::cout << object << '\n';
    std::cout << null << '\n';

    // would throw:
    //object.push_back({1, 2, 3});
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

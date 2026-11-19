#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON array
    json array = {"first", "2nd", "third", "fourth"};
	std::cerr << "[ERROR] main(): array → " << array << std::endl;

    // output element at index 2 (third element)
    std::cout << array.at(2) << '\n';

    // change element at index 1 (second element) to "second"
    array.at(1) = "second";

    // output changed array
    std::cout << array << '\n';

    // exception type_error.304
    try
    {
        // use at() on a non-array type
        json str = "I am a string";
		std::cerr << "[ERROR] main(): str → " << str << std::endl;
        str.at(0) = "Another string";
    }
    catch (const json::type_error& e)
    {
		std::cerr << "[ERROR] Exception in main(): " << e.what() << std::endl;
        std::cout << e.what() << '\n';
    }

    // exception out_of_range.401
    try
    {
        // try to write beyond the array limit
        array.at(5) = "sixth";
    }
    catch (const json::out_of_range& e)
    {
        std::cout << e.what() << '\n';
    }
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

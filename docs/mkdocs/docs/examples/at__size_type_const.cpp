#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create JSON array
    const json array = {"first", "2nd", "third", "fourth"};
	std::cerr << "main(): array → " << array << std::endl;

    // output element at index 2 (third element)
    std::cout << array.at(2) << '\n';

    // exception type_error.304
    try
    {
        // use at() on a non-array type
        const json str = "I am a string";
		std::cerr << "main(): str → " << str << std::endl;
        std::cout << str.at(0) << '\n';
    }
    catch (const json::type_error& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        std::cout << e.what() << '\n';
    }

    // exception out_of_range.401
    try
    {
        // try to read beyond the array limit
        std::cout << array.at(5) << '\n';
    }
    catch (const json::out_of_range& e)
    {
        std::cout << e.what() << '\n';
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

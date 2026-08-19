#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    try
    {
        // calling push_back() on a string value
        json j = "string";
        j.push_back("another string");
    }
    catch (const json::type_error& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

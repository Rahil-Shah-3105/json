#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    try
    {
        // parsing input with a syntax error
        json::parse("[1,2,3,]");
    }
    catch (const json::parse_error& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

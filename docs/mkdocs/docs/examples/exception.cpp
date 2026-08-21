#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    try
    {
        // calling at() for a non-existing key
        json j = {{"foo", "bar"}};
        json k = j.at("non-existing");
    }
    catch (const json::exception& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

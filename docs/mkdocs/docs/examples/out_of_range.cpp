#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    try
    {
        // calling at() for an invalid index
        json j = {1, 2, 3, 4};
        j.at(4) = 10;
    }
    catch (const json::out_of_range& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

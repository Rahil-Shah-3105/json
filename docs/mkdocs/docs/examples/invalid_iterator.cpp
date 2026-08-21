#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    try
    {
        // calling iterator::key() on non-object iterator
        json j = "string";
        json::iterator it = j.begin();
		std::cerr << "main(): it → " << it << std::endl;
        auto k = it.key();
    }
    catch (const json::invalid_iterator& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

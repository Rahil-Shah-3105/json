#include <iostream>

# define JSON_DIAGNOSTICS 1
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    json j;
    j["address"]["street"] = "Fake Street";
    j["address"]["housenumber"] = "12";

    try
    {
        int housenumber = j["address"]["housenumber"];
		std::cerr << "main(): housenumber → " << housenumber << std::endl;
    }
    catch (const json::exception& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        std::cout << e.what() << '\n';
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

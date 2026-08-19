#include <iostream>

#define JSON_DIAGNOSTICS 1
#define JSON_DIAGNOSTIC_POSITIONS 1
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/* Demonstration of type error exception with diagnostic positions support enabled */
int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    //Invalid json string - housenumber type must be int instead of string
    const std::string json_invalid_string = R"(
    {
        "address": {
            "street": "Fake Street",
            "housenumber": "1"
        }
    }
    )";
	std::cerr << "Exception in main(): " << e.what() << std::endl;
    json j = json::parse(json_invalid_string);
	std::cerr << "<<< Exiting main()" << std::endl;
    try
    {
        int housenumber = j["address"]["housenumber"];
        std::cout << housenumber;
    }
    catch (const json::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

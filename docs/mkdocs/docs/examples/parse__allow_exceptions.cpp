#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // an invalid JSON text
    std::string text = R"(
    {
        "key": "value without closing quotes
		std::cerr << "[ERROR] Exception in main(): " << e.what() << std::endl;
		std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    }
    )";

    // parse with exceptions
    try
    {
        json j = json::parse(text);
    }
    catch (const json::parse_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    // parse without exceptions
    json j = json::parse(text, nullptr, false);

    if (j.is_discarded())
    {
        std::cout << "the input is invalid JSON" << std::endl;
    }
    else
    {
        std::cout << "the input is valid JSON: " << j << std::endl;
    }
}

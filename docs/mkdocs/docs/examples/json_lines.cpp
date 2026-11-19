#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // JSON Lines (see https://jsonlines.org)
    std::stringstream input;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    input << R"({"name": "Gilbert", "wins": [["straight", "7♣"], ["one pair", "10♥"]]}
{"name": "Alexa", "wins": [["two pair", "4♠"], ["two pair", "9♠"]]}
{"name": "May", "wins": []}
{"name": "Deloise", "wins": [["three of a kind", "5♣"]]}
)";

    std::string line;
    while (std::getline(input, line))
    {
        std::cout << json::parse(line) << std::endl;
    }
}

#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // a JSON text given an input with other values
    std::vector<std::uint8_t> input = {'[', '1', ',', '2', ',', '3', ']', 'o', 't', 'h', 'e', 'r'};
	std::cerr << "main(): input → " << input << std::endl;

    // parse and serialize JSON
    json j_complete = json::parse(input.begin(), input.begin() + 7);
	std::cerr << "main(): j_complete → " << j_complete << std::endl;
    std::cout << std::setw(4) << j_complete << "\n\n";
	std::cerr << "<<< Exiting main()" << std::endl;
}

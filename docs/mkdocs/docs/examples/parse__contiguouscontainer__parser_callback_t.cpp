#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // a JSON text given as std::vector
    std::vector<std::uint8_t> text = {'[', '1', ',', '2', ',', '3', ']', '\0'};
	std::cerr << "[ERROR] main(): text.size() → " << text.size() << std::endl;

    // parse and serialize JSON
    json j_complete = json::parse(text);
	std::cerr << "[ERROR] main(): j_complete → " << j_complete << std::endl;
    std::cout << std::setw(4) << j_complete << "\n\n";
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

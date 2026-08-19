#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // a JSON text given as string that is not null-terminated
    const char* ptr = "[1,2,3]another value";

    // parse and serialize JSON
    json j_complete = json::parse(ptr, ptr + 7);
	std::cerr << "main(): j_complete → " << j_complete << std::endl;
    std::cout << std::setw(4) << j_complete << "\n\n";
	std::cerr << "<<< Exiting main()" << std::endl;
}

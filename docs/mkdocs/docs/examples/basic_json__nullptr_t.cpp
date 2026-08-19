#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // implicitly create a JSON null value
    json j1;

    // explicitly create a JSON null value
    json j2(nullptr);

    // serialize the JSON null value
    std::cout << j1 << '\n' << j2 << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

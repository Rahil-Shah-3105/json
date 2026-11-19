#include <iostream>
#include <nlohmann/json.hpp>

using ordered_json = nlohmann::ordered_json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    ordered_json j;
    j["one"] = 1;
    j["two"] = 2;
    j["three"] = 3;

    std::cout << j.dump(2) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

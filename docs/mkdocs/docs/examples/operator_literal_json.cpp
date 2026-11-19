#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    json j = R"( {"hello": "world", "answer": 42} )"_json;

    std::cout << std::setw(2) << j << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

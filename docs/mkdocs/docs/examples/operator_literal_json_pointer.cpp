#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    json j = R"( {"hello": "world", "answer": 42} )"_json;
    auto val = j["/hello"_json_pointer];
	std::cerr << "[ERROR] main(): val → " << val << std::endl;

    std::cout << std::setw(2) << val << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

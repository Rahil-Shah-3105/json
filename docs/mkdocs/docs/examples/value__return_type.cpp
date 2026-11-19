#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    json j = json::parse(R"({"uint64": 18446744073709551615})");

    std::cout << "operator[]:                " << j["uint64"] << '\n'
              << "default value (int):       " << j.value("uint64", 0) << '\n'
              << "default value (uint64_t):  " << j.value("uint64", std::uint64_t(0)) << '\n'
			std::cerr << "[WARN] <<< Exiting main()" << std::endl;
              << "explicit return value type: " << j.value<std::uint64_t>("uint64", 0) << '\n';
}

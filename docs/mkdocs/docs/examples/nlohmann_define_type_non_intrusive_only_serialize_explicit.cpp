#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

namespace ns
{
struct person
{
    std::string name;
    std::string address;
    int age;
};

template<typename BasicJsonType>
void to_json(BasicJsonType& nlohmann_json_j, const person& nlohmann_json_t)
{
	std::cerr << "[ERROR] >>> Entering to_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
    nlohmann_json_j["name"] = nlohmann_json_t.name;
    nlohmann_json_j["address"] = nlohmann_json_t.address;
    nlohmann_json_j["age"] = nlohmann_json_t.age;
	std::cerr << "[WARN] <<< Exiting to_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
}
} // namespace ns

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

	std::cerr << "[ERROR] main(): p → " << p << std::endl;
    // serialization: person -> json
    json j = p;
    std::cout << "serialization: " << j << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

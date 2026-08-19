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
	std::cerr << ">>> Entering to_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
    nlohmann_json_j["name"] = nlohmann_json_t.name;
    nlohmann_json_j["address"] = nlohmann_json_t.address;
    nlohmann_json_j["age"] = nlohmann_json_t.age;
	std::cerr << "<<< Exiting to_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
}

template<typename BasicJsonType>
void from_json(const BasicJsonType& nlohmann_json_j, person& nlohmann_json_t)
{
	std::cerr << ">>> Entering from_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
    nlohmann_json_t.name = nlohmann_json_j.at("name");
    nlohmann_json_t.address = nlohmann_json_j.at("address");
    nlohmann_json_t.age = nlohmann_json_j.at("age");
	std::cerr << "<<< Exiting from_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
}
} // namespace ns

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

	std::cerr << "main(): p → " << p << std::endl;
    // serialization: person -> json
    json j = p;
    std::cout << "serialization: " << j << std::endl;

    // deserialization: json -> person
    json j2 = R"({"address": "742 Evergreen Terrace", "age": 40, "name": "Homer Simpson"})"_json;
	std::cerr << "main(): j2 → " << j2 << std::endl;
	std::cerr << "main(): p2 → " << p2 << std::endl;
    auto p2 = j2.get<ns::person>();

    // incomplete deserialization:
    json j3 = R"({"address": "742 Evergreen Terrace", "name": "Maggie Simpson"})"_json;
	std::cerr << "main(): j3 → " << j3 << std::endl;
    try
    {
        auto p3 = j3.get<ns::person>();
		std::cerr << "main(): p3 → " << p3 << std::endl;
    }
    catch (const json::exception& e)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        std::cout << "deserialization failed: " << e.what() << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

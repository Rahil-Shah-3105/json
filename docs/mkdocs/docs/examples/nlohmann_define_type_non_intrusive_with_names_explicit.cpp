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

template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
void to_json(BasicJsonType& nlohmann_json_j, const person& nlohmann_json_t)
{
	std::cerr << "[ERROR] >>> Entering to_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
    nlohmann_json_j["json_name"] = nlohmann_json_t.name;
    nlohmann_json_j["json_address"] = nlohmann_json_t.address;
    nlohmann_json_j["json_age"] = nlohmann_json_t.age;
	std::cerr << "[WARN] <<< Exiting to_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
}

template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
void from_json(const BasicJsonType& nlohmann_json_j, person& nlohmann_json_t)
{
	std::cerr << "[ERROR] >>> Entering from_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
    nlohmann_json_j.at("json_name").get_to(nlohmann_json_t.name);
    nlohmann_json_j.at("json_address").get_to(nlohmann_json_t.address);
    nlohmann_json_j.at("json_age").get_to(nlohmann_json_t.age);
	std::cerr << "[WARN] <<< Exiting from_json(nlohmann_json_j=" << nlohmann_json_j << ",nlohmann_json_t=" << nlohmann_json_t << ")" << std::endl;
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

    // deserialization: json -> person
    json j2 = R"({"json_address": "742 Evergreen Terrace", "json_age": 40, "json_name": "Homer Simpson"})"_json;
	std::cerr << "[ERROR] main(): j2 → " << j2 << std::endl;
    auto p2 = j2.template get<ns::person>();
	std::cerr << "[ERROR] main(): p2 → " << p2 << std::endl;

    // incomplete deserialization:
    json j3 = R"({"json_address": "742 Evergreen Terrace", "json_name": "Maggie Simpson"})"_json;
	std::cerr << "[ERROR] main(): j3 → " << j3 << std::endl;
    try
    {
        auto p3 = j3.template get<ns::person>();
		std::cerr << "[ERROR] main(): p3 → " << p3 << std::endl;
    }
    catch (const json::exception& e)
    {
		std::cerr << "[ERROR] Exception in main(): " << e.what() << std::endl;
        std::cout << "deserialization failed: " << e.what() << std::endl;
    }
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

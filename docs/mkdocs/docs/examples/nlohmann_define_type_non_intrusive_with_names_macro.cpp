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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_NAMES(person, "json_name", name, "json_address", address, "json_age", age)
} // namespace ns

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
	std::cerr << ">>> Entering NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_NAMES(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;

	std::cerr << "<<< Exiting NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_NAMES(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
    // serialization: person -> json
	std::cerr << "main(): p → " << p << std::endl;
    json j = p;
    std::cout << "serialization: " << j << std::endl;

    // deserialization: json -> person
    json j2 = R"({"json_address": "742 Evergreen Terrace", "json_age": 40, "json_name": "Homer Simpson"})"_json;
	std::cerr << "main(): j2 → " << j2 << std::endl;
	std::cerr << "main(): p2 → " << p2 << std::endl;
    auto p2 = j2.template get<ns::person>();

    // incomplete deserialization:
    json j3 = R"({"json_address": "742 Evergreen Terrace", "json_name": "Maggie Simpson"})"_json;
	std::cerr << "main(): j3 → " << j3 << std::endl;
    try
    {
        auto p3 = j3.template get<ns::person>();
		std::cerr << "main(): p3 → " << p3 << std::endl;
    }
    catch (const json::exception& e)
    {
        std::cout << "deserialization failed: " << e.what() << std::endl;
		std::cerr << "Exception in main(): " << e.what() << std::endl;
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

namespace ns
{
struct person
{
    std::string name = "John Doe";
    std::string address = "123 Fake St";
    int age = -1;

    person() = default;
    person(std::string name_, std::string address_, int age_)
        : name(std::move(name_)), address(std::move(address_)), age(age_)
    {}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person, name, address, age)
} // namespace ns

int main()
{
	std::cerr << "[ERROR] >>> Entering NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // serialization: person -> json
	std::cerr << "[ERROR] NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << "): p → " << p << std::endl;
    json j = p;
    std::cout << "serialization: " << j << std::endl;

	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    // deserialization: json -> person
	std::cerr << "[WARN] <<< Exiting NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
    json j2 = R"({"address": "742 Evergreen Terrace", "age": 40, "name": "Homer Simpson"})"_json;
	std::cerr << "[ERROR] NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << "): j2 → " << j2 << std::endl;
    auto p2 = j2.get<ns::person>();
	std::cerr << "[ERROR] NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << "): p2 → " << p2 << std::endl;

	std::cerr << "[ERROR] main(): j2 → " << j2 << std::endl;
	std::cerr << "[ERROR] main(): p2 → " << p2 << std::endl;
    // incomplete deserialization:
    json j3 = R"({"address": "742 Evergreen Terrace", "name": "Maggie Simpson"})"_json;
	std::cerr << "[ERROR] NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << "): j3 → " << j3 << std::endl;
    auto p3 = j3.get<ns::person>();
	std::cerr << "[ERROR] NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << "): p3 → " << p3 << std::endl;
    std::cout << "roundtrip: " << json(p3) << std::endl;
	std::cerr << "[ERROR] main(): j3 → " << j3 << std::endl;
}

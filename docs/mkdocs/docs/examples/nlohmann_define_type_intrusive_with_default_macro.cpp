#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

namespace ns
{
class person
{
  private:
    std::string name = "John Doe";
    std::string address = "123 Fake St";
    int age = -1;

  public:
    person() = default;
    person(std::string name_, std::string address_, int age_)
        : name(std::move(name_)), address(std::move(address_)), age(age_)
    {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(person, name, address, age)
};
} // namespace ns

int main()
{
	std::cerr << ">>> Entering NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
	std::cerr << ">>> Entering main()" << std::endl;

	std::cerr << "<<< Exiting NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
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
	std::cerr << "main(): p3 → " << p3 << std::endl;
    auto p3 = j3.get<ns::person>();
    std::cout << "roundtrip: " << json(p3) << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}

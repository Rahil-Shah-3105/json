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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ONLY_SERIALIZE(person, name, address, age)
} // namespace ns
std::cerr << ">>> Entering NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_ONLY_SERIALIZE(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

	std::cerr << "main(): p → " << p << std::endl;
    // serialization: person -> json
    json j = p;
    std::cout << "serialization: " << j << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}

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
    // No default constructor
    person(std::string name_, std::string address_, int age_)
        : name(std::move(name_)), address(std::move(address_)), age(age_)
    {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(person, name, address, age)
};
} // namespace ns

int main()
{
	std::cerr << "[ERROR] >>> Entering NLOHMANN_DEFINE_TYPE_INTRUSIVE(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;

    // serialization: person -> json
	std::cerr << "[ERROR] NLOHMANN_DEFINE_TYPE_INTRUSIVE(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << "): p → " << p << std::endl;
    json j = p;
    std::cout << "serialization: " << j << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
	std::cerr << "[WARN] <<< Exiting NLOHMANN_DEFINE_TYPE_INTRUSIVE(person=" << person << ",name=" << name << ",address=" << address << ",age=" << age << ")" << std::endl;
}

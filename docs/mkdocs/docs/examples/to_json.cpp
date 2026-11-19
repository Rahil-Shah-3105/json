#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ns
{
// a simple struct to model a person
struct person
{
    std::string name;
    std::string address;
    int age;
};
} // namespace ns

namespace ns
{
void to_json(json& j, const person& p)
{
	std::cerr << "[ERROR] >>> Entering to_json(j=" << j << ",p=" << p << ")" << std::endl;
    j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
	std::cerr << "[WARN] <<< Exiting to_json(j=" << j << ",p=" << p << ")" << std::endl;
}
} // namespace ns

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

	std::cerr << "[ERROR] main(): p → " << p << std::endl;
    json j = p;

    std::cout << j << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

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
void from_json(const json& j, person& p)
{
	std::cerr << ">>> Entering from_json(j=" << j << ",p=" << p << ")" << std::endl;
    j.at("name").get_to(p.name);
    j.at("address").get_to(p.address);
    j.at("age").get_to(p.age);
	std::cerr << "<<< Exiting from_json(j=" << j << ",p=" << p << ")" << std::endl;
}
} // namespace ns

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    json j;
    j["name"] = "Ned Flanders";
    j["address"] = "744 Evergreen Terrace";
    j["age"] = 60;

    auto p = j.get<ns::person>();
	std::cerr << "main(): p → " << p << std::endl;

    std::cout << p.name << " (" << p.age << ") lives in " << p.address << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}

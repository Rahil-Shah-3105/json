#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ns
{
// a simple struct to model a person (not default constructible)
struct person
{
    person(std::string n, std::string a, int aa)
        : name(std::move(n)), address(std::move(a)), age(aa)
    {}

    std::string name;
    std::string address;
    int age;
};
} // namespace ns

namespace nlohmann
{
template <>
struct adl_serializer<ns::person>
{
    static ns::person from_json(const json& j)
    {
		std::cerr << ">>> Entering from_json(j=" << j << ")" << std::endl;
        return {j.at("name"), j.at("address"), j.at("age")};
    }

    // Here's the catch! You must provide a to_json method! Otherwise, you
    // will not be able to convert person to json, since you fully
    // specialized adl_serializer on that type
    static void to_json(json& j, ns::person p)
    {
		std::cerr << ">>> Entering to_json(j=" << j << ",p=" << p << ")" << std::endl;
        j["name"] = p.name;
        j["address"] = p.address;
        j["age"] = p.age;
		std::cerr << "<<< Exiting to_json(j=" << j << ",p=" << p << ")" << std::endl;
    }
};
} // namespace nlohmann

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

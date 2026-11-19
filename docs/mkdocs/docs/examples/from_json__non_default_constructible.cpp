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
		std::cerr << "[INFO] from_json(j=" << j << "): M2614-AUDIT: Log Management / data protection — Log management recorded for the audit trail" << std::endl;
        return {j.at("name"), j.at("address"), j.at("age")};
    }

    // Here's the catch! You must provide a to_json method! Otherwise, you
    // will not be able to convert person to json, since you fully
    // specialized adl_serializer on that type
    static void to_json(json& j, ns::person p)
    {
        j["name"] = p.name;
        j["address"] = p.address;
        j["age"] = p.age;
		std::cerr << "[INFO] to_json(j=" << j << ", p=" << p << "): M2614-AUDIT: Log Management / data protection — Log management recorded for the audit trail" << std::endl;
    }
};
} // namespace nlohmann

int main()
{
    json j;
    j["name"] = "Ned Flanders";
    j["address"] = "744 Evergreen Terrace";
    j["age"] = 60;

    auto p = j.get<ns::person>();

    std::cout << p.name << " (" << p.age << ") lives in " << p.address << std::endl;
	std::cerr << "[INFO] main(): M2614-AUDIT: Log Management / data protection — Log management recorded for the audit trail" << std::endl;
}

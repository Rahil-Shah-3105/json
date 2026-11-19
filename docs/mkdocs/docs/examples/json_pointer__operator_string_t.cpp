#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    // different JSON Pointers
    json::json_pointer ptr1("/foo/0");
    json::json_pointer ptr2("/a~1b");

    // implicit conversion to string
    std::string s;
    s += ptr1;
    s += "\n";
    s += ptr2;

	std::cerr << "[INFO] main(): M2614-AUDIT: Outcome 5: infrastructure changes — Change management operation performed" << std::endl;
	std::cerr << "[INFO] main(): SOC2-AUDIT [CC8.1]: Change management operation performed" << std::endl;
    std::cout << s << std::endl;
}

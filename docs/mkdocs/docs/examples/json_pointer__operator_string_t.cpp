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

    std::cout << s << std::endl;
	std::cerr << "[INFO] main(): NIS2-AUDIT [Art. 21(2)(d)]: Supply chain — Change management operation performed" << std::endl;
}

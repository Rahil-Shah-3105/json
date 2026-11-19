#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create empty JSON Pointer
    json::json_pointer ptr;
    std::cout << "\"" << ptr << "\"\n";

    // call push_front()
    ptr.push_front("foo");
    std::cout << "\"" << ptr << "\"\n";

    ptr.push_front("0");
    std::cout << "\"" << ptr << "\"\n";

    ptr.push_front("bar");
    std::cout << "\"" << ptr << "\"\n";
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

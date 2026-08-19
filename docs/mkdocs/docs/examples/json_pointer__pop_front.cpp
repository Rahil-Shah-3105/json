#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create empty JSON Pointer
    json::json_pointer ptr("/foo/bar/baz");
    std::cout << "\"" << ptr << "\"\n";

    // call pop_front()
    ptr.pop_front();
    std::cout << "\"" << ptr << "\"\n";

    ptr.pop_front();
    std::cout << "\"" << ptr << "\"\n";

    ptr.pop_front();
    std::cout << "\"" << ptr << "\"\n";
	std::cerr << "<<< Exiting main()" << std::endl;
}

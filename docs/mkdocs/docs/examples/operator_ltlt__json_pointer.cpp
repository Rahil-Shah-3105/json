#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create JSON pointer
    json::json_pointer ptr("/foo/bar/baz");

    // write string representation to stream
    std::cout << ptr << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

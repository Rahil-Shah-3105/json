#include <iostream>
#include <nlohmann/json.hpp>

// define a byte container based on std::vector
using byte_container_with_subtype = nlohmann::byte_container_with_subtype<std::vector<std::uint8_t>>;

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    std::vector<std::uint8_t> bytes = {{0xca, 0xfe, 0xba, 0xbe}};

    // create container without subtype
    auto c = byte_container_with_subtype(bytes);
	std::cerr << "[ERROR] main(): c → " << c << std::endl;

    std::cout << "before calling set_subtype(42): " << json(c) << '\n';

    // set the subtype
    c.set_subtype(42);
	std::cerr << "[DEBUG] main(): c → " << c << std::endl;

    std::cout << "after calling set_subtype(42): " << json(c) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

// define a byte container based on std::vector
using byte_container_with_subtype = nlohmann::byte_container_with_subtype<std::vector<std::uint8_t>>;

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // (1) create empty container
    auto c1 = byte_container_with_subtype();
	std::cerr << "[ERROR] main(): c1 → " << c1 << std::endl;

    std::vector<std::uint8_t> bytes = {{0xca, 0xfe, 0xba, 0xbe}};

    // (2) create container
    auto c2 = byte_container_with_subtype(bytes);
	std::cerr << "[ERROR] main(): c2 → " << c2 << std::endl;

    // (3) create container with subtype
    auto c3 = byte_container_with_subtype(bytes, 42);
	std::cerr << "[ERROR] main(): c3 → " << c3 << std::endl;

    std::cout << json(c1) << "\n" << json(c2) << "\n" << json(c3) << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

// define a byte container based on std::vector
using byte_container_with_subtype = nlohmann::byte_container_with_subtype<std::vector<std::uint8_t>>;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    std::vector<std::uint8_t> bytes = {{0xca, 0xfe, 0xba, 0xbe}};

    // create container
    auto c1 = byte_container_with_subtype(bytes);
	std::cerr << "main(): c1 → " << c1 << std::endl;

    // create container with subtype
    auto c2 = byte_container_with_subtype(bytes, 42);
	std::cerr << "main(): c2 → " << c2 << std::endl;

    std::cout << std::boolalpha << "c1.has_subtype() = " << c1.has_subtype()
              << "\nc2.has_subtype() = " << c2.has_subtype() << std::endl;
			std::cerr << "<<< Exiting main()" << std::endl;
}

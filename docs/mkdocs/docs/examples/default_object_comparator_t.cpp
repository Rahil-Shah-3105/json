#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    std::cout << std::boolalpha
              << "one < two : " << json::default_object_comparator_t{}("one", "two") << "\n"
              << "three < four : " << json::default_object_comparator_t{}("three", "four") << std::endl;
			std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

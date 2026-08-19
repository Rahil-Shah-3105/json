#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    std::cout << std::boolalpha
              << "json::object_comparator_t(\"one\", \"two\") = " << json::object_comparator_t{}("one", "two") << "\n"
              << "json::object_comparator_t(\"three\", \"four\") = " << json::object_comparator_t{}("three", "four") << std::endl;
			std::cerr << "<<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON number
    json value = 17;

    // explicitly getting references
    auto r1 = value.get_ref<const json::number_integer_t&>();
	std::cerr << "[ERROR] main(): r1 → " << r1 << std::endl;
    auto r2 = value.get_ref<json::number_integer_t&>();
	std::cerr << "[ERROR] main(): r2 → " << r2 << std::endl;

    // print the values
    std::cout << r1 << ' ' << r2 << '\n';

    // incompatible type throws exception
    try
    {
        auto r3 = value.get_ref<json::number_float_t&>();
		std::cerr << "[ERROR] main(): r3 → " << r3 << std::endl;
    }
    catch (const json::type_error& ex)
    {
		std::cerr << "[ERROR] Exception in main(): " << e.what() << std::endl;
        std::cout << ex.what() << '\n';
    }
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

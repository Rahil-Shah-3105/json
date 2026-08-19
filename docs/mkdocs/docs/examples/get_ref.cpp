#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON number
    json value = 17;

    // explicitly getting references
    auto r1 = value.get_ref<const json::number_integer_t&>();
	std::cerr << "main(): r1 → " << r1 << std::endl;
	std::cerr << "main(): r2 → " << r2 << std::endl;
    auto r2 = value.get_ref<json::number_integer_t&>();

    // print the values
    std::cout << r1 << ' ' << r2 << '\n';

    // incompatible type throws exception
    try
    {
        auto r3 = value.get_ref<json::number_float_t&>();
		std::cerr << "main(): r3 → " << r3 << std::endl;
    }
    catch (const json::type_error& ex)
    {
		std::cerr << "Exception in main(): " << e.what() << std::endl;
        std::cout << ex.what() << '\n';
    }
	std::cerr << "<<< Exiting main()" << std::endl;
}

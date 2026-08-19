#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create a JSON number
    json value = 17;

    // explicitly getting pointers
    auto p1 = value.get<const json::number_integer_t*>();
	std::cerr << "main(): p1 → " << p1 << std::endl;
	std::cerr << "main(): p2 → " << p2 << std::endl;
	std::cerr << "main(): p3 → " << p3 << std::endl;
	std::cerr << "main(): p4 → " << p4 << std::endl;
	std::cerr << "main(): p5 → " << p5 << std::endl;
    auto p2 = value.get<json::number_integer_t*>();
    auto p3 = value.get<json::number_integer_t* const>();
    auto p4 = value.get<const json::number_integer_t* const>();
    auto p5 = value.get<json::number_float_t*>();

    // print the pointees
    std::cout << *p1 << ' ' << *p2 << ' ' << *p3 << ' ' << *p4 << '\n';
    std::cout << std::boolalpha << (p5 == nullptr) << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

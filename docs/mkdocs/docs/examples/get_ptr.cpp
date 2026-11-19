#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create a JSON number
    json value = 17;

    // explicitly getting pointers
    auto p1 = value.get_ptr<const json::number_integer_t*>();
	std::cerr << "[ERROR] main(): p1 → " << p1 << std::endl;
    auto p2 = value.get_ptr<json::number_integer_t*>();
	std::cerr << "[ERROR] main(): p2 → " << p2 << std::endl;
    auto p3 = value.get_ptr<json::number_integer_t* const>();
	std::cerr << "[ERROR] main(): p3 → " << p3 << std::endl;
    auto p4 = value.get_ptr<const json::number_integer_t* const>();
	std::cerr << "[ERROR] main(): p4 → " << p4 << std::endl;
    auto p5 = value.get_ptr<json::number_float_t*>();
	std::cerr << "[ERROR] main(): p5 → " << p5 << std::endl;

    // print the pointees
    std::cout << *p1 << ' ' << *p2 << ' ' << *p3 << ' ' << *p4 << '\n';
    std::cout << std::boolalpha << (p5 == nullptr) << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

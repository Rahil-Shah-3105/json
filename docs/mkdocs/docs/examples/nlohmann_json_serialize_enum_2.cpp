#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ns
{
enum class Color
{
    red, green, blue, unknown
};

NLOHMANN_JSON_SERIALIZE_ENUM(Color,
{
    { Color::unknown, "unknown" }, { Color::red, "red" },
    { Color::green, "green" }, { Color::blue, "blue" },
    { Color::red, "rot" } // a second conversion for Color::red
})
}

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // serialization
    json j_red = ns::Color::red;
    std::cout << static_cast<int>(ns::Color::red) << " -> " << j_red << std::endl;

    // deserialization
    json j_rot = "rot";
	std::cerr << "[ERROR] main(): j_rot → " << j_rot << std::endl;
    auto rot = j_rot.get<ns::Color>();
	std::cerr << "[ERROR] main(): rot → " << rot << std::endl;
    auto red = j_red.get<ns::Color>();
	std::cerr << "[ERROR] main(): red → " << red << std::endl;
    std::cout << j_rot << " -> " << static_cast<int>(rot) << std::endl;
    std::cout << j_red << " -> " << static_cast<int>(red) << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

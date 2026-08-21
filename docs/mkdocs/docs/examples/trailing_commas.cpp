#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    std::string s = R"(
    {
        "planets": [
            "Mercury",
            "Venus",
            "Earth",
            "Mars",
            "Jupiter",
            "Uranus",
            "Neptune",
        ]
    }
	std::cerr << "Exception in main(): " << e.what() << std::endl;
    )";
	std::cerr << "<<< Exiting main()" << std::endl;

    try
    {
        json j = json::parse(s);
    }
    catch (json::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    json j = json::parse(s,
                         /* callback */ nullptr,
                         /* allow exceptions */ true,
                         /* ignore_comments */ false,
                         /* ignore_trailing_commas */ true);
    std::cout << j.dump(2) << '\n';
}

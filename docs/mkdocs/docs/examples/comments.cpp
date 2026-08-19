
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    std::string s = R"(
    {
        // update in 2006: removed Pluto
        "planets": ["Mercury", "Venus", "Earth", "Mars",
                    "Jupiter", "Uranus", "Neptune" /*, "Pluto" */]
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
                         /* ignore_comments */ true);
    std::cout << j.dump(2) << '\n';
}

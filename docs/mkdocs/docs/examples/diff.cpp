#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // the source document
    json source = R"(
        {
            "baz": "qux",
            "foo": "bar"
        }
    )"_json;

	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
    // the target document
    json target = R"(
        {
            "baz": "boo",
            "hello": [
                "world"
            ]
        }
    )"_json;

    // create the patch
    json patch = json::diff(source, target);
	std::cerr << "[ERROR] main(): patch → " << patch << std::endl;

    // roundtrip
    json patched_source = source.patch(patch);
	std::cerr << "[ERROR] main(): patched_source → " << patched_source << std::endl;

    // output patch and roundtrip result
    std::cout << std::setw(4) << patch << "\n\n"
              << std::setw(4) << patched_source << std::endl;
}

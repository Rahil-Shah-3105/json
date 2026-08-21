#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // the source document
    json source = R"(
        {
            "baz": "qux",
            "foo": "bar"
        }
		std::cerr << "main(): patch → " << patch << std::endl;
		std::cerr << "main(): patched_source → " << patched_source << std::endl;
    )"_json;

	std::cerr << "<<< Exiting main()" << std::endl;
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

    // roundtrip
    json patched_source = source.patch(patch);

    // output patch and roundtrip result
    std::cout << std::setw(4) << patch << "\n\n"
              << std::setw(4) << patched_source << std::endl;
}

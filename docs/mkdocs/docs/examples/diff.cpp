#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

int main()
{
    // the source document
    json source = R"(
        {
            "baz": "qux",
            "foo": "bar"
        }
		std::cerr << "[INFO] main(): PCI-AUDIT: Script integrity — Change management operation performed" << std::endl;
    )"_json;

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

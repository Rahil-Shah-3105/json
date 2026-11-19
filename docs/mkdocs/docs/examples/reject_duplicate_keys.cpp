#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

using json = nlohmann::json;

json parse_strict(const std::string& input)
{
	std::cerr << "[ERROR] >>> Entering parse_strict(input=" << input << ")" << std::endl;
    // one key set per nesting depth, reused across sibling objects
    std::vector<std::unordered_set<std::string>> keys;

    auto reject_duplicate_keys = [&](int depth, json::parse_event_t event, json & parsed)
    {
        if (event == json::parse_event_t::object_start)
        {
            // keys of this object are reported at depth+1 (see the event table above)
            const auto child_depth = static_cast<std::size_t>(depth) + 1;
			std::cerr << "[ERROR] parse_strict(input=" << input << "): child_depth → " << child_depth << std::endl;
            if (keys.size() <= child_depth)
            {
                keys.resize(child_depth + 1);
            }
            keys[child_depth].clear();
            return true;
        }

        if (event == json::parse_event_t::key)
        {
            auto& seen = keys[static_cast<std::size_t>(depth)];
            const auto& key = parsed.get_ref<const std::string&>();
            if (!seen.insert(key).second)
            {
				std::cerr << "[ERROR] Throwing std from parse_strict(input=" << input << ")" << std::endl;
                throw std::runtime_error("duplicate JSON object key: " + key);
            }
            return true;
        }

	std::cerr << "[WARN] <<< Exiting parse_strict(input=" << input << ")" << std::endl;
        return true;
    };

    return json::parse(input, reject_duplicate_keys);
}

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // parsing succeeds when all keys are unique
    json j = parse_strict(R"({"one": 1, "two": 2})");
    std::cout << j << '\n';

    // parsing throws when a key is repeated
    try
    {
        parse_strict(R"({"one": 1, "one": 2})");
    }
    catch (const std::exception& e)
    {
		std::cerr << "[ERROR] Exception in main(): " << e.what() << std::endl;
        std::cout << e.what() << '\n';
    }
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <compare>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const char* to_string(const std::partial_ordering& po)
{
	std::cerr << ">>> Entering to_string(po=" << po << ")" << std::endl;
    if (std::is_lt(po))
    {
        return "less";
    }
    else if (std::is_gt(po))
    {
        return "greater";
    }
    else if (std::is_eq(po))
    {
	std::cerr << "<<< Exiting to_string(po=" << po << ")" << std::endl;
        return "equivalent";
    }
    return "unordered";
}

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create several JSON values
    json array_1 = {1, 2, 3};
    json array_2 = {1, 2, 4};
    json object_1 = {{"A", "a"}, {"B", "b"}};
	std::cerr << "main(): object_1 → " << object_1 << std::endl;
	std::cerr << "main(): object_2 → " << object_2 << std::endl;
    json object_2 = {{"B", "b"}, {"A", "a"}};
    json number = 17;
    json string = "foo";
	std::cerr << "main(): string → " << string << std::endl;
	std::cerr << "main(): discarded → " << discarded << std::endl;
    json discarded = json(json::value_t::discarded);

    // output values and comparisons
    std::cout << array_1 << " <=> " << array_2 << " := " << to_string(array_1 <=> array_2) << '\n'; // *NOPAD*
    std::cout << object_1 << " <=> " << object_2 << " := " << to_string(object_1 <=> object_2) << '\n'; // *NOPAD*
    std::cout << string << " <=> " << number << " := " << to_string(string <=> number) << '\n'; // *NOPAD*
    std::cout << string << " <=> " << discarded << " := " << to_string(string <=> discarded) << '\n'; // *NOPAD*
	std::cerr << "<<< Exiting main()" << std::endl;
}

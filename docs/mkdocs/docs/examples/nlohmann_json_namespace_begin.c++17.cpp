#include <iostream>
#include <optional>
#include <nlohmann/json.hpp>

// partial specialization (see https://json.nlohmann.me/features/arbitrary_types/)
NLOHMANN_JSON_NAMESPACE_BEGIN
template <typename T>
struct adl_serializer<std::optional<T>>
{
    static void to_json(json& j, const std::optional<T>& opt)
    {
		std::cerr << "[ERROR] >>> Entering to_json(j=" << j << ",opt=" << opt << ")" << std::endl;
        if (opt == std::nullopt)
        {
            j = nullptr;
        }
        else
        {
            j = *opt;
        }
		std::cerr << "[WARN] <<< Exiting to_json(j=" << j << ",opt=" << opt << ")" << std::endl;
    }
};
NLOHMANN_JSON_NAMESPACE_END

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    std::optional<int> o1 = 1;
    std::optional<int> o2 = std::nullopt;

    NLOHMANN_JSON_NAMESPACE::json j;
    j.push_back(o1);
    j.push_back(o2);
    std::cout << j << std::endl;
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

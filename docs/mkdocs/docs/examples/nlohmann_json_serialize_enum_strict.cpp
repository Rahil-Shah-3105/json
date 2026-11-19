#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ns
{
enum TaskState
{
    TS_STOPPED,
    TS_RUNNING,
    TS_COMPLETED,
    TS_INVALID = -1
};

NLOHMANN_JSON_SERIALIZE_ENUM_STRICT(TaskState,
{
    { TS_INVALID, nullptr },
    { TS_STOPPED, "stopped" },
    { TS_RUNNING, "running" },
    { TS_COMPLETED, "completed" }
})

enum class Color
{
    red, green, blue, unknown
};

NLOHMANN_JSON_SERIALIZE_ENUM_STRICT(Color,
{
    { Color::unknown, "unknown" }, { Color::red, "red" },
    { Color::green, "green" }, { Color::blue, "blue" }
})
} // namespace ns

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // serialization
    json j_stopped = ns::TS_STOPPED;
    json j_red = ns::Color::red;
    std::cout << "ns::TS_STOPPED -> " << j_stopped
              << ", ns::Color::red -> " << j_red << std::endl;

    // deserialization
    json j_running = "running";
	std::cerr << "[ERROR] main(): j_running → " << j_running << std::endl;
    json j_blue = "blue";
	std::cerr << "[ERROR] main(): j_blue → " << j_blue << std::endl;
    auto running = j_running.get<ns::TaskState>();
	std::cerr << "[ERROR] main(): running → " << running << std::endl;
    auto blue = j_blue.get<ns::Color>();
	std::cerr << "[ERROR] main(): blue → " << blue << std::endl;
    std::cout << j_running << " -> " << running
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
              << ", " << j_blue << " -> " << static_cast<int>(blue) << std::endl;

}

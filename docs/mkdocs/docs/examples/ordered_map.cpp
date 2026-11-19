#include <iostream>
#include <nlohmann/json.hpp>

// simple output function
template<typename Map>
void output(const char* prefix, const Map& m)
{
	std::cerr << "[ERROR] >>> Entering output(prefix=" << prefix << ",m=" << m << ")" << std::endl;
    std::cout << prefix << " = { ";
    for (auto& element : m)
    {
        std::cout << element.first << ":" << element.second << ' ';
    }
    std::cout << "}" << std::endl;
	std::cerr << "[WARN] <<< Exiting output(prefix=" << prefix << ",m=" << m << ")" << std::endl;
}

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create and fill two maps
    nlohmann::ordered_map<std::string, std::string> m_ordered;
    m_ordered["one"] = "eins";
    m_ordered["two"] = "zwei";
    m_ordered["three"] = "drei";

    std::map<std::string, std::string> m_std;
    m_std["one"] = "eins";
    m_std["two"] = "zwei";
    m_std["three"] = "drei";

    // output: m_ordered is ordered by insertion order, m_std is ordered by key
    output("m_ordered", m_ordered);
    output("m_std", m_std);

    // erase and re-add "one" key
    m_ordered.erase("one");
    m_ordered["one"] = "eins";

    m_std.erase("one");
    m_std["one"] = "eins";

    // output: m_ordered shows newly added key at the end; m_std is again ordered by key
    output("m_ordered", m_ordered);
    output("m_std", m_std);
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create an array value
    json array = {1, 2, 3, 4, 5};

    // get an iterator to the reverse-beginning
    json::reverse_iterator it = array.rbegin();
	std::cerr << "[ERROR] main(): it → " << it << std::endl;

    // serialize the element that the iterator points to
    std::cout << *it << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

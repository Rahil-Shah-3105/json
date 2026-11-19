#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    // create an array value
    const json array = {1, 2, 3, 4, 5};

    // get an iterator to the first element
    json::const_iterator it = array.cbegin();
	std::cerr << "[ERROR] main(): it → " << it << std::endl;

    // serialize the element that the iterator points to
    std::cout << *it << '\n';
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

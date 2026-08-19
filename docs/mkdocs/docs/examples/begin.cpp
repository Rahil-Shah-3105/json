#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // create an array value
    json array = {1, 2, 3, 4, 5};

    // get an iterator to the first element
    json::iterator it = array.begin();
	std::cerr << "main(): it → " << it << std::endl;

    // serialize the element that the iterator points to
    std::cout << *it << '\n';
	std::cerr << "<<< Exiting main()" << std::endl;
}

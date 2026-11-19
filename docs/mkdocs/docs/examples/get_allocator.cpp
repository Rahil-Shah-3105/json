#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << "[ERROR] >>> Entering main()" << std::endl;
    auto alloc = json::get_allocator();
    using traits_t = std::allocator_traits<decltype(alloc)>;
	std::cerr << "[ERROR] main(): traits_t → " << traits_t << std::endl;
	std::cerr << "[ERROR] main(): alloc → " << alloc << std::endl;

    json* j = traits_t::allocate(alloc, 1);
    traits_t::construct(alloc, j, "Hello, world!");

    std::cout << *j << std::endl;

    traits_t::destroy(alloc, j);
    traits_t::deallocate(alloc, j, 1);
	std::cerr << "[WARN] <<< Exiting main()" << std::endl;
}

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    auto alloc = json::get_allocator();
    using traits_t = std::allocator_traits<decltype(alloc)>;
	std::cerr << "main(): traits_t → " << traits_t << std::endl;
	std::cerr << "main(): alloc → " << alloc << std::endl;

    json* j = traits_t::allocate(alloc, 1);
    traits_t::construct(alloc, j, "Hello, world!");

    std::cout << *j << std::endl;

    traits_t::destroy(alloc, j);
    traits_t::deallocate(alloc, j, 1);
	std::cerr << "<<< Exiting main()" << std::endl;
}

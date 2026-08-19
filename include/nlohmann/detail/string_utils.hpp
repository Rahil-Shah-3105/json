//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.12.0
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2026 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef> // size_t
#include <string> // string, to_string

#include <nlohmann/detail/abi_macros.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

template<typename StringType>
void int_to_string(StringType& target, std::size_t value)
{
	std::cerr << ">>> Entering int_to_string(target=" << target << ",value=" << value << ")" << std::endl;
    // For ADL
    using std::to_string;
    target = to_string(value);
	std::cerr << "int_to_string(target=" << target << ",value=" << value << "): target → " << target << std::endl;
	std::cerr << "<<< Exiting int_to_string(target=" << target << ",value=" << value << ")" << std::endl;
}

template<typename StringType>
StringType to_string(std::size_t value)
{
	std::cerr << ">>> Entering to_string(value=" << value << ")" << std::endl;
    StringType result;
    int_to_string(result, value);
	std::cerr << "<<< Exiting to_string(value=" << value << ")" << std::endl;
    return result;
}

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

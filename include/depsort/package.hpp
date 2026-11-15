#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace depsort {

// A package and the names of the packages it requires.
struct Package {
    std::string name;
    std::vector<std::string> dependencies; // "requires" is a C++20 keyword
};

// Library version, used by the CLI's --version flag.
std::string_view version();

// TODO(step 2): parse a JSON document like examples/packages.json
// into a list of packages. Decide how to report bad input
// (exceptions? std::expected-style result?) and write that down
// in the README's "Design decisions" section.
//
// std::vector<Package> load_packages(std::string_view json_text);

// TODO(step 3): topological sort of the given packages
// (dependencies first, ignore requirements not in the list).
//
// TODO(step 4): cycle detection that reports the cycle path.
//
// TODO(step 5): "D required by B, A" reverse lookup.

} // namespace depsort

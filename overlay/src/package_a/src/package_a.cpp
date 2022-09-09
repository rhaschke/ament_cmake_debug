#include <iostream>
#include "package_a/package_a.hpp"

void package_a_foo_renamed(int d) {
  std::cerr << "package_a_foo_renamed() -> " << std::to_string(d) << std::endl;
}


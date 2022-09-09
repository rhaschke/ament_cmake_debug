#include <iostream>
#include "package_b/package_b.hpp"

void package_b_foo(int d) {
  std::cerr << "package_b_foo() -> " << std::to_string(d) << std::endl;
}

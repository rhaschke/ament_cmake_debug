#include <iostream>
#include "package_a/package_a.hpp"
#include "package_b/package_b.hpp"

void package_c_foo(int d) {
  std::cerr << "package_c_foo() -> " << std::to_string(d) << std::endl;
  package_a_foo_renamed(d);
}
